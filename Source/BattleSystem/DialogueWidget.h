// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Utils/Macros.h"

#include <Blueprint/UserWidget.h>
#include <Engine/DataTable.h>

#include "DialogueWidget.generated.h"


USTRUCT(BlueprintType)
struct FDialogueTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> DialogueText;
};


UCLASS()
class BATTLESYSTEM_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	TArray<FText> Text;

	FString CurrentText;
	FString VisibleText;
	int32 CharactersVisible = 0;
	int32 Page = 0;

	FTimerHandle IncrementTimerHandle;
	float TextInterval = 0.05f;
	bool TextRunning = false;

	float TextSoundPitch = 1.0f;
	UPROPERTY(EditAnywhere)
	class USoundBase* TextSound;

	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* TextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameBlock = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* AnimFadein = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* AnimFadeout = nullptr;

	FWidgetAnimationDynamicEvent EventStart;
	FWidgetAnimationDynamicEvent EventStart2;
	FWidgetAnimationDynamicEvent EventEnd;
	FOnInputAction AdvanceDelegate;

	DECLARE_DYNAMIC_DELEGATE(FDialogueFinishedSignature);

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetName(const FText& Name);
	void SetDialogueText(const TArray<FText>& _Text);

	void Start();

	SETTER(float, TextSoundPitch);

	FDialogueFinishedSignature OnDialogueFinished;

private:
	UFUNCTION()
	void EnableInput();

	UFUNCTION()
	void IncrementCharactersVisible();

	void UpdateVisibleText();

	UFUNCTION()
	void StartText();
	UFUNCTION()
	void AdvanceText();

	UFUNCTION()
	void Destroy();
};
