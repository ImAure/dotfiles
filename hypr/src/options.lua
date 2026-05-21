local theme = require("themes.catppuccin.mocha")
local accent = theme.rosewater.hex
local accent_alt = theme.maroon.hex
local red = theme.red.hex
local yellow = theme.yellow.hex

hl.config({
        general = {
                border_size     =   1,  -- d: 2
                gaps_in         =   3,
                gaps_out        =  12,  -- d: 20
                float_gaps      =  10,
                gaps_workspaces = -12,

                ["col.active_border"]         = { colors = { accent, accent_alt }, angle = 35 },
                ["col.inactive_border"]       = "#181825" .. "00",
                ["col.nogroup_border"]        = red,
                ["col.nogroup_border_active"] = yellow,

                layout = "scrolling",

                no_focus_fallback       = true,         -- false
                resize_on_border        = true,         -- false
                extend_border_grab_area = 6,            -- 15
                hover_icon_on_border    = true,         -- true
                allow_tearing           = false,        -- false
                resize_corner           = 0,            -- 0
                modal_parent_blocking   = true,         -- true

                locale = "",

                snap = {
                        enabled        = true,  -- false
                        window_gap     = 15,    -- 10
                        monitor_gap    = 4,     -- 10
                        border_overlap = true,
                        respect_gaps   = true,
                },

        },

        scrolling = {
                fullscreen_on_one_column = true,
                column_width             = 0.5,
                focus_fit_method         = 1,           -- 0: center; 1: bring into view
                follow_focus             = true,
                follow_min_visible       = 1,
                explicit_column_widths   = "0.5, 0.95",
                wrap_focus               = false,
                wrap_swapcol             = false,
                direction                = "right"
        },

        group = {
                auto_group = true, -- true
                insert_after_current = true, -- true
                focus_removed_window = true, -- true
                drag_into_group = 1, -- true
                merge_groups_on_groupbar = true,
                merge_floated_into_tiled_on_groupbar = false,
                group_on_movetoworkspace = false,
                -- col.border_active = rgba($rosewaterAlphaff) rgba($flamingoAlphaff) 45deg,

                groupbar = {

                }

        },

        decoration = { -- DONE
                --> window corners
                rounding       = 4,     -- 5
                rounding_power = 5,     -- 2.0
                --> opacity and dimming
                active_opacity     = 1.0,       -- 1.0
                inactive_opacity   = 1.0,       -- 1.0
                fullscreen_opacity = 1.0,       -- 1.0

                dim_modal    = true,    -- true
                dim_inactive = false,   -- false
                dim_strength = 0.15,    -- 0.5
                dim_special  = 0.0,     -- 0.2
                dim_around = 0.0,

                screen_shader = "",
                border_part_of_window = true, -- true

                blur = { -- TO BE REFINED
                        -- backgroun blur
                        enabled = true, -- true

                        size   = 6, -- 8
                        passes = 3, -- 1

                        ignore_opacity    = true,  -- true
                        new_optimizations = true,  -- true
                        xray              = true, -- false

                        -- color correction
                        noise      = 0.0,       -- 0.0117
                        contrast   = 1.0,        -- 0.8916
                        brightness = 1.0,        -- 0.8172
                        vibrancy   = 0.0,        -- 0.1696
                        vibrancy_darkness = 0.0, -- 0.0

                        special = true,-- false

                        popups = true,
                        popups_ignorealpha = 0.05,-- 0.2
                        input_methods = false,
                        input_methods_ignorealpha = 0.05,
                },

                shadow = { -- DONE
                        --> drop shadow
                        enabled       = true,   -- true
                        range         = 0,      -- 4
                        render_power  = 1,      -- 3
                        sharp         = false,  -- false
                        -- ignore_window = true -- true

                        color          = "#f2cdcd00", -- rgba(1a1a1aee)
                        color_inactive = "#11111b00",     -- unset

                        offset = { 0, 0 },
                        scale  = 1.0,
                },

                glow = {
                        enabled = true,
                        range = 0,
                        render_power = 1,
                        color = "#f2cdcd00",
                        color_inactive = "#11111b00",     -- unset
                },

        },

        animations = {
                enabled = true,
                workspace_wraparound = false
        },

        xwayland = {
                force_zero_scaling = true
        }
})
