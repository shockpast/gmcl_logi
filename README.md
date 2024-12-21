# gmcl_logi

A C++ Garry's Mod module for interfacing with LogiLED SDK *(tested on G102, and seems to be very buggy...)*

## Requirements

- Visual Studio 2022
- [Logitech SDK](https://www.logitechg.com/en-us/innovation/developer-lab)
- [garrysmod_common](https://github.com/danielga/garrysmod_common) *(x64 branch)*

## Building

1. Clone
```bash
git clone https://github.com/yourusername/gmcl_logi.git
```

2. Install LogiLED SDK from the dependencies

3. Generate the project files:
```bash
premake5 vs2022
```

4. Open the solution in Visual Studio 2022 and build

## Installation

1. Build the module or download from releases
2. Place `gmcl_logi_win64.dll` in `GarrysMod/garrysmod/lua/bin`

## Usage

```lua
require("logi")
local logi = Logitech

logi.Initialize("gmod")
logi.SetTargetDevice(logi.DeviceType.Mouse)
logi.SetLightning(Color(255, 0, 0))

timer.Simple(5, function() logi.Shutdown() end)
```
