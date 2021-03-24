// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	TArray<FString> Text;

	FString VisibleText;
	uint32 CharactersVisible = 0;
	uint32 Page = 0;

	FTimerHandle IncrementTimerHandle;
	float TextInterval = 0.3f;

	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* TextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameBlock = nullptr;

public:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	void SetName(const FText& Name);
	void SetDialogueText(const TArray<FString>& _Text);

	void Start();

private:
	UFUNCTION()
	void IncrementCharactersVisible();

	void UpdateVisibleText();
};
