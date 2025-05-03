// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimatedShowHideWidget.generated.h"

USTRUCT(BlueprintType)
struct FBCIVNDKWidgetAnimationFinishedResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ESlateVisibility DesiredVisibility;
	
	UPROPERTY(BlueprintReadOnly)
	bool bSuccess = false;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShowHideAnimationSignature, const FBCIVNDKWidgetAnimationFinishedResponse&, Result);

/**
 * @brief UBCIVNDKWidgetAnimatedShowHideWidget is a wrapper widget over a slot that provides show/hide animations.
 */
UCLASS(MinimalAPI)
class UBCIVNDKWidgetAnimatedShowHideWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		
	virtual void SetVisibility(ESlateVisibility NewVisibility) override;

	UPROPERTY(BlueprintAssignable)
	FShowHideAnimationSignature OnShowHideAnimationFinished;
	
	/**
	 * @brief Content is the content to display.
	 */
	UPROPERTY(EditDefaultsOnly, Transient, meta=(BindWidget))
	TObjectPtr<class UNamedSlot> Content;

	/**
	 * @brief ShowAnimation is the optional animation to play when showing.
	 */
	UPROPERTY(EditDefaultsOnly, Transient, meta=(BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> ShowAnimation;

	/**
	 * @brief HideAnimation is the optional animation to play when hiding.
	 */
	UPROPERTY(EditDefaultsOnly, Transient, meta=(BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> HideAnimation;

private:

	UPROPERTY()
	ESlateVisibility DesiredVisibility;
	
	UFUNCTION()
	void ShowHideFinished();
	
};
