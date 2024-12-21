--
-- Example of how to use the Logitech LED SDK to create an ambient light effect
-- that changes the color of the mouse based on the average color of the screen.
--
-- @shockpast
--

pcall(require, "logi")

--
local logi = Logitech
logi.Initialize("gmod_color_sync")
logi.SetTargetDevice(logi.DeviceType.Mouse)

--
local w, h = ScrW(), ScrH()

--
local c = color_black

hook.Add("DrawOverlay", "logi:ColorSync", function()
  local total_r, total_g, total_b = 0, 0, 0
  local count = 0

  render.CapturePixels()

  for i = 0, w - 1 do
    local r, g, b = render.ReadPixel(i, 0)
    total_r = total_r + r
    total_g = total_g + g
    total_b = total_b + b
    count = count + 1

    r, g, b = render.ReadPixel(i, h - 1)
    total_r = total_r + r
    total_g = total_g + g
    total_b = total_b + b
    count = count + 1
  end

  for i = 0, h - 1 do
    local r, g, b = render.ReadPixel(0, i)
    total_r = total_r + r
    total_g = total_g + g
    total_b = total_b + b
    count = count + 1

    r, g, b = render.ReadPixel(w - 1, i)
    total_r = total_r + r
    total_g = total_g + g
    total_b = total_b + b
    count = count + 1
  end

  c = Color(
    math.floor(total_r / count),
    math.floor(total_g / count),
    math.floor(total_b / count)
  )
end)

timer.Create("logi:ColorSync", 0.16, 0, function()
  logi.SetLightning(c)
end)

hook.Add("ShutDown", "logi:ColorSync", function()
  logi.Shutdown()
end)