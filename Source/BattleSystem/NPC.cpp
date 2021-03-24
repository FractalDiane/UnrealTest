// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Cosmo.h"

#include <Kismet/KismetSystemLibrary.h>

#define PRINT(fmt, ...) UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT(fmt), __VA_ARGS__))

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Model = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(Root);

	TalkArea = CreateDefaultSubobject<USphereComponent>(TEXT("TalkArea"));
	TalkArea->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	TalkArea->OnComponentBeginOverlap.AddDynamic(this, &ANPC::SphereStartCol);
	TalkArea->OnComponentEndOverlap.AddDynamic(this, &ANPC::SphereEndCol);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ANPC::Interact()
{
	UUserWidget* Widget = CreateWidget(GetWorld(), DialogueWidgetRef, TEXT("Dialogue"));
	UDialogueWidget* Dialogue = Cast<UDialogueWidget>(Widget);

	Dialogue->SetName(FText::FromString(Name));
	Dialogue->SetDialogueText(DialogueText);

	Widget->AddToViewport();
}

void ANPC::SphereStartCol(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACosmo::StaticClass())) {
		Cast<ACosmo>(OtherActor)->SetNPCInRange(this);
	}
}

void ANPC::SphereEndCol(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACosmo::StaticClass())) {
		Cast<ACosmo>(OtherActor)->SetNPCInRange(nullptr);
	}
}
