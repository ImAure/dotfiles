--
-- env = ELECTRON_OZONE_PLATFORM_HINT,wayland
-- env = QT_QPA_PLATFORM,wayland;xcb
-- env = SDL_VIDEODRIVER,wayland
-- env = XCURSOR_SIZE,24
-- env = QT_QPA_PLATFORMTHEME,qt6ct
-- env = HYPRCURSOR_THEME,catppuccin-mocha-rosewater-cursors
-- env = HYPRCURSOR_SIZE,24
hl.env("XDG_CURRENT_DESKTOP", "Hyprland")
hl.env("XDG_SESSION_TYPE", "wayland")
hl.env("XDG_SESSION_DESKTOP", "Hyprland")

hl.env("GDK_SCALE", "2")
hl.env("QT_QPA_PLATFORM", "wayland;xcb")
hl.env("QT_QPA_PLATFORMTHEME", "qt6ct")
hl.env("SDL_VIODEODRIVER", "wayland")
hl.env("HYPRCURSOR_THEME", "catppuccin-mocha-rosewater-cursors")
hl.env("HYPRCURSOR_SIZE", "24")

hl.env("ELECTRON_OZONE_PLATFORM_HINT", "wayland")
-- hl.env("", "")
-- hl.env("", "")
-- hl.env("", "")
-- hl.env("", "")
