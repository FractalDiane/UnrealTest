// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosmo.h"

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

}

// Called when the game starts or when spawned
void ACosmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACosmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Camera movement
	CameraPivot->AddLocalRotation(FRotator(0, -GetInputAxisValue("CameraH") * 0.3f, 0));

	// Movement
	float X = GetInputAxisValue("Forward");
	float Y = GetInputAxisValue("Side");
	
	FTransform CamXform = Camera->GetComponentTransform();
	FVector MotionTarget = FVector::ZeroVector;
	MotionTarget += CamXform.GetRotation().GetAxisY() * Y;
	MotionTarget -= CamXform.GetRotation().GetAxisX() * X;
	MotionTarget.Normalize();

	MotionTarget.Z = 0.0f;
	Motion = FMath::Lerp(Motion, MotionTarget, DeltaTime * 10.0f);
	
	SetActorLocation(GetActorLocation() + Motion * SpeedLimit);

	bool Moving = !MotionTarget.IsZero();

	// Rotation
	if (Moving) {
		FQuat QFrom = Model->GetComponentRotation().Quaternion();
		FQuat QTo{ FVector(0, 0, 1), FMath::Atan2(-MotionTarget.X, MotionTarget.Y) + FMath::DegreesToRadians(180.0f) };

		Model->SetWorldRotation(FQuat::Slerp(QFrom, QTo, DeltaTime * 10.0f));
	}
	
	// Animation
	UAnimInstance* AnimInst = Model->GetAnimInstance();
	FBoolProperty* WalkingVar = FindFProperty<FBoolProperty>(AnimInst->GetClass(), "Walking");
	if (WalkingVar) {
		WalkingVar->SetPropertyValue_InContainer(AnimInst, Moving);
	}
}

// Called to bind functionality to input
void ACosmo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward");
	PlayerInputComponent->BindAxis("Side");
	PlayerInputComponent->BindAxis("CameraH");
}

