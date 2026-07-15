hl.curve("myBezier", { type = "bezier", points = { {0.25, 0.1}, {0.25, 1} }})
hl.curve("almostLinear", { type = "bezier", points = { {0.5, 0.5}, {0.75, 1} }})

hl.animation({ leaf = "windows",        enabled = true, speed = 4,   bezier = "myBezier", style = "gnomed"})
hl.animation({ leaf = "workspaces",     enabled = true, speed = 1,   bezier = "almostLinear", style = "fade" })
hl.animation({ leaf = "workspacesIn",   enabled = true, speed = 2.3, bezier = "almostLinear", style = "slidevert" })
hl.animation({ leaf = "workspacesOut",  enabled = true, speed = 2.3, bezier = "almostLinear", style = "slidevert" })
