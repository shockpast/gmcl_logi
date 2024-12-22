--
-- This example will make your Logitech keyboard light up in a rainbow pattern.
--
-- @shockpast
--

pcall(require, "logi")

local logi = Logitech

logi.Initialize("gmod_rainbow")

timer.Create("logi:Rainbow", 0.16, 0, function()
  logi.SetLightning(HSVToColor((CurTime() * 100) % 360, 1, 1))
end)

hook.Add("ShutDown", "logi:Rainbow", function()
  logi.Shutdown()
end)