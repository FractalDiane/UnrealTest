// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Engine/SkeletalMesh.h>

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

	// Components
	UPROPERTY(EditAnywhere)
	USceneComponent* CameraPivot;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Model;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
