function rmt --wraps='trashy put -c always -t auto' --wraps='trashy -c always -t auto put' --description 'alias rmt=trashy -c always -t auto put'
    trashy -c always -t auto put $argv
end
