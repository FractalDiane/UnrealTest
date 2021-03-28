// Fill out your copyright notice in the Description page of Project Settings.


#include "Cutscene.h"

#include "Cosmo.h"
#include "DialogueWidget.h"

#include <Components/BoxComponent.h>
#include <LevelSequence/Public/LevelSequence.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>
#include <LevelSequence/Public/LevelSequenceActor.h>
#include <Engine/DataTable.h>

// Sets default values
ACutscene::ACutscene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CutsceneTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CutsceneTrigger"));
	CutsceneTrigger->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ACutscene::BeginPlay()
{
	Super::BeginPlay();

	ALevelSequenceActor* Temp = nullptr;
	CutscenePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), CutsceneToPlay, FMovieSceneSequencePlaybackSettings(), Temp);
	
	if (AutoPlay) {
		StartCutscene();
	}
	else {
		CutsceneTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACutscene::PlayerEnterArea);
	}
}

// Called every frame
void ACutscene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACutscene::StartCutscene()
{
	CutscenePlayer->OnFinished.AddDynamic(this, &ACutscene::CutsceneFinished);
	CutscenePlayer->Play();
	CutsceneStarted = true;
}


void ACutscene::Dialogue(UDataTable* DialogueTable, FName Row)
{
	UUserWidget* Widget = CreateWidget(GetWorld(), DialogueBlueprintRef, TEXT("Dialogue"));

	DialogueObj = Cast<UDialogueWidget>(Widget);

	FDialogueTable* ThisRow = DialogueTable->FindRow<FDialogueTable>(Row, "");
	DialogueObj->SetName(ThisRow->Name);
	DialogueObj->SetTextSoundPitch(ThisRow->SoundPitch);
	DialogueObj->SetDialogueText(ThisRow->DialogueText);

	Widget->AddToViewport();
	DialogueObj->OnDialogueFinished.BindDynamic(this, &ACutscene::ResumeCutscene);
	CutscenePlayer->Pause();
	DialogueObj->Start();
}


void ACutscene::ResumeCutscene()
{
	CutscenePlayer->Play();
}


void ACutscene::CutsceneFinished()
{

	OnCutsceneFinished.ExecuteIfBound();
}


void ACutscene::PlayerEnterArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!CutsceneStarted && OtherActor->IsA(ACosmo::StaticClass())) {
		ACosmo* Player = Cast<ACosmo>(OtherActor);
		Player->StopMovement();
		OnCutsceneFinished.BindDynamic(Player, &ACosmo::EndCutscene);
		StartCutscene();
	}
}
