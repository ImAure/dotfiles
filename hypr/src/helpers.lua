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
H.explorer        = H.terminal .. " yazi"
H.menu            = "wofi --show drun -c ~/.config/wofi/config -s ~/.config/wofi/style.css"
H.menu_bin = "wofi --show  run -c ~/.config/wofi/config -s ~/.config/wofi/style.css"
H.screenshot = "hyprshot -m region --clipboard-only"

-- functions

-- function H.exec(keys, cmd, flags)
--         hl.bind(keys, hl.dsp.exec_cmd(cmd), flags)
-- end

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
H.workspaces_per_monitor = 10

local function get_current_or_special_workspace()
    local special_workspace = hl.get_active_special_workspace()
    if special_workspace == nil then return hl.get_active_workspace() end
    return special_workspace
end

local function contains(list, x)
    for _, item in ipairs(list) do
        if item == x then return true end
    end
    return false
end

local function move_floating(monitor, target_workspace, window, offset, direction)
    local offsets = {
        ["l"] = {-offset,       0},
        ["d"] = {      0,  offset},
        ["u"] = {      0, -offset},
        ["r"] = { offset,       0},
    }

    local current_workspace = get_current_or_special_workspace()
    local scale = monitor.scale or 1.0
    local logical_width = monitor.width / scale
    local logical_height = monitor.height / scale
    local window_width = window.size.x
    local window_height = window.size.y
    local safe_pixels = 35
    local x_min = - window_width + safe_pixels
    local x_max = logical_width - safe_pixels
    local y_min = - window_height + safe_pixels
    local y_max = logical_height - safe_pixels

    if direction == "u" and window.at.y <= y_min then
        hl.dispatch(hl.dsp.window.move({ workspace = target_workspace }))
        if current_workspace == get_current_or_special_workspace() then return end
        hl.dispatch(hl.dsp.window.move({ x = window.at.x,
                                         y = y_max,
                                         relative = false }))
        return
    end
    if direction == "d" and window.at.y >= y_max then
        hl.dispatch(hl.dsp.window.move({ workspace = target_workspace }))
        if current_workspace == get_current_or_special_workspace() then return end
        hl.dispatch(hl.dsp.window.move({ x = window.at.x,
                                         y = y_min,
                                         relative = false }))
        return
    end
    if direction == "l" and window.at.x <= x_min then return end
    if direction == "r" and window.at.x >= x_max then return end

    hl.dispatch(hl.dsp.window.move({ x = offsets[direction][1],
                                     y = offsets[direction][2],
                                     relative = true }))
end

function H.smart_focus(args) return function()
    local direction
    local relative
    if args.direction then direction = args.direction else return end
    if args.relative then relative = args.direction else relative = true end
    local current_window = hl.get_active_window()
    local current_workspace = get_current_or_special_workspace()
    if current_workspace == nil then return end
    if current_workspace.tiled_layout == "scrolling" then
        hl.dispatch(hl.dsp.layout("focus " .. direction))
    else
        hl.dispatch(hl.dsp.focus({ direction = direction }))
    end
    if current_workspace.tiled_layout == "scrolling" then
        local target_workspace
        if relative then target_workspace = { u = "r-1", d = "r+1" }
                    else target_workspace = { u = "e-1", d = "e+1" } end
        if current_window == hl.get_active_window() then
            if contains({ "u", "d" }, direction) then hl.dispatch(hl.dsp.focus({ workspace = target_workspace[direction] })) end
        end
    end
end end

function H.smart_move(args) return function()
    local direction
    local relative
    if args.direction then direction = args.direction else return end
    if args.relative then relative = args.relative else relative = true end
    local current_window = hl.get_active_window()
    local current_workspace = get_current_or_special_workspace()
    local current_monitor = hl.get_active_monitor()
    if current_window == nil or
        current_workspace == nil or
        current_monitor == nil then
        return
    end

    if current_workspace.tiled_layout == "scrolling" then
        local target_workspace
        if relative then target_workspace = { u = "r-1", d = "r+1" }
                    else target_workspace = { u = "e-1", d = "e+1" } end
        if current_window.floating == true then
            move_floating(current_monitor, target_workspace[direction], current_window, 50, direction)
            return
        end
        if contains({ "l", "r" }, direction) then
            hl.dispatch(hl.dsp.window.move({ direction = direction }))
            return
        end
        local opposites = { u = "d", d = "u" }

        if contains({ "u", "d" }, direction) then
            hl.dispatch(hl.dsp.focus({ direction = direction }))
            if current_window == hl.get_active_window() then
                hl.dispatch(hl.dsp.window.move({ workspace = target_workspace[direction], follow = true }))
            else
                hl.dispatch(hl.dsp.focus({ direction = opposites[direction] }))
                hl.dispatch(hl.dsp.window.move({ direction = direction }))
            end
        end
    else
        hl.dispatch(hl.dsp.window.move({ direction = direction, focus = true }))
    end
end end

local function one_function_to_parse_them_all(node, current_modifiers, layout)
    for key, value in pairs(node) do
        if type(value) == "table" and not value.action and not value.options then
            local new_modifiers = current_modifiers == "" and key or (current_modifiers .. " + " .. key)
            one_function_to_parse_them_all(value, new_modifiers, layout)
        elseif type(value) == "table" and value.action then
            local key_combination = current_modifiers == "" and key or (current_modifiers .. " + " .. key)
            local action = value.action
            local options = value.options or {}
            if layout == "GLOBAL" then
                hl.bind(key_combination, action, options)
            else
                hl.bind(key_combination, function()
                    if get_current_or_special_workspace().tiled_layout == string.lower(layout) then
                        if type(action) == "function" then action()
                                                      else hl.dispatch(action) end
                    end
                end, options)
            end
        end
    end
end

function H.and_in_the_darkness_bind_them(tree)
    for layout, binds in pairs(tree) do
        one_function_to_parse_them_all(binds, "", layout)
    end
end

function H.set_environment_variables(tree)
    for variable, value in pairs(tree) do
        hl.env(variable, value)
    end
end

function H.init_split_workspaces(target_monitor)
    local monitors = target_monitor and { target_monitor } or (hl.get_monitors and hl.get_monitors() or {})
    if #monitors == 0 then return end

    local active_mon = hl.get_active_monitor()

    for _, mon in ipairs(monitors) do
        hl.dispatch(hl.dsp.focus({ monitor = mon.name }))
        hl.dispatch(hl.dsp.focus({ workspace = H.split_workspace(1) }))
    end

    if active_mon then
        hl.dispatch(hl.dsp.focus({ monitor = active_mon.name }))
    end
end

function H.split_workspace(n)
    local mon = hl.get_active_monitor()
    local monitor_id = mon and mon.id or 0
    return monitor_id * H.workspaces_per_monitor + n
end

function H.merge_orphaned_windows()
    local clients = hl.get_windows and hl.get_windows() or {}

    for _, client in ipairs(clients) do
        if client.workspace and client.workspace.id > 0 and client.monitor ~= nil then
            local workspace_id = client.workspace.id
            local monitor_id = client.monitor.id

            local expected_min = monitor_id * H.workspaces_per_monitor + 1
            local expected_max = (monitor_id + 1) * H.workspaces_per_monitor

            if workspace_id < expected_min or workspace_id > expected_max then
                local relative_workspace = ((workspace_id - 1) % H.workspaces_per_monitor) + 1
                local target_workspace = monitor_id * H.workspaces_per_monitor + relative_workspace

                hl.dispatch(hl.dsp.window.move({
                    window = client,
                    workspace = target_workspace,
                }))
            end
        end
    end
end

return H
