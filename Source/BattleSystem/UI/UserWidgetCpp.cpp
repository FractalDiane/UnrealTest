// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetCpp.h"

#include <Kismet/KismetSystemLibrary.h>

#define PRINT(fmt, ...) UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT(fmt), __VA_ARGS__))

void UUserWidgetCpp::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock->SetText(FText::FromString("This is a test"));
}


void UUserWidgetCpp::SetText(const FText& Text)
{
	if (TextBlock) {
		TextBlock->SetText(Text);
	}
}
