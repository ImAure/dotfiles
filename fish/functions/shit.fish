function shit --wraps='shutdown 5' --wraps='shutdown 5s' --wraps='shutdown 0' --description 'alias shit=shutdown 0'
    shutdown 0 $argv
end
