// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	enum Button : int32
	{
		FaceUp,
		FaceDown,
		FaceLeft,
		FaceRight,
		L1,
		L2,
		R1,
		R2,
	};

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<class UTexture2D*> ButtonImages;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractText = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UImage* InteractButton = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* AnimInteractFadein = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* AnimInteractFadeout = nullptr;

public:
	void ShowInteractHUD(bool Show);
	void SetInteractPrompt(const FText& Prompt);
	void SetInteractButton(Button _Button);
};
