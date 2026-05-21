local H = require("src.helpers")
require("src.plugins")

local TERMINAL = H.terminal
local BROWSER  = H.browser
local BROWSER_RECOVER  = H.browser_recover
local MENU     = H.menu
local MENU_BIN = H.menu_bin

local BRIGHTNESS_UP_KEY   = H.brightness_up_key
local BRIGHTNESS_DOWN_KEY = H.brightness_down_key

local AUDIO_UP_KEY       = H.audio_up_key
local AUDIO_DOWN_KEY     = H.audio_down_key
local AUDIO_MUTE_KEY     = H.audio_mute_key
local AUDIO_MIC_MUTE_KEY = H.audio_mic_mute_key

local MOUSE_LEFT   = H.lmb
local MOUSE_RIGHT  = H.rmb
local MOUSE_MIDDLE = H.mmb

local smart_focus = H.smart_focus

-- ESSENTIAL UTILITIES
hl.bind("SUPER +       + return", hl.dsp.exec_cmd(TERMINAL))
hl.bind("SUPER +       + Q", hl.dsp.window.close("activewindow"))
hl.bind("SUPER + SHIFT + Q", hl.dsp.window.kill("activewindow"))
hl.bind("SUPER +       + D", hl.dsp.exec_cmd(MENU))
hl.bind("SUPER + SHIFT + D", hl.dsp.exec_cmd(MENU_BIN))
hl.bind("SUPER +       + W", hl.dsp.exec_cmd(BROWSER))
hl.bind("SUPER + SHIFT + W", hl.dsp.exec_cmd("~/.local/bin/dm-zen"))
hl.bind("SUPER +       + B", hl.dsp.exec_cmd("pkill waybar || waybar"))
hl.bind("SUPER + CTRL  + S", hl.dsp.exec_cmd("hyprshot -m region --clipboard-only"))
hl.bind("SUPER + CTRL  + L", hl.dsp.exec_cmd("hyprlock"))

-- WORKSPACES & WINDOWS & MOVEMENT
--- move focus
hl.bind("SUPER + H", hl.dsp.layout("focus l"))
hl.bind("SUPER + L", hl.dsp.layout("focus r"))
hl.bind("SUPER + J", smart_focus("d", "r+1"))
hl.bind("SUPER + K", smart_focus("u", "r-1"))

--- move windows
hl.bind("SUPER + SHIFT + H", hl.dsp.layout("consume_or_expel prev"))
hl.bind("SUPER + SHIFT + L", hl.dsp.layout("consume_or_expel next"))
hl.bind("SUPER + SHIFT + J", hl.dsp.window.move({ workspace = "r+1" }))
hl.bind("SUPER + SHIFT + K", hl.dsp.window.move({ workspace = "r-1" }))

--- move columns
hl.bind("SUPER + ALT   + H", hl.dsp.layout("swapcol l"))
hl.bind("SUPER + ALT   + L", hl.dsp.layout("swapcol r"))
-- add here something to move the whole column to another workspace u/d
-- add here something to move the whole column to another workspace u/d

--- specific workspaces
hl.bind("SUPER +       + S", hl.dsp.workspace.toggle_special())
hl.bind("SUPER + SHIFT + S", hl.dsp.window.move({ workspace = "special" }))
for key = 1, 9 do
        hl.bind("SUPER + "         .. key, hl.dsp.focus({ workspace = key }))
        hl.bind("SUPER + SHIFT + " .. key, hl.dsp.window.move({ workspace = key }))
end
-- hl.bind("SUPER +       + 0", hl.dsp.focus({ workspace = more_workspaces() })                 --extra workspaces, when you press 0 ask for a 2-digit number and go to that ws
-- hl.bind("SUPER + SHIFT + 0", hl.dsp.window.move({ workspace = more_workspaces() })

--- column size
hl.bind("SUPER +       + V", hl.dsp.layout("colresize +conf"))
hl.bind("SUPER + SHIFT + V", hl.dsp.layout("fit visible"))
hl.bind("SUPER +       + COMMA",  hl.dsp.layout("colresize -0.02"), { repeating = true })
hl.bind("SUPER +       + PERIOD", hl.dsp.layout("colresize +0.02"), { repeating = true })

--- fullscreen & floating
hl.bind("SUPER +       + F", hl.dsp.window.fullscreen_state({ internal = 2, client = 0, action = "toggle" }))
hl.bind("SUPER + SHIFT + F", hl.dsp.window.float( { action = "toggle" }))
hl.bind("SUPER +       + " .. MOUSE_LEFT, hl.dsp.window.resize())
hl.bind("SUPER + SHIFT + " .. MOUSE_LEFT, hl.dsp.window.drag())


-- -- hl.bind("SUPER + T", hl.plugin.Hyprdrive())
-- hl.bind("SUPER + I", function()
--         hl.exec_cmd("Hyprdrive:toggle")
-- end)

-- OTHER UTILITIES
hl.bind("SUPER + C", hl.dsp.exec_cmd("kitty peaclock"))
hl.bind("SUPER + N", hl.dsp.exec_raw("~/.local/bin/dm-mako"))
hl.bind("SUPER + M", hl.dsp.exec_cmd("~/.local/bin/dm-sunsetr"))

hl.bind(BRIGHTNESS_UP_KEY,   H.brightness_up(5),   { repeating = true, locked = true })
hl.bind(BRIGHTNESS_DOWN_KEY, H.brightness_down(5), { repeating = true, locked = true })

hl.bind(AUDIO_UP_KEY,       H.volume_up(5),   { repeating = true, locked = true })
hl.bind(AUDIO_DOWN_KEY,     H.volume_down(5), { repeating = true, locked = true })
hl.bind(AUDIO_MUTE_KEY,     H.audio_mute(),   { locked = true })
hl.bind(AUDIO_MIC_MUTE_KEY, H.mic_mute(),     { locked = true })

hl.bind("SUPER + " .. AUDIO_MUTE_KEY, H.player_pause_play())
hl.bind("SUPER + " .. AUDIO_UP_KEY,   H.player_next())
hl.bind("SUPER + " .. AUDIO_DOWN_KEY, H.player_prev())



-- hl.bind("SUPER + G", function()
--         local layout = hl.get_active_workspace().tiled_layout
--         hl.notification.create({ text = layout, duration = 1000 })
--         if layout == "scrolling" then
--                 hl.notification.create({ text = "minchia", duration = 1000 })
--         else
--                 hl.notification.create({ text = "no" .. hl.layout, duration = 1000 })
--         end
-- end)

-- GESTURES
--
hl.config({
        gestures = {
                -- see https://wiki.hypr.land/Configuring/Gestures
                workspace_swipe_distance = 300, -- 300
                workspace_swipe_invert = true,  -- true
        },
})

hl.gesture({ fingers = 3, direction = "up",    action = smart_focus("d", "r+1") })
hl.gesture({ fingers = 3, direction = "down",  action = smart_focus("u", "r-1") })
hl.gesture({ fingers = 3, direction = "right", action = function() hl.dispatch(hl.dsp.layout("focus l")) end })
hl.gesture({ fingers = 3, direction = "left",  action = function() hl.dispatch(hl.dsp.layout("focus r")) end })
