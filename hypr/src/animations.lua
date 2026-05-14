hl.curve("myBezier", { type = "bezier", points = { {0.25, 0.1}, {0.25, 1} }})

hl.animation({ leaf = "windows", enabled = true, speed = 4, bezier = "myBezier", style = "gnomed"})
hl.animation({ leaf = "workspaces", enabled = true, speed = 4, bezier = "myBezier", style = "slidevert" })
