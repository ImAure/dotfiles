local H = require("src.helpers")
local P = require("src.peripherals")
require("src.plugins")

local TERMINAL = H.terminal
local EMACS    = H.emacs
local BROWSER  = H.browser
local BROWSER_RECOVER  = H.browser_recover
local MENU     = H.menu
local MENU_BIN = H.menu_bin

local BRIGHTNESS_UP_KEY   = P.brightness_up_key
local BRIGHTNESS_DOWN_KEY = P.brightness_down_key

local AUDIO_UP_KEY       = P.audio_up_key
local AUDIO_DOWN_KEY     = P.audio_down_key
local AUDIO_MUTE_KEY     = P.audio_mute_key
local AUDIO_MIC_MUTE_KEY = P.audio_mic_mute_key
local POWER_KEY      = P.power_key

local MOUSE_LEFT   = P.mouse_left_button
local MOUSE_RIGHT  = P.mouse_right_button
local MOUSE_MIDDLE = P.mouse_middle_button
local MOUSE_UP     = P.mouse_scroll_up
local MOUSE_DOWN   = P.mouse_scroll_down

local smart_focus = H.smart_focus
local smart_move = H.smart_move

-- hl.bind("SUPER + P", function()
--         if hl.get_active_workspace().tiled_layout == "master" then
--             return hl.exec_cmd("hyprctl notify 0 5000 'rgb(ffffff)' ' ciao '")
--         end
--     end)

hl.bind("SUPER + P", function()
    local current_workspace = hl.get_active_workspace()
    local special_workspace = hl.get_active_special_workspace()
    if not (special_workspace == nil) then current_workspace = special_workspace end
    if current_workspace == nil then return end
    local layout = current_workspace.tiled_layout

    hl.exec_cmd("notify-send " .. layout)
    if current_workspace.special then hl.exec_cmd("notify-send special") end
end)


-- ESSENTIAL UTILITIES
hl.bind("SUPER +       + RETURN", hl.dsp.exec_cmd(TERMINAL))
hl.bind("SUPER + SEMICOLON", hl.dsp.exec_cmd('hyprctl notify 0 5000 "rgb(ffffff)" ";"'), { repeating = true })
hl.bind("SUPER + CTRL  + RETURN", hl.dsp.exec_cmd(TERMINAL))
hl.bind("SUPER + SHIFT + return", hl.dsp.exec_cmd(EMACS))
hl.bind("SUPER +       + Q", hl.dsp.window.close("activewindow"))
hl.bind("SUPER + SHIFT + Q", hl.dsp.window.kill("activewindow"))
hl.bind("SUPER +       + D", hl.dsp.exec_cmd(MENU))
hl.bind("SUPER + SHIFT + D", hl.dsp.exec_cmd(MENU_BIN))
hl.bind("SUPER +       + W", hl.dsp.exec_cmd(BROWSER))
hl.bind("SUPER + SHIFT + W", hl.dsp.exec_cmd("~/.local/bin/dm-zen"))
hl.bind("SUPER +       + B", hl.dsp.exec_cmd("pkill waybar || waybar"))
hl.bind("SUPER + CTRL  + S", hl.dsp.exec_cmd("hyprshot -m region --clipboard-only"))
hl.bind("SUPER + TAB + ", function() hl.plugin.overview.toggle() end)
hl.bind("SUPER + ESCAPE", hl.dsp.exec_cmd("hyprlock"))

-- WORKSPACES & WINDOWS & MOVEMENT
--- move focus
hl.bind("SUPER + H", smart_focus({ direction = "l", relative = true }), { repeating = true })
hl.bind("SUPER + L", smart_focus({ direction = "r", relative = true }), { repeating = true })
hl.bind("SUPER + J", smart_focus({ direction = "d", relative = true }), { repeating = true })
hl.bind("SUPER + K", smart_focus({ direction = "u", relative = true }), { repeating = true })
-- hl.bind("SUPER + CTRL + H", smart_focus("m", "+1")) -- "m" is a custom value, short for monitor
-- hl.bind("SUPER + CTRL + L", smart_focus("m", "-1"))

--- move windows
-- hl.bind("SUPER + SHIFT + H", hl.dsp.layout("consume_or_expel prev"), { repeating = true })
-- hl.bind("SUPER + SHIFT + L", hl.dsp.layout("consume_or_expel next"), { repeating = true })
-- hl.bind("SUPER + SHIFT + J", hl.dsp.window.move({ workspace = "r+1" }))
-- hl.bind("SUPER + SHIFT + K", hl.dsp.window.move({ workspace = "r-1" }))

hl.bind("SUPER + SHIFT + H", smart_move({ direction = "l", relative = true }), { repeating = true })
hl.bind("SUPER + SHIFT + L", smart_move({ direction = "r", relative = true }), { repeating = true })
hl.bind("SUPER + SHIFT + J", smart_move({ direction = "d", relative = true }), { repeating = true })
hl.bind("SUPER + SHIFT + K", smart_move({ direction = "u", relative = true }), { repeating = true })

hl.bind("SUPER + SHIFT + CTRL + H", hl.dsp.window.move({ monitor = "+1" }))
hl.bind("SUPER + SHIFT + CTRL + L", hl.dsp.window.move({ monitor = "-1" }))

--- change monitor

--- move columns
hl.bind("SUPER + ALT   + H", hl.dsp.layout("swapcol l"))
hl.bind("SUPER + ALT   + L", hl.dsp.layout("swapcol r"))
-- add here something to move the whole column to another workspace u/d
-- add here something to move the whole column to another workspace u/d

--- MOUSE
hl.bind("SUPER + " .. MOUSE_UP,   smart_focus({ direction = "d", relative = true }))
hl.bind("SUPER + " .. MOUSE_DOWN, smart_focus({ direction = "u", relative = true }))
hl.bind("SUPER + SHIFT + " .. MOUSE_UP,   smart_move({ direction = "d", relative = "r+1" }))
hl.bind("SUPER + SHIFT + " .. MOUSE_DOWN, smart_move("u", "r-1"))

--- specific workspaces
hl.bind("SUPER +       + BACKSLASH", hl.dsp.workspace.toggle_special())
hl.bind("SUPER + SHIFT + BACKSLASH", hl.dsp.window.move({ workspace = "special" }))
hl.bind("SUPER +       + GRAVE", hl.dsp.workspace.toggle_special())
hl.bind("SUPER + SHIFT + GRAVE", hl.dsp.window.move({ workspace = "special" }))
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
-- hl.bind("SUPER +       + F", hl.dsp.window.fullscreen_state({ internal = 2, client = 0, action = "toggle", layout_aware = false }))
hl.bind("SUPER +       + F", hl.dsp.window.fullscreen({ mode = "fullscreen", action = "toggle", layout_aware = "true" }))
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
hl.bind(POWER_KEY, H.go_to_sleep(),     { locked = true })

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

hl.config({
        gestures = {
                -- see https://wiki.hypr.land/Configuring/Gestures
                workspace_swipe_distance = 300, -- 300
                workspace_swipe_invert = true,  -- true
        },
})

hl.gesture({ fingers = 3, direction = "up",    action = smart_focus({ direction = "d", relative = true }) })
hl.gesture({ fingers = 3, direction = "down",  action = smart_focus({ direction = "u", relative = true }) })
hl.gesture({ fingers = 3, direction = "right", action = smart_focus({ direction = "l", relative = true }) })
hl.gesture({ fingers = 3, direction = "left",  action = smart_focus({ direction = "r", relative = true }) })
