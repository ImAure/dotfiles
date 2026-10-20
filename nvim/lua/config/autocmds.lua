-- Autocmds are automatically loaded on the VeryLazy event
-- Default autocmds that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/autocmds.lua
--
-- Add any additional autocmds here
-- with `vim.api.nvim_create_autocmd`
--
-- Or remove existing autocmds by their group name (which is prefixed with `lazyvim_` for the defaults)
-- e.g. vim.api.nvim_del_augroup_by_name("lazyvim_wrap_spell")
local augroup = vim.api.nvim_create_augroup("FileTypeIndent", { clear = true })

local function set_tab_to(n)
    vim.bo.tabstop = n
    vim.bo.shiftwidth = n
    vim.bo.softtabstop = n
    vim.bo.expandtab = true
end

vim.api.nvim_create_autocmd("FileType", {
    group = augroup,
    pattern = "c",
    callback = function()
        set_tab_to(8)
    end,
})

vim.api.nvim_create_autocmd("FileType", {
    group = augroup,
    pattern = "tex",
    callback = function(args)
        local filename = vim.api.nvim_buf_get_name(args.buf)
        local ext = vim.fn.fnamemodify(filename, ":e")
        if ext == "cls" or ext == "sty" or ext == "def" then
            set_tab_to(2)
        else
            set_tab_to(4)
        end
    end
})

vim.api.nvim_create_autocmd("FileType", {
    group = augroup,
    pattern = "python",
    callback = function()
        set_tab_to(4)
    end,
})

vim.api.nvim_create_autocmd("FileType", {
    group = augroup,
    pattern = "nix",
    callback = function()
        set_tab_to(2)
    end,
})



-- vim.api.nvim_create_autocmd("User", {
--     pattern = "VeryLazy",
--     callback = function()
--         for _, group in ipairs({
--             "Normal", "NormalNC", "NormalFloat", "FloatBorder",
--             "SignColumn", "MsgArea", "TelescopeNormal", "TelescopeBorder",
--             "Pmenu", "PmenuSel", "StatusLine", "NeoTreeNormal", "NeoTreeNormalNC",
--         }) do
--             vim.api.nvim_set_hl(0, group, { bg = "none" })
--         end
--     end,
-- })

