// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Battle/BattleCharacter.h"

#include <Blueprint/UserWidget.h>

#include "BattleUI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UBattleUI : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UTexture2D* ButtonTexture;

	UPROPERTY(meta = (BindWidget))
	class UImage* PentagramImage = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonAttack = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonAbility = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonItem = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonNegotiate = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTactics = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UAbilityListUI* AbilityList = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* AnimClickAttack = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* AnimShowAbilityList = nullptr;

	ABattleCharacter* CurrentCharacter;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	SETTER(ABattleCharacter*, CurrentCharacter);

private:
	UFUNCTION()
	void ClickButtonAttack();
	UFUNCTION()
	void ClickButtonAbility();
	UFUNCTION()
	void ClickButtonItem();
	UFUNCTION()
	void ClickButtonNegotiate();
	UFUNCTION()
	void ClickButtonTactics();
};
