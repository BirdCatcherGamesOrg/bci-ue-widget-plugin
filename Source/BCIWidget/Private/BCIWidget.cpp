// SPDX-License-Identifier: MPL-2.0

#include "BCIWidget.h"

#define LOCTEXT_NAMESPACE "FBCIWidgetModule"

void FBCIWidgetModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FBCIWidgetModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBCIWidgetModule, BCIWidget)