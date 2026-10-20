local H = {}

-- keys
H.mod = "SUPER"
H.lmb = "mouse:272"
H.rmb = "mouse:273"
H.mmb = "mouse:274"

-- apps
H.terminal        = "kitty"
H.emacs           = "emacsclient -c"
H.browser         = "zen-browser --blank-window"
H.browser_recover = "zen-browser"
H.editor          = "nvim"
H.explorer        = "yazi"
H.menu            = "wofi --show drun -c ~/.config/wofi/config -s ~/.config/wofi/style.css"
H.menu_bin = "wofi --show  run -c ~/.config/wofi/config -s ~/.config/wofi/style.css"
H.screenshoy = "hyprshot -m region --clipboard-only"

-- functions

-- function H.exec(keys, cmd, flags)
--         hl.bind(keys, hl.dsp.exec_cmd(cmd), flags)
-- end

function on_layouts(allowed_layouts, action, fallback)
    return function()
        local current_layout = hl.get_active_workspace().tiled_layout
        for _, l in ipairs(allowed_layouts) do
            if current_layout == l then
            end
        end
    end
end

local exec = hl.dsp.exec_cmd

function H.toggle_state_bar()       return exec("pkill waybar || waybar") end
function H.brightness_up(percent)   return exec("brightnessctl set +" .. percent .. "%") end
function H.brightness_down(percent) return exec("brightnessctl set " .. percent .. "%-") end
function H.volume_up(percent)       return exec("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ " .. percent .. "%+") end
function H.volume_down(percent)     return exec("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ ".. percent .. "%-") end
function H.mic_mute()               return exec("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle") end
function H.audio_mute()             return exec("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") end
function H.player_pause_play()      return exec("playerctl play-pause") end
function H.player_next()            return exec("playerctl next") end
function H.player_prev()            return exec("playerctl previous") end
function H.go_to_sleep()            return exec("systemctl sleep") end

function H.smart_focus(dir, ws)
        return function()
                if dir == "m" then
                        hl.dsp.focus({ monitor = ws })
                        return
                end
                local current = hl.get_active_window()
                hl.dispatch(hl.dsp.focus({ direction = dir }))
                if current == hl.get_active_window() then
                        hl.dispatch(hl.dsp.focus{ workspace = ws })
                end
        end
end

function H.smart_move(dir, ws)
    return function()
        local offset = {
            ["l"] = {-50,   0},
            ["d"] = {  0,  50},
            ["u"] = {  0, -50},
            ["r"] = { 50, 0},
        }

        local current = hl.get_active_window()
        if current == nil then return end

        local monitor = hl.get_active_monitor()
        if monitor == nil then return end
        local scale = monitor.scale or 1.0

        local logical_width = monitor.width / scale
        local logical_height = monitor.height / scale

        local window_width = current.size.x
        local window_height = current.size.y


        if current.floating == true then
            local safe_pixels = 30
            local x_min = - window_width + safe_pixels
            local x_max = logical_width - safe_pixels
            local y_min = - window_height + safe_pixels
            local y_max = logical_height - safe_pixels

            if dir == "u" and current.at.y <= y_min then
                hl.dispatch(hl.dsp.window.move({ workspace = ws, follow = true }))
                hl.dispatch(hl.dsp.window.move({ x = current.at.x, y = y_max, relative = false }))
            end
            if dir == "d" and current.at.y >= y_max then
                hl.dispatch(hl.dsp.window.move({ workspace = ws, follow = true }))
                hl.dispatch(hl.dsp.window.move({ x = current.at.x, y = y_min, relative = false }))
            end
            if dir == "l" and current.at.x <= x_min then return end
            if dir == "r" and current.at.x >= x_max then return end

            hl.dispatch(hl.dsp.window.move({ x = offset[dir][1], y = offset[dir][2], relative = true }))
            return
        end

        if dir == "l" then
            hl.dispatch(hl.dsp.layout("consume_or_expel prev"))
            return
        elseif dir == "r" then
            hl.dispatch(hl.dsp.layout("consume_or_expel next"))
            return
        end

        local opposites = { u = "d", d = "u" }
        hl.dispatch(hl.dsp.focus({ direction = dir }))
        if current == hl.get_active_window() then
            hl.dispatch(hl.dsp.window.move({ workspace = ws, follow = true }))
        else
            hl.dispatch(hl.dsp.focus({ direction = opposites[dir] }))
            hl.dispatch(hl.dsp.window.move({ direction = dir }))
        end
    end
end

local function one_function_to_bind_them_all(binds)
    for key, val in binds do
        if key == "SUPER" or key == "SHIFT" or key == "CTRL" or key == "ALT" then
            -- non so cosa sto facendo 
        end
    end


end

function H.do_them_binds(tree)
    for layout, binds in tree do
        if layout == "GLOBAL" then
            one_function_to_bind_them_all(binds)
        end

    end
end

return H
