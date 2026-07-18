hl.curve("myBezier", { type = "bezier", points = { {0.25, 0.1}, {0.25, 1} }})
hl.curve("almostLinear", { type = "bezier", points = { {0.5, 0.5}, {0.75, 1} }})

local default_movement = "almostLinear"
local default_color    = "myBezier"

-- WINDOWS
hl.animation({ leaf = "windows",     enabled = true, speed = 2.5, bezier = default_movement, style = "gnomed" })
hl.animation({ leaf = "windowsIn",   enabled = true, speed = 2.5, bezier = default_movement, style = "slide" })
hl.animation({ leaf = "windowsOut",  enabled = true, speed = 2.5, bezier = default_movement, style = "slide" })
hl.animation({ leaf = "windowsMove", enabled = true, speed = 2.5, bezier = default_movement, style = "slide" })

-- WORKSPACES
hl.animation({ leaf = "workspaces",       enabled = true, speed = 1,   bezier = default_movement, style = "fade" })
hl.animation({ leaf = "workspacesIn",     enabled = true, speed = 2.5, bezier = default_movement, style = "slidevert" })
hl.animation({ leaf = "workspacesOut",    enabled = true, speed = 2.5, bezier = default_movement, style = "slidevert" })
hl.animation({ leaf = "specialWorkspace", enabled = true, speed = 2.5, bezier = default_movement, style = "slidefadevert" })

-- COLORS
hl.animation({ leaf = "border",      enabled = true, speed = 3.0, bezier = default_color })
hl.animation({ leaf = "borderangle", enabled = true, speed = 100, bezier = default_color, style = "loop"})
