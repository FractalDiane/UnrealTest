// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleUI.h"

#include "AbilityListUI.h"

#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/ScrollBox.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

#define BIND_BUTTON(Btn) Button ## Btn ## ->OnClicked.AddDynamic(this, &UBattleUI::ClickButton ## Btn)

void UBattleUI::NativeConstruct()
{
	Super::NativeConstruct();

	BIND_BUTTON(Attack);
	BIND_BUTTON(Ability);
	BIND_BUTTON(Item);
	BIND_BUTTON(Negotiate);
	BIND_BUTTON(Tactics);

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Controller->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUI(Controller, this);
	Controller->SetIgnoreLookInput(true);
}


void UBattleUI::NativeDestruct()
{
	Super::NativeDestruct();


}


void UBattleUI::ClickButtonAttack()
{
	for (auto* Ability : CurrentCharacter->GetData()->GetAbilities()) {
		AbilityList->AddAbility(Ability->GetAbilityName(), Ability->GetAbilityIcon(), ButtonTexture);
	}

	PlayAnimation(AnimClickAttack);
	PlayAnimation(AnimShowAbilityList);
}

void UBattleUI::ClickButtonAbility()
{

}

void UBattleUI::ClickButtonItem()
{

}

void UBattleUI::ClickButtonNegotiate()
{

}

void UBattleUI::ClickButtonTactics()
{

}