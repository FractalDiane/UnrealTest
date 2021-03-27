// Fill out your copyright notice in the Description page of Project Settings.


#include "Cutscene.h"

#include "DialogueWidget.h"

#include <Components/BoxComponent.h>
#include <LevelSequence/Public/LevelSequence.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>
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

	SequencePlayer = CreateDefaultSubobject<ULevelSequencePlayer>(TEXT("SequencePlayer"));
}

// Called when the game starts or when spawned
void ACutscene::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACutscene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACutscene::Dialogue(UDataTable* DialogueTable, FName Row)
{
	UUserWidget* Widget = CreateWidget(GetWorld(), DialogueWidgetRef, TEXT("Dialogue"));

	DialogueObj = Cast<UDialogueWidget>(Widget);

	FDialogueTable* ThisRow = DialogueTable->FindRow<FDialogueTable>(Row, "");
	DialogueObj->SetName(ThisRow->Name);
	DialogueObj->SetTextSoundPitch(ThisRow->SoundPitch);
	DialogueObj->SetDialogueText(ThisRow->DialogueText);

	Widget->AddToViewport();
	DialogueObj->OnDialogueFinished.BindDynamic(this, &ACutscene::ResumeCutscene);
	DialogueObj->Start();
}


void ACutscene::ResumeCutscene()
{

}
