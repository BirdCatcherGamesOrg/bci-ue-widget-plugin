// SPDX-License-Identifier: MPL-2.0


#include "AnimatedShowHideWidget.h"

void UBCIVNDKWidgetAnimatedShowHideWidget::SetVisibility(ESlateVisibility NewVisibility)
{
	if (NewVisibility != ESlateVisibility::Visible || NewVisibility != ESlateVisibility::Hidden)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick([this, NewVisibility]()
		{
			Super::SetVisibility(NewVisibility);
			FBCIVNDKWidgetAnimationFinishedResponse Response;
			Response.DesiredVisibility = NewVisibility;
			Response.bSuccess = true;
			OnShowHideAnimationFinished.Broadcast(Response);
		});
	}
	
	if (IsAnimationPlaying(ShowAnimation) || IsAnimationPlaying(HideAnimation))
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick([this, NewVisibility]()
		{
			FBCIVNDKWidgetAnimationFinishedResponse Response;
			Response.DesiredVisibility = NewVisibility;
			Response.bSuccess = false;
			OnShowHideAnimationFinished.Broadcast(Response);
		});
	}

	DesiredVisibility = NewVisibility;

	UWidgetAnimation* AnimationToPlay = nullptr;
	if (NewVisibility == ESlateVisibility::Hidden)
	{
		AnimationToPlay = HideAnimation;

	}
	else if (NewVisibility == ESlateVisibility::Visible)
	{
		// Set visible immediately. Designers need to handle stuff like making the widget start off with 0 opacity.
		SetVisibility(ESlateVisibility::Visible);
		AnimationToPlay = ShowAnimation;
	}

	if (AnimationToPlay)
	{
		FWidgetAnimationDynamicEvent Delegate;
		Delegate.BindDynamic(this, &UBCIVNDKWidgetAnimatedShowHideWidget::ShowHideFinished);
		BindToAnimationFinished(AnimationToPlay, Delegate);
		QueuePlayAnimation(AnimationToPlay);
	}
	
	GetWorld()->GetTimerManager().SetTimerForNextTick([this, NewVisibility]()
    {
    	FBCIVNDKWidgetAnimationFinishedResponse Response;
    	Response.DesiredVisibility = NewVisibility;
    	Response.bSuccess = false;
    	OnShowHideAnimationFinished.Broadcast(Response);
    });
}

void UBCIVNDKWidgetAnimatedShowHideWidget::ShowHideFinished()
{
	Super::SetVisibility(DesiredVisibility);
	FBCIVNDKWidgetAnimationFinishedResponse Response;
	Response.DesiredVisibility = DesiredVisibility;
	Response.bSuccess = true;
	OnShowHideAnimationFinished.Broadcast(Response);
}
