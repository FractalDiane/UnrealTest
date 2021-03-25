// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Cosmo.h"
#include "DialogueWidget.h"

#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include <Components/InputComponent.h>

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Model = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
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
	Dialogue->SetDialogueText(DialogueText);

	Widget->AddToViewport();
	Dialogue->OnDialogueFinished.BindDynamic(this, &ANPC::InteractFinish);
	Dialogue->Start();
}


void ANPC::InteractFinish()
{
	Dialogue->OnDialogueFinished.Unbind();
	OnInteractionFinished.Execute();
}
