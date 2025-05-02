// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlock.h"

/**
 * 
 */
struct FRichTextBlockDecoratorSync : private URichTextBlock
{
	static void Sync(class URichTextBlock* BlockToSync, const TArray<const TSubclassOf<class URichTextBlockDecorator>>& Decorators);
};
