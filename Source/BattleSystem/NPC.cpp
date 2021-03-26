// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Cosmo.h"

#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include <Components/InputComponent.h>

// Sets default values
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = false;

	Model = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FName> Rows = DialogueTable->GetRowNames();
	for (int i = 0; i < Rows.Num(); i++) {
		DialogueText.Add(DialogueTable->FindRow<FDialogueTable>(Rows[i], ""));
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ANPC::Interact()
{
	UUserWidget* Widget = CreateWidget(GetWorld(), DialogueWidgetRef, TEXT("Dialogue"));

	Dialogue = Cast<UDialogueWidget>(Widget);

	Dialogue->SetName(FText::FromString(Name));
	//Dialogue->SetDialogueText(DialogueTable->FindRow<FDialogueTable>(DialogueTextRows[DialogueSet], "")->DialogueText);
	Dialogue->SetDialogueText(DialogueText[DialogueSet]->DialogueText);

	Widget->AddToViewport();
	Dialogue->OnDialogueFinished.BindDynamic(this, &ANPC::InteractFinish);
	Dialogue->SetTextSoundPitch(TextSoundPitch);
	Dialogue->Start();
}


void ANPC::InteractFinish()
{
	if (DialogueSet < DialogueText.Num() - 1) {
		DialogueSet++;
	}

	Dialogue->OnDialogueFinished.Unbind();
	OnInteractionFinished.Execute();
}
