#include <GarrysMod/Lua/Interface.h>
#include <dependencies/windows/include/LogitechLEDLib.h>

#include "modules/logi.h"

GMOD_MODULE_OPEN()
{
	Logi::Initialize(LUA);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	LogiLedShutdown();

	// elegantly remove our table
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->PushNil();
	LUA->SetField(-2, "Logitech");
	LUA->Pop(1);

	return 0;
}