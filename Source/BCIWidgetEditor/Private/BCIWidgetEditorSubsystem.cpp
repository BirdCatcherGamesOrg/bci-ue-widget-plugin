// SPDX-License-Identifier: MPL-2.0

#include "BCIWidgetEditorSubsystem.h"

#include "RichTextBlockDecoratorSync.h"

void UBCIWidgetEditorSubsystem::Sync(class URichTextBlock* BlockToSync, const TArray<const TSubclassOf<class URichTextBlockDecorator>>& Decorators)
{
	FRichTextBlockDecoratorSync::Sync(BlockToSync, Decorators);
}
