// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue.h"

#include <Kismet/KismetSystemLibrary.h>

#define PRINT(fmt, ...) UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT(fmt), __VA_ARGS__))

// Sets default values
ADialogue::ADialogue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void ADialogue::BeginPlay()
{
	Super::BeginPlay();

	DialogueWidget = Cast<UUserWidgetCpp>(DialogueWidgetRef->GetDefaultObject<UUserWidget>());
	
	UUserWidget* Widget = CreateWidget(GetWorld(), DialogueWidgetRef, TEXT("Dialogue"));
	Widget->AddToViewport();

	//DialogueWidget->SetText(FText::FromString("This is a test"));
}

// Called every frame
void ADialogue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADialogue::SetDialogueText(const FText& _Text)
{
	DialogueWidget->SetText(_Text);
}
