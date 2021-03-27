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


void ANPC::Interact()
{
	Super::Interact();

	UUserWidget* Widget = CreateWidget(GetWorld(), DialogueWidgetRef, TEXT("Dialogue"));

	Dialogue = Cast<UDialogueWidget>(Widget);

	FDialogueTable* ThisRow = DialogueText[DialogueSet];
	Dialogue->SetName(ThisRow->Name);
	Dialogue->SetTextSoundPitch(ThisRow->SoundPitch);
	Dialogue->SetDialogueText(ThisRow->DialogueText);

	Widget->AddToViewport();
	Dialogue->OnDialogueFinished.BindDynamic(this, &ANPC::InteractFinish);
	Dialogue->Start();
}


void ANPC::InteractFinish()
{
	Super::InteractFinish();

	if (DialogueSet < DialogueText.Num() - 1) {
		DialogueSet++;
	}

	Dialogue->OnDialogueFinished.Unbind();
	OnInteractionFinished.Execute();
}
