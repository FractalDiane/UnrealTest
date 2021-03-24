// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Blueprint/UserWidget.h>
#include <Components/RichTextBlock.h>
#include <Components/TextBlock.h>

#include "UserWidgetCpp.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UUserWidgetCpp : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* TextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameBlock = nullptr;

public:
	virtual void NativeConstruct() override;

public:
	void SetText(const FText& Text);
};
