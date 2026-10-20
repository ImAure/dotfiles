local H = require("src.helpers")

local function FREE(_) end
local function RESERVED(_) end

local exec = hl.dsp.exec_cmd
local close = hl.dsp.window.close
local kill = hl.dsp.window.kill
local toggle_fullscreen = hl.dsp.window.fullscreen_state
local function toggle_overview() hl.plugin.overview.toggle() end

local BINDINGS = {}
BINDINGS.GLOBAL.SUPER.H.options.repeating = true
BINDINGS.GLOBAL.SUPER.J.options.repeating = true
BINDINGS.GLOBAL.SUPER.K.options.repeating = true
BINDINGS.GLOBAL.SUPER.L.options.repeating = true

BINDINGS = {
    GLOBAL = {
        -- common keybinds
        XF86AudioRaiseVolume  = { action = H.volume_up(5),   options = { repeating = true, locked = true } },
        XF86AudioLowerVolume  = { action = H.volume_down(5), options = { repeating = true, locked = true } },
        XF86AudioMute         = { action = H.audio_mute(),   options = { locked = true } },
        XF86AudioMicMute      = { action = H.mic_mute(),     options = { locked = true } },
        XF86MonBrightnessUp   = { action = H.brightness_up(5),   options = { repeating = true, locked = true } },
        XF86MonBrightnessDown = { action = H.brightness_down(5), options = { repeating = true, locked = true } },
        XF86PowerOff          = { action = H.go_to_sleep(), options = { locked = true } },
        -- common options

        SUPER = {
            RETURN = { action = exec(H.terminal) },
            BACKSLASH = { action = hl.dsp.workspace.toggle_special() },

            Q = { action = close("activewindow") },
            W = { action = exec(H.browser) },
            E = { action = exec(H.explorer) },
            R = FREE, -- { action = resize... }, to resize active window (submap -> vim motions)
            T = FREE,

            A = FREE,
            S = FREE,
            D = { action = exec(H.menu) },
            F = { action = toggle_fullscreen({ internal = 2, client = 0, action = "toggle" }) },
            G = FREE,

            Z = FREE,
            X = FREE,
            C = FREE,
            V = RESERVED("scrolling"),
            B = { action = H.toggle_state_bar() },

            ESCAPE = { action = exec("hyprlock") },

            Y = FREE,
            U = FREE,
            I = FREE,
            O = FREE,
            P = FREE, -- pin?

            H = { action = H.smart_focus("l", "r") },
            J = { action = H.smart_focus("d", "r+1") },
            K = { action = H.smart_focus("u", "r-1") },
            L = { action = H.smart_focus("r", "r") },
            SEMICOLON = FREE,

            SHIFT = {
                RETURN = { action = exec(H.emacs) },
                Q      = { action = kill("activewindow") },
                W      = FREE,
                E      = { action = toggle_overview() },
                R      = FREE,
                A      = FREE,
                S      = { action = exec(H.screenshot) },
                D      = { exec(H.menu_bin) },
                F      = RESERVED("scrolling floating"),

                H = { action = H.smart_move("l", "r"),   options = { repeating = true } },
                J = { action = H.smart_move("d", "r+1") },
                K = { action = H.smart_move("u", "r-1") },
                L = { action = H.smart_move("r", "r"),   options = { repeating = true } },
            }
        }
    },
    SCROLLING = {},

    MASTER = {},
}


