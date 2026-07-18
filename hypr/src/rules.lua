-- WINDOW RULES
hl.window_rule({ match = { workspace = "w[t1]" } , animation = "popin" })

-- WORKSPACE RULES
hl.workspace_rule({ workspace = "r[1-3]", monitor = "eDP-1" })
hl.workspace_rule({ workspace = "s[true]", layout = "master" })
hl.workspace_rule({ workspace = "w[t1]", gaps_out = 30 })


-- LAYER RULES
local to_be_blurred = {
        "waybar",
        "notifications",
        "wofi"
}

for _,target in ipairs(to_be_blurred) do
        hl.layer_rule({ name = target, match = { namespace = target }, blur = true, ignore_alpha = 0.0 })
end
