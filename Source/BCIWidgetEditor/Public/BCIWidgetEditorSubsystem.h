// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "BCIWidgetEditorSubsystem.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UBCIWidgetEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	
	BCIWIDGETEDITOR_API void Sync(class URichTextBlock* BlockToSync, const TArray<const TSubclassOf<class URichTextBlockDecorator>>& Decorators);
	
};
