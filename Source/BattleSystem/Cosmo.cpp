// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosmo.h"

#include "Interactibles/Interactible.h"
#include "CharacterAnimation.h"

#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
ACosmo::ACosmo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CameraPivot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPivot"));
	CameraPivot->SetupAttachment(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraPivot);

	Model = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(Root);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ACosmo::BeginPlay()
{
	Super::BeginPlay();
	
	UUserWidget* Widget = CreateWidget(GetWorld(), PlayerHUDRef, TEXT("PlayerHUD"));

	PlayerHUD = Cast<UPlayerHUD>(Widget);
	Widget->AddToViewport();
}

// Called every frame
void ACosmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Camera movement
	CameraPivot->AddLocalRotation(FRotator(0, -GetInputAxisValue("CameraH") * 60.0f * DeltaTime, 0));

	// Movement
	float X = GetInputAxisValue("Forward");
	float Y = GetInputAxisValue("Side");

	bool Moving = false;
	if (AllowMovement) {
		FTransform CamXform = Camera->GetComponentTransform();
		FVector MotionTarget = FVector::ZeroVector;
		MotionTarget += CamXform.GetRotation().GetAxisY() * Y;
		MotionTarget -= CamXform.GetRotation().GetAxisX() * X;
		MotionTarget.Normalize();

		MotionTarget.Z = 0.0f;
		Motion = FMath::Lerp(Motion, MotionTarget, DeltaTime * 10.0f);

		SetActorLocation(GetActorLocation() + (Motion * SpeedLimit + Motion * SpeedLimit * Running) * DeltaTime);

		Moving = !MotionTarget.IsZero();

		// Rotation
		if (Moving) {
			FQuat QFrom = Model->GetComponentRotation().Quaternion();
			FQuat QTo{ FVector(0, 0, 1), FMath::Atan2(-MotionTarget.X, MotionTarget.Y) + FMath::DegreesToRadians(180.0f) };

			Model->SetWorldRotation(FQuat::Slerp(QFrom, QTo, DeltaTime * 10.0f));
		}
	}
	
	// Animation
	SetAnimationBool("Walking", Moving);
	SetAnimationBool("Running", Running);
}

// Called to bind functionality to input
void ACosmo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward");
	PlayerInputComponent->BindAxis("Side");
	PlayerInputComponent->BindAxis("CameraH");
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACosmo::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACosmo::EndRun);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACosmo::Interact);
}


void ACosmo::StopMovement()
{
	AllowMovement = false;
	Motion = FVector::ZeroVector;
	SetAnimationBool("Walking", false);
}


void ACosmo::AddInteractibleInRange(AInteractible* Target)
{
	InteractiblesInRange.Add(Target);
}


void ACosmo::RemoveInteractibleInRange(AInteractible* Target)
{
	InteractiblesInRange.Remove(Target);
}


void ACosmo::StartRun()
{
	Running = true;
}


void ACosmo::EndRun()
{
	Running = false;
}


void ACosmo::SetAnimationBool(FName Field, bool Value)
{
	UAnimInstance* AnimInst = Model->GetAnimInstance();
	FBoolProperty* Prop = FindFProperty<FBoolProperty>(AnimInst->GetClass(), Field);
	Prop->SetPropertyValue_InContainer(AnimInst, Value);
}


void ACosmo::Interact()
{
	if (AllowMovement && InteractiblesInRange.Num() > 0) {
		StopMovement();
		InteractiblesInRange[0]->OnInteractionFinished.BindDynamic(this, &ACosmo::EndInteract);
		InteractiblesInRange[0]->Interact();
	}
}


void ACosmo::EndInteract()
{
	InteractiblesInRange[0]->OnInteractionFinished.Unbind();
	AllowMovement = true;
}


void ACosmo::EndCutscene()
{
	AllowMovement = true;
}
