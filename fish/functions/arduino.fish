function arduino --wraps='arduino-ide --enable-features=UseOzonePlatform --ozone-platform=wayland' --description 'alias arduino=arduino-ide --enable-features=UseOzonePlatform --ozone-platform=wayland'
  arduino-ide --enable-features=UseOzonePlatform --ozone-platform=wayland $argv
        
end
