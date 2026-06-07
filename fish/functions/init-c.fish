function init-c --wraps='mkdir -p src build bin include && touch src/main.c && touch makefile' --description 'alias init-c=mkdir -p src build bin include && touch src/main.c && touch makefile'
    mkdir -p src build bin include && touch src/main.c && touch makefile $argv
end
