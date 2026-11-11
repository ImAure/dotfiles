local H = require("src.helpers")

local function FREE(_) end
local function RESERVED(_) end

local exec = hl.dsp.exec_cmd
local close = hl.dsp.window.close
local kill = hl.dsp.window.kill
local toggle_fullscreen = hl.dsp.window.fullscreen_state
local function toggle_overview() hl.plugin.overview.toggle() end

BINDS = {
    GLOBAL = {
        -- common keybinds
        XF86AudioRaiseVolume  = { action = H.volume_up(5),       options = { repeating = true, locked = true } },
        XF86AudioLowerVolume  = { action = H.volume_down(5),     options = { repeating = true, locked = true } },
        XF86AudioMute         = { action = H.audio_mute(),       options = { locked = true } },
        XF86AudioMicMute      = { action = H.mic_mute(),         options = { locked = true } },
        XF86MonBrightnessUp   = { action = H.brightness_up(5),   options = { repeating = true, locked = true } },
        XF86MonBrightnessDown = { action = H.brightness_down(5), options = { repeating = true, locked = true } },
        XF86PowerOff          = { action = H.go_to_sleep(),      options = { locked = true } },
        -- common options

        SUPER = {

            GRAVE = { action = hl.dsp.workspace.toggle_special() },

            TAB = { action = hl.dsp.focus({ last = true }) },
            Q = { action = close("activewindow"), options = { repeating = true }},
            W = { action = exec(H.browser) },
            E = { action = exec(H.explorer) },
            R = FREE, -- { action = resize... }, to resize active window (submap -> vim motions)
            T = FREE,

            ESCAPE = { action = exec("hyprlock") },
            A = FREE,
            S = FREE,
            D = { action = exec(H.menu) },
            F = { action = toggle_fullscreen({ internal = 2, client = 0, action = "toggle" }) },
            G = FREE,

            Z = FREE,
            X = FREE,
            C = { action = hl.dsp.window.pseudo({ action = "toggle" })},
            V = RESERVED("scrolling"),
            B = { action = H.toggle_state_bar() },


            Y = FREE,
            U = FREE,
            I = FREE,
            O = { action = toggle_overview },
            P = FREE, -- pin?
            BRACKETLEFT = { action = hl.dsp.focus({ monitor = "-1" })},
            BRACKETRIGHT = { action = hl.dsp.focus({ monitor = "+1" })},
            BACKSLASH = { action = hl.dsp.workspace.toggle_special() },

            H = { action = H.smart_focus({ direction = "l" }),                  options = { repeating = true } },
            J = { action = H.smart_focus({ direction = "d", relative = true }), options = { repeating = true } },
            K = { action = H.smart_focus({ direction = "u", relative = true }), options = { repeating = true } },
            L = { action = H.smart_focus({ direction = "r" }),                  options = { repeating = true } },
            SEMICOLON = FREE,
            APOSTROPHE = FREE,
            RETURN = { action = hl.dsp.exec_cmd(H.terminal), options = { repeating = true } },

            SHIFT = {
                RETURN    = { action = exec(H.emacs) },
                BACKSLASH = { action = hl.dsp.window.move({ workspace = "special" }) },
                GRAVE     = { action = hl.dsp.window.move({ workspace = "special" }) },
                Q         = { action = kill("activewindow") },
                W         = FREE,
                -- E         = { action = toggle_overview() },
                R         = FREE,
                A         = FREE,
                S         = { action = exec(H.screenshot) },
                D         = { action = exec(H.menu_bin) },
                F         = { action = hl.dsp.window.float({ action = "toggle" })},

                H = { action = H.smart_move({ direction = "l" }),                  options = { repeating = true } },
                J = { action = H.smart_move({ direction = "d", relative = true }), options = { repeating = true } },
                K = { action = H.smart_move({ direction = "u", relative = true }), options = { repeating = true } },
                L = { action = H.smart_move({ direction = "r" }),                  options = { repeating = true } },
                BRACKETLEFT = { action = hl.dsp.window.move({ monitor = "-1" })},
                BRACKETRIGHT = { action = hl.dsp.window.move({ monitor = "+1" })},
            }
        }
    },
    SCROLLING = {
        SUPER = {
            V = { action = hl.dsp.layout("colresize +conf") },

            SHIFT = {
                V = { action = hl.dsp.layout("fit visible") }
            }
        }
    },


    MASTER = {
        SUPER = {
            -- Bind utilissimi nativi per il layout Master in Hyprland
            SPACE = { action = hl.dsp.layout("orientationnext") }, -- Gira il master in orizzontale/verticale
            I     = { action = hl.dsp.layout("addmaster") },       -- Aggiunge la finestra corrente allo stack master
            O     = { action = hl.dsp.layout("removemaster") },    -- Rimuove dal master

            SHIFT = {
                RETURN = { action = hl.dsp.layout("swapwithmaster") }, -- Prende la finestra corrente e la sbatte come Master
                M      = { action = hl.dsp.layout("focusmaster") },    -- Sposta il focus immediatamente sulla finestra Master
            }
        }
    }
}

for i = 1, 9 do
    local key = tostring(i)
    BINDS.GLOBAL.SUPER[key] = { action = hl.dsp.focus({ workspace = i }) }
    if not BINDS.GLOBAL.SUPER.SHIFT then BINDS.GLOBAL.SUPER.SHIFT = {} end
    BINDS.GLOBAL.SUPER.SHIFT[key] = { action = hl.dsp.window.move({ workspace = i }) }
end
H.and_in_the_darkness_bind_them(BINDS)

hl.config({
    gestures = {
        -- see https://wiki.hypr.land/Configuring/Gestures
        workspace_swipe_distance = 300, -- 300
        workspace_swipe_invert = true,  -- true
    },
})

hl.gesture({ fingers = 3, direction = "up",    action = H.smart_focus({ direction = "d", relative = true }) })
hl.gesture({ fingers = 3, direction = "down",  action = H.smart_focus({ direction = "u", relative = true }) })
hl.gesture({ fingers = 3, direction = "right", action = H.smart_focus({ direction = "l", relative = true }) })
hl.gesture({ fingers = 3, direction = "left",  action = H.smart_focus({ direction = "r", relative = true }) })
