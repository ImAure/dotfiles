set --erase fish_greeting

if status is-interactive
    # Commands to run in interactive sessions can go here
    # fet.sh
    fastfetch
end

set -q GHCUP_INSTALL_BASE_PREFIX[1]; or set GHCUP_INSTALL_BASE_PREFIX $HOME ; set -gx PATH $HOME/.cabal/bin /home/Aurelio/.ghcup/bin $PATH # ghcup-env

set -g fish_key_bindings fish_vi_key_bindings
