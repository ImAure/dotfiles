#!/bin/bash

CONFIG="${XDG_CONFIG_HOME:-$HOME/.config}"
DOTFILES="$HOME/dotfiles"

REQUIRED_PKGS=(
    waybar
    hyprland
    hyprlock
    hyprpaper
    kitty
    wofi
    cava
    fastfetch
    nvim

    ttf-fira-code
    ttf-firacode-nerd
    otf-font-awesome
)

link() {
    src="$1"
    dst="$2"

    # if destination is already set and is correct, skip
    if [ -L "$dst" ] && [ "$(readlink "$dst")" = "$src" ]; then
        echo "$dst already set and correct"
        return
    fi

    # if destination exist and is wrong, correct it
    if [ -e "$dst" ] || [ -d "$dst" ]; then
        mv "$dst" "$dst.backup.$(date +%s)"
        echo "! Moved existing $dst > backup"
    fi

    # create needed parent folders
    mkdir -p "$(dirname "$dst")"

    # make link
    ln -s "$src" "$dst"
    echo "linked $dst > $src"
}

link "$DOTFILES/hypr" "$CONFIG/hypr"
link "$DOTFILES/kitty" "$CONFIG/kitty"
link "$DOTFILES/waybar" "$CONFIG/waybar"
link "$DOTFILES/nvim" "$CONFIG/nvim"
link "$DOTFILES/fastfetch" "$CONFIG/fastfetch"
link "$DOTFILES/wofi" "$CONFIG/wofi"
link "$DOTFILES/cava" "$CONFIG/cava"
