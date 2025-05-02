// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "Modules/ModuleManager.h"

class FBCIWidgetModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
