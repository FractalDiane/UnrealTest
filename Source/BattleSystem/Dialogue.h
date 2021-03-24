// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UI/UserWidgetCpp.h"

#include <GameFramework/Actor.h>
#include <Blueprint/UserWidget.h>
#include <Components/RichTextBlock.h>

#include "Dialogue.generated.h"

UCLASS()
class BATTLESYSTEM_API ADialogue : public AActor
{
	GENERATED_BODY()

private:
	TArray<FString> Text;
	unsigned int CharactersVisible = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DialogueWidgetRef;

	UUserWidgetCpp* DialogueWidget;
	
public:	
	// Sets default values for this actor's properties
	ADialogue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDialogueText(const FText& _Text);
};
