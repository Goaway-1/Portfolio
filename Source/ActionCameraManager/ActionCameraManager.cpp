// Copyright 2022 Namman. All Rights Reserved.

#include "ActionCameraManager.h"

#define LOCTEXT_NAMESPACE "FActionCameraManagerModule"

void FActionCameraManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FActionCameraManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FActionCameraManagerModule, ActionCameraManager)


//#include "ActionCameraManager.h"
//
////�ָ��ε��� �����ϵ��� ����
//IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, ActionCameraManager, "ActionCameraManager");