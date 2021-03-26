// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactible.generated.h"

UCLASS()
class BATTLESYSTEM_API AInteractible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	FText InteractPrompt;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* InteractArea;

	bool PlayerInArea = false;

	DECLARE_DYNAMIC_DELEGATE(FInteractionFinishedSignature);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact();
	
	FInteractionFinishedSignature OnInteractionFinished;

protected:
	UFUNCTION()
	virtual void InteractFinish();

private:
	UFUNCTION()
	void PlayerEnterArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void PlayerExitArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
