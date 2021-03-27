// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <GameFramework/Actor.h>

#include "Cutscene.generated.h"

UCLASS()
class BATTLESYSTEM_API ACutscene : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class ULevelSequence* CutsceneToPlay;
	UPROPERTY(EditAnywhere)
	bool AutoPlay = false;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* CutsceneTrigger;
	UPROPERTY(EditDefaultsOnly)
	class ULevelSequencePlayer* SequencePlayer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> DialogueWidgetRef;

	class UDialogueWidget* DialogueObj;
	
public:	
	// Sets default values for this actor's properties
	ACutscene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Dialogue(class UDataTable* DialogueTable, FName Row);

private:
	UFUNCTION()
	void ResumeCutscene();
};
