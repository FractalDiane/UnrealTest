// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DialogueWidget.h"

#include <GameFramework/Actor.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>

#include "NPC.generated.h"

UCLASS()
class BATTLESYSTEM_API ANPC : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere, meta = (MultiLine = "true"))
	TArray<FString> DialogueText;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Model;
	UPROPERTY(EditAnywhere)
	USphereComponent* TalkArea;

	//ADialogue* DialogueRef;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DialogueWidgetRef;

	//UDialogueWidget* Dialogue;

	bool PlayerInArea = false;
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact();

private:
	UFUNCTION()
	void SphereStartCol(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void SphereEndCol(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
