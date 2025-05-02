// SPDX-License-Identifier: MPL-2.0

#include "RichTextBlockDecoratorSync.h"

#include "BCILog.h"
#include "Components/RichTextBlockDecorator.h"


void FRichTextBlockDecoratorSync::Sync(URichTextBlock* BlockToSync, const TArray<const TSubclassOf<URichTextBlockDecorator>>& Decorators)
{
	static FName PropName = GET_MEMBER_NAME_CHECKED(FRichTextBlockDecoratorSync, DecoratorClasses);
	FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(BlockToSync->GetClass(), PropName);

	if (!ArrayProp)
	{
		BCILOG(LogTemp, Warning, TEXT("Failed to find DecoratorClasses"));
		return;
	}

	void* ArrayPtr = ArrayProp->ContainerPtrToValuePtr<void>(BlockToSync);
	FScriptArrayHelper ArrayHelper(ArrayProp, ArrayPtr);

	for (const auto& NewDecoratorClass : Decorators)
	{
		bool bExists = false;

		// Check if the NewDecoratorClass is already in the DecoratorClasses
		for (int32 i = 0; i < ArrayHelper.Num(); ++i)
		{
			const FObjectPropertyBase* InnerProp = CastFieldChecked<FObjectPropertyBase>(ArrayProp->Inner);
			UObject* ExistingDecoratorClass = InnerProp->GetObjectPropertyValue(ArrayHelper.GetRawPtr(i));

			if (ExistingDecoratorClass && ExistingDecoratorClass->IsA(NewDecoratorClass))
			{
				bExists = true;
				break;
			}
		}

		// If it doesn't exist, add it manually
		if (!bExists)
		{
			// Add a new entry at the end of the array
			ArrayHelper.AddValue();

			// Access the newly added element and set it to the new decorator class
			FObjectPropertyBase* InnerProp = CastFieldChecked<FObjectPropertyBase>(ArrayProp->Inner);
			InnerProp->SetObjectPropertyValue(ArrayHelper.GetRawPtr(ArrayHelper.Num() - 1), NewDecoratorClass);

			UE_LOG(LogTemp, Log, TEXT("Added %s to DecoratorClasses."), *NewDecoratorClass->GetName());
		}
	}
}
