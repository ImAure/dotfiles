for _,target in ipairs({ "waybar", "notifications", "wofi" }) do
        hl.layer_rule({ name = target, match = { namespace = target }, blur = true, ignore_alpha = 0.0 })
end
