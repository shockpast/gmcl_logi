#include <GarrysMod/Lua/Interface.h>
#include <dependencies/windows/include/LogitechLEDLib.h>

#include <stdio.h>
#include <string.h>
#include <utility>

#include "modules/logi.h"

static const std::pair<const char*, int> keyEnum[] = {
  {"ESC", 0x01}, {"F1", 0x3b}, {"F2", 0x3c}, {"F3", 0x3d}, {"F4", 0x3e},
  {"F5", 0x3f}, {"F6", 0x40}, {"F7", 0x41}, {"F8", 0x42}, {"F9", 0x43},
  {"F10", 0x44}, {"F11", 0x57}, {"F12", 0x58}, {"PRINT_SCREEN", 0x137},
  {"SCROLL_LOCK", 0x46}, {"PAUSE_BREAK", 0x145}, {"TILDE", 0x29},
  {"ONE", 0x02}, {"TWO", 0x03}, {"THREE", 0x04}, {"FOUR", 0x05},
  {"FIVE", 0x06}, {"SIX", 0x07}, {"SEVEN", 0x08}, {"EIGHT", 0x09},
  {"NINE", 0x0A}, {"ZERO", 0x0B}, {"MINUS", 0x0C}, {"EQUALS", 0x0D},
  {"BACKSPACE", 0x0E}, {"INSERT", 0x152}, {"HOME", 0x147}, {"PAGE_UP", 0x149},
  {"NUM_LOCK", 0x45}, {"NUM_SLASH", 0x135}, {"NUM_ASTERISK", 0x37},
  {"NUM_MINUS", 0x4A}, {"TAB", 0x0F}, {"Q", 0x10}, {"W", 0x11},
  {"E", 0x12}, {"R", 0x13}, {"T", 0x14}, {"Y", 0x15}, {"U", 0x16},
  {"I", 0x17}, {"O", 0x18}, {"P", 0x19}, {"OPEN_BRACKET", 0x1A},
  {"CLOSE_BRACKET", 0x1B}, {"BACKSLASH", 0x2B}, {"KEYBOARD_DELETE", 0x153},
  {"END", 0x14F}, {"PAGE_DOWN", 0x151}, {"NUM_SEVEN", 0x47},
  {"NUM_EIGHT", 0x48}, {"NUM_NINE", 0x49}, {"NUM_PLUS", 0x4E},
  {"CAPS_LOCK", 0x3A}, {"A", 0x1E}, {"S", 0x1F}, {"D", 0x20}, {"F", 0x21},
  {"G", 0x22}, {"H", 0x23}, {"J", 0x24}, {"K", 0x25}, {"L", 0x26},
  {"SEMICOLON", 0x27}, {"APOSTROPHE", 0x28}, {"ENTER", 0x1C},
  {"NUM_FOUR", 0x4B}, {"NUM_FIVE", 0x4C}, {"NUM_SIX", 0x4D},
  {"LEFT_SHIFT", 0x2A}, {"Z", 0x2C}, {"X", 0x2D}, {"C", 0x2E},
  {"V", 0x2F}, {"B", 0x30}, {"N", 0x31}, {"M", 0x32}, {"COMMA", 0x33},
  {"PERIOD", 0x34}, {"FORWARD_SLASH", 0x35}, {"RIGHT_SHIFT", 0x36},
  {"ARROW_UP", 0x148}, {"NUM_ONE", 0x4F}, {"NUM_TWO", 0x50},
  {"NUM_THREE", 0x51}, {"NUM_ENTER", 0x11C}, {"LEFT_CONTROL", 0x1D},
  {"LEFT_WINDOWS", 0x15B}, {"LEFT_ALT", 0x38}, {"SPACE", 0x39},
  {"RIGHT_ALT", 0x138}, {"RIGHT_WINDOWS", 0x15C}, {"APPLICATION_SELECT", 0x15D},
  {"RIGHT_CONTROL", 0x11D}, {"ARROW_LEFT", 0x14B}, {"ARROW_DOWN", 0x150},
  {"ARROW_RIGHT", 0x14D}, {"NUM_ZERO", 0x52}, {"NUM_PERIOD", 0x53},
  {"G_1", 0xFFF1}, {"G_2", 0xFFF2}, {"G_3", 0xFFF3}, {"G_4", 0xFFF4},
  {"G_5", 0xFFF5}, {"G_6", 0xFFF6}, {"G_7", 0xFFF7}, {"G_8", 0xFFF8},
  {"G_9", 0xFFF9}, {"G_LOGO", 0xFFFF1}, {"G_BADGE", 0xFFFF2}
};

static const std::pair<const char*, int> deviceTypeEnum[] = {
  {"Keyboard", LogiLed::Keyboard}, {"Mouse", LogiLed::Mouse}, {"Mousemat", LogiLed::Mousemat},
  {"Headset", LogiLed::Headset}, {"Speaker", LogiLed::Speaker}
};

static void CreateEnumTable(GarrysMod::Lua::ILuaBase* LUA, const char* tableName, const std::pair<const char*, int> enumTable[], size_t size)
{
  LUA->CreateTable();

  for (size_t i = 0; i < size; i++)
  {
    LUA->PushNumber(enumTable[i].second);
    LUA->SetField(-2, enumTable[i].first);
  }

  LUA->SetField(-2, tableName);
}

static void ReadColor(GarrysMod::Lua::ILuaBase* LUA, int index, int &r, int &g, int &b)
{
  if (!LUA->IsType(-index, GarrysMod::Lua::Type::TABLE))
  {
    char buf[512];
    sprintf(buf, "Expected Color at '%d', got '%s' instead", index, LUA->GetTypeName(LUA->GetType(-index)));

    LUA->ThrowError(buf);

    return;
  }

  LUA->GetField(-1, "r");
  r = LUA->GetNumber(-1);
  LUA->Pop(1);

  LUA->GetField(-1, "g");
  g = LUA->GetNumber(-1);
  LUA->Pop(1);

  LUA->GetField(-1, "b");
  b = LUA->GetNumber(-1);
  LUA->Pop(1);
}

// Class Functions
LUA_FUNCTION_STATIC(L_LogiLedInitWithName)
{
  bool result = LogiLedInitWithName(LUA->CheckString());
  LUA->PushBool(result);
  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedShutdown)
{
  LogiLedShutdown();
  return 0;
}

// Per-Key Functions (there is a lot of them, but i'm not sure if i should add them as they do same thing)
LUA_FUNCTION_STATIC(L_LogiLedSaveLightingForKey)
{
  LogiLed::KeyName keyName = static_cast<LogiLed::KeyName>(LUA->CheckNumber());

  bool result = LogiLedSaveLightingForKey(keyName);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedSetLightingForKey)
{
  LogiLed::KeyName keyName = static_cast<LogiLed::KeyName>(LUA->CheckNumber(-1));

  int r, g, b;
  ReadColor(LUA, -2, r, g, b);

  bool result = LogiLedSetLightingForKeyWithKeyName(keyName, r, g, b);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedRestoreLightingForKey)
{
  LogiLed::KeyName keyName = static_cast<LogiLed::KeyName>(LUA->CheckNumber());

  bool result = LogiLedRestoreLightingForKey(keyName);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedFlashSingleKey)
{
  LogiLed::KeyName keyName = static_cast<LogiLed::KeyName>(LUA->CheckNumber(-1));

  int r, g, b;
  ReadColor(LUA, -2, r, g, b);

  int duration = LUA->CheckNumber(-3);
  int interval = LUA->CheckNumber(-4);

  bool result = LogiLedFlashSingleKey(keyName, r, g, b, duration, interval);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedPulseSingleKey)
{
  LogiLed::KeyName keyName = static_cast<LogiLed::KeyName>(LUA->CheckNumber(-1));

  int startR, startG, startB;
  ReadColor(LUA, -2, startR, startG, startB);

  int finishR, finishG, finishB;
  ReadColor(LUA, -3, finishR, finishG, finishB);

  int duration = LUA->CheckNumber(-4);
  bool isInfinite = LUA->CheckNumber(-5);

  bool result = LogiLedPulseSingleKey(keyName, startR, startG, startB, finishR, finishG, finishB, duration, isInfinite);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedStopEffectsOnKey)
{
  LogiLed::KeyName keyName = static_cast<LogiLed::KeyName>(LUA->CheckNumber());

  bool result = LogiLedStopEffectsOnKey(keyName);
  LUA->PushBool(result);

  return 1;
}

// Getters
LUA_FUNCTION_STATIC(L_LogiLedGetSdkVersion)
{
  int major, minor, build;
  char buf[32];

  LogiLedGetSdkVersion(&major, &minor, &build);
  sprintf(buf, "%d.%d.%d", major, minor, build);

  LUA->PushString(buf);

  return 1;
}

// Zonal Functions
LUA_FUNCTION_STATIC(L_LogiLedSetLightingForTargetZone)
{
  LogiLed::DeviceType deviceType = static_cast<LogiLed::DeviceType>(LUA->CheckNumber(-1));
  int zone = LUA->CheckNumber(-2);

  int r, g, b;
  ReadColor(LUA, -3, r, g, b);

  bool result = LogiLedSetLightingForTargetZone(deviceType, zone, r, g, b);
  LUA->PushBool(result);

  return 1;
}

// Generic Functions (as described in Logi SDK)
LUA_FUNCTION_STATIC(L_LogiLedSetTargetDevice)
{
  LogiLed::DeviceType targetDevice = static_cast<LogiLed::DeviceType>(LUA->CheckNumber());

  bool result = LogiLedSetTargetDevice(targetDevice);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedSaveCurrentLighting)
{
  bool result = LogiLedSaveCurrentLighting();
  LUA->PushBool(result);
  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedSetLightning)
{
  int r, g, b;
  ReadColor(LUA, -1, r, g, b);

  bool result = LogiLedSetLighting(r, g, b);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedRestoreLighting)
{
  bool result = LogiLedRestoreLighting();
  LUA->PushBool(result);
  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedFlashLighting)
{
  int r, g, b;
  ReadColor(LUA, -1, r, g, b);

  int duration = LUA->CheckNumber(-2);
  int interval = LUA->CheckNumber(-3);

  bool result = LogiLedFlashLighting(r, g, b, duration, interval);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedPulseLighting)
{
  int r, g, b;
  ReadColor(LUA, -1, r, g, b);

  int duration = LUA->CheckNumber(-2);
  int interval = LUA->CheckNumber(-3);

  bool result = LogiLedPulseLighting(r, g, b, duration, interval);
  LUA->PushBool(result);

  return 1;
}

LUA_FUNCTION_STATIC(L_LogiLedStopEffects)
{
  bool result = LogiLedStopEffects();
  LUA->PushBool(result);
  return 1;
}

void Logi::Initialize(GarrysMod::Lua::ILuaBase* LUA)
{
  LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->CreateTable();
      LUA->PushCFunction(L_LogiLedInitWithName);
      LUA->SetField(-2, "Initialize");
      LUA->PushCFunction(L_LogiLedShutdown);
      LUA->SetField(-2, "Shutdown");

      // Getters
      LUA->PushCFunction(L_LogiLedGetSdkVersion);
      LUA->SetField(-2, "GetSdkVersion");

      // Zonal
      LUA->PushCFunction(L_LogiLedSetLightingForTargetZone);
      LUA->SetField(-2, "SetLightingForTargetZone");

      // Per-Key
      LUA->PushCFunction(L_LogiLedSaveLightingForKey);
      LUA->SetField(-2, "SaveLightingForKey");
      LUA->PushCFunction(L_LogiLedSetLightingForKey);
      LUA->SetField(-2, "SetLightingForKey");
      LUA->PushCFunction(L_LogiLedRestoreLightingForKey);
      LUA->SetField(-2, "RestoreLightingForKey");
      LUA->PushCFunction(L_LogiLedFlashSingleKey);
      LUA->SetField(-2, "FlashSingleKey");
      LUA->PushCFunction(L_LogiLedPulseSingleKey);
      LUA->SetField(-2, "PulseSingleKey");
      LUA->PushCFunction(L_LogiLedStopEffectsOnKey);
      LUA->SetField(-2, "StopEffectsOnKey");

      // Generic
      LUA->PushCFunction(L_LogiLedSetTargetDevice);
      LUA->SetField(-2, "SetTargetDevice");
      LUA->PushCFunction(L_LogiLedSaveCurrentLighting);
      LUA->SetField(-2, "SaveCurrentLighting");
      LUA->PushCFunction(L_LogiLedSetLightning);
      LUA->SetField(-2, "SetLightning");
      LUA->PushCFunction(L_LogiLedRestoreLighting);
      LUA->SetField(-2, "RestoreLighting");
      LUA->PushCFunction(L_LogiLedFlashLighting);
      LUA->SetField(-2, "FlashLighting");
      LUA->PushCFunction(L_LogiLedPulseLighting);
      LUA->SetField(-2, "PulseLighting");
      LUA->PushCFunction(L_LogiLedStopEffects);
      LUA->SetField(-2, "StopEffects");

      CreateEnumTable(LUA, "KeyName", keyEnum, sizeof(keyEnum) / sizeof(keyEnum[0]));
      CreateEnumTable(LUA, "DeviceType", deviceTypeEnum, sizeof(deviceTypeEnum) / sizeof(deviceTypeEnum[0]));
    LUA->SetField(-2, "Logitech");
  LUA->Pop();
}
