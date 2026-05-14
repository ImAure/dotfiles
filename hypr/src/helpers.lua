local H = {}

-- keys
H.mod = "SUPER"
H.lmb = "mouse:272"
H.mmb = "mouse:274"
H.audio_up_key   = "XF86AudioRaiseVolume"
H.audio_down_key = "XF86AudioLowerVolume"
H.audio_mute_key = "XF86AudioMute"
H.audio_mic_mute_key = "XF86AudioMicMute"
H.brightness_up_key   = "XF86MonBrightnessUp"
H.brightness_down_key = "XF86MonBrightnessDown"

-- apps
H.terminal = "kitty"
H.browser  = "zen-browser"
H.editor   = "nvim"
H.explorer = "yazi"
H.menu     = "wofi --show drun -c ~/.config/wofi/config -s ~/.config/wofi/style.css"
H.menu_bin = "wofi --show  run -c ~/.config/wofi/config -s ~/.config/wofi/style.css"

-- functions
function H.exec(keys, cmd, flags)
        hl.bind(keys, hl.dsp.exec_cmd(cmd), flags)
end

function H.brightness_up(percent)
        return hl.dsp.exec_cmd("brightnessctl set +" .. percent .. "%")
end

function H.brightness_down(percent)
        return hl.dsp.exec_cmd("brightnessctl set " .. percent .. "%-")
end

function H.volume_up(percent)
        return hl.dsp.exec_cmd("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ " .. percent .. "%+")
end

function H.volume_down(percent)
        return hl.dsp.exec_cmd("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ ".. percent .. "%-")
end

function H.mic_mute()
       return hl.dsp.exec_cmd("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle")
end

function H.audio_mute()
        return hl.dsp.exec_cmd("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle")
end

function H.player_pause_play()
        return hl.dsp.exec_cmd("playerctl play-pause")
end

function H.player_next()
        return hl.dsp.exec_cmd("playerctl next")
end

function H.player_prev()
        return hl.dsp.exec_cmd("playerctl previous")
end

function H.smart_focus(dir, wp)
        return function()
                local before = hl.get_active_window()
                hl.dispatch(hl.dsp.focus({ direction = dir }))
                if before == hl.get_active_window() then
                        hl.dispatch(hl.dsp.focus{ workspace = wp })
                end
        end
end

return H
