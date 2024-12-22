# gmcl_logi

A C++ Garry's Mod module for interfacing with LogiLED SDK.

## Requirements

- Visual Studio 2022
- [LED ILLUMINATION SDK](https://www.logitechg.com/en-us/innovation/developer-lab)
- [garrysmod_common](https://github.com/danielga/garrysmod_common) *(x64 branch)*

## Building

1. Clone the repository
```bash
git clone https://github.com/shockpast/gmcl_logi.git
```

2. Install [garrysmod_common](https://github.com/danielga/garrysmod_common) with x86_64 branch from the dependencies
```bash
git clone --branch x86-64-support-sourcesdk https://github.com/danielga/garrysmod_common development/gmcommon
```

3. Install [LED ILLUMINATION SDK](https://www.logitechg.com/en-us/innovation/developer-lab) from the dependencies

4. Generate the project files
```bash
premake5 vs2022 --gmcommon=development/gmcommon
```

5. Open the solution in Visual Studio 2022 and build with `x64` configuration

## Installation

1. Build the module or download from releases
2. Place `gmcl_logi_win64.dll` in `GarrysMod/garrysmod/lua/bin`
3. Include it in your `.lua` file with `require("logi")` and access it through `Logitech` table.

## Functions

[FUNCTIONS.md](FUNCTIONS.md)

## Examples

You can view our examples in [examples/](examples/)
