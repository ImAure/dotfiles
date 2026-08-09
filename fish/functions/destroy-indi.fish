function destroy-indi --wraps='rm -r ~/.indi && killall -q indi' --description 'alias destroy-indi=rm -r ~/.indi && killall -q indi'
    rm -r ~/.indi && killall -q indi $argv
end
