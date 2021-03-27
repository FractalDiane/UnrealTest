// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interactibles/Interactible.h"
#include "DialogueWidget.h"

#include "NPC.generated.h"

UCLASS()
class BATTLESYSTEM_API ANPC : public AInteractible
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UDataTable* DialogueTable;

	TArray<FDialogueTable*> DialogueText;
	int32 DialogueSet = 0;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* Model;

	UPROPERTY(EditDefaultsOnly)
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
	void Interact() override;

private:
	void InteractFinish() override;
};
