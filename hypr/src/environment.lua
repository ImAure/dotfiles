local H = require("src.helpers")

local home = os.getenv("HOME")
local xdg_config = home .. "/.config"
local xdg_data = home .. "/.local/share"
local xdg_state = home .. "/.local/state"
local xdg_cache = home .. "/.cache"

local VARIABLES = {
    -- Sessione & Wayland
    XDG_CURRENT_DESKTOP = "Hyprland",
    XDG_SESSION_TYPE = "wayland",
    XDG_SESSION_DESKTOP = "Hyprland",
    GDK_SCALE = "2",
    QT_QPA_PLATFORM = "wayland;xcb",
    QT_QPA_PLATFORMTHEME = "qt6ct",
    SDL_VIDEODRIVER = "wayland",
    HYPRCURSOR_THEME = "catppuccin-mocha-rosewater-cursors",
    HYPRCURSOR_SIZE = "24",
    ELECTRON_OZONE_PLATFORM_HINT = "wayland",

    -- Base XDG
    XDG_CONFIG_HOME = xdg_config,
    XDG_DATA_HOME = xdg_data,
    XDG_STATE_HOME = xdg_state,
    XDG_CACHE_HOME = xdg_cache,

    -- Toolchain & Linguaggi (xdg-ninja)
    RUSTUP_HOME = xdg_data .. "/rustup",
    STACK_XDG = "1",
    NUGET_PACKAGES = xdg_cache .. "/NuGetPackages",
    GRADLE_USER_HOME = xdg_data .. "/gradle",
    _JAVA_OPTIONS = "-Djava.util.prefs.userRoot=" .. xdg_config .. "/java",
    TEXMFVAR = xdg_cache .. "/texlive/texmf-var",
    PYTHON_HISTORY = xdg_state .. "/python_history",

    -- Sistema, Shell & UI (xdg-ninja)
    GTK2_RC_FILES = xdg_config .. "/gtk-2.0/gtkrc",
    GNUPGHOME = xdg_data .. "/gnupg",
    HISTFILE = xdg_state .. "/bash/history",
}

H.set_environment_variables(VARIABLES)
