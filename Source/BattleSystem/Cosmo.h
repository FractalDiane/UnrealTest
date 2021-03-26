// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "UI/PlayerHUD.h"
#include "Utils/Macros.h"

#include "Cosmo.generated.h"

UCLASS()
class BATTLESYSTEM_API ACosmo : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACosmo();

private:
	UPROPERTY(EditAnywhere)
	float SpeedLimit = 5;

	FVector Motion = FVector::ZeroVector;
	bool Running = false;

	bool AllowMovement = true;

	TArray<class AInteractible*> InteractiblesInRange;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerHUDRef;

	class UPlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere)
	class USceneComponent* CameraPivot;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* Model;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	SETTER(bool, AllowMovement);

	GETTER(UPlayerHUD*, PlayerHUD);
	void AddInteractibleInRange(class AInteractible* Target);
	void RemoveInteractibleInRange(class AInteractible* Target);

private:
	void StartRun();
	void EndRun();

	void Interact();
	UFUNCTION()
	void EndInteract();
};
