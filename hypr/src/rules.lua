-- WINDOW RULES



-- WORKSPACE RULES

hl.workspace_rule({ workspace = "r[1-3]", monitor = "eDP-1" })
hl.workspace_rule({ workspace = "s[true]", layout = "master" })

-- LAYER RULES
for _,target in ipairs({ "waybar", "notifications", "wofi" }) do
        hl.layer_rule({ name = target, match = { namespace = target }, blur = true, ignore_alpha = 0.0 })
end
