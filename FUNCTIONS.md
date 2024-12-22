# Logitech LED SDK Functions

## Initialization Functions

### Initialize(name)
- **Arguments**: `string name` - Name of your application
- **Returns**: `boolean` - Success status
- **Description**: Initializes the Logitech LED SDK with the specified application name

### Shutdown()
- **Returns**: None
- **Description**: Shuts down the Logitech LED SDK and releases resources

## Generic Lighting Functions

### SetTargetDevice(deviceType)
- **Arguments**: `number deviceType` - Device type from DeviceType enum
- **Returns**: `boolean` - Success status
- **Description**: Sets which device type to target for lighting effects

### SaveCurrentLighting()
- **Returns**: `boolean` - Success status
- **Description**: Saves current lighting state for later restoration

### SetLightning(color)
- **Arguments**: `Color color` - RGB color table {r, g, b}
- **Returns**: `boolean` - Success status
- **Description**: Sets lighting for the targeted device

### RestoreLighting()
- **Returns**: `boolean` - Success status
- **Description**: Restores previously saved lighting state

### FlashLighting(color, duration, interval)
- **Arguments**:
  - `Color color` - RGB color table {r, g, b}
  - `number duration` - Effect duration in milliseconds
  - `number interval` - Flash interval in milliseconds
- **Returns**: `boolean` - Success status
- **Description**: Creates a flashing effect on targeted device

### PulseLighting(color, duration, interval)
- **Arguments**:
  - `Color color` - RGB color table {r, g, b}
  - `number duration` - Effect duration in milliseconds
  - `number interval` - Pulse interval in milliseconds
- **Returns**: `boolean` - Success status
- **Description**: Creates a pulsing effect on targeted device

### StopEffects()
- **Returns**: `boolean` - Success status
- **Description**: Stops all running effects

## Per-Key Functions

### SaveLightingForKey(keyName)
- **Arguments**: `number keyName` - Key from KeyName enum
- **Returns**: `boolean` - Success status
- **Description**: Saves lighting state for specific key

### SetLightingForKey(keyName, color)
- **Arguments**:
  - `number keyName` - Key from KeyName enum
  - `Color color` - RGB color table {r, g, b}
- **Returns**: `boolean` - Success status
- **Description**: Sets lighting for specific key

### RestoreLightingForKey(keyName)
- **Arguments**: `number keyName` - Key from KeyName enum
- **Returns**: `boolean` - Success status
- **Description**: Restores saved lighting state for specific key

### FlashSingleKey(keyName, color, duration, interval)
- **Arguments**:
  - `number keyName` - Key from KeyName enum
  - `Color color` - RGB color table {r, g, b}
  - `number duration` - Effect duration in milliseconds
  - `number interval` - Flash interval in milliseconds
- **Returns**: `boolean` - Success status
- **Description**: Creates a flashing effect on specific key

### PulseSingleKey(keyName, startColor, finishColor, duration, isInfinite)
- **Arguments**:
  - `number keyName` - Key from KeyName enum
  - `Color startColor` - Starting RGB color table {r, g, b}
  - `Color finishColor` - Ending RGB color table {r, g, b}
  - `number duration` - Effect duration in milliseconds
  - `boolean isInfinite` - Whether effect should loop indefinitely
- **Returns**: `boolean` - Success status
- **Description**: Creates a pulsing effect on specific key

### StopEffectsOnKey(keyName)
- **Arguments**: `number keyName` - Key from KeyName enum
- **Returns**: `boolean` - Success status
- **Description**: Stops all effects on specific key

## Utility Functions

### GetSdkVersion()
- **Returns**: `string` - SDK version in format "major.minor.build"
- **Description**: Returns the current SDK version

## Zonal Functions

### SetLightingForTargetZone(deviceType, zone, color)
> [!WARNING]
> It doesn't work at the moment, and spews out the error about number.

- **Arguments**:
  - `number deviceType` - Device type from DeviceType enum
  - `number zone` - Zone identifier
  - `Color color` - RGB color table {r, g, b}
- **Returns**: `boolean` - Success status
- **Description**: Sets lighting for specific zone on targeted device