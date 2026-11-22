
H = require("src.helpers")

hl.on("hyprland.start", function()
    for _, command in ipairs({
        "sudo systemctl start --now tlp bluetooth keyd",
        "hyprpaper",
        -- "awww-daemon -l background",
        "WALPIPER_PORTAL=hyprland wallpiperd",
        "hyprpm reload -nn && hyprctl dismissnotify",
        "dbus-update-activation-environment --systemd WAYLAND_DISPLAY XDG_CURRENT_DESKTOP",
        "mako",
        "makoctl mode -s default",
        "nm-applet",
        "sunsetr",
        "hypridle",
        "swayosd-server",
        "emacs --daemon"
    }) do
        hl.exec_cmd(command)
    end

    H.init_split_workspaces()
end)

hl.on("monitor.added", function(monitor) H.init_split_workspaces(monitor) end)
hl.on("monitor.removed", function() H.merge_orphaned_window() end)
