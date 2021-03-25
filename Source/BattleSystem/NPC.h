// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactibles/Interactible.h"

#include "NPC.generated.h"

UCLASS()
class BATTLESYSTEM_API ANPC : public AInteractible
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere, meta = (MultiLine = "true"))
	TArray<FString> DialogueText;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* Model;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DialogueWidgetRef;

	class UDialogueWidget* Dialogue;

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

	void Interact() override;
	void InteractFinish() override;
};
