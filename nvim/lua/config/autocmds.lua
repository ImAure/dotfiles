-- Autocmds are automatically loaded on the VeryLazy event
-- Default autocmds that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/autocmds.lua
--
-- Add any additional autocmds here
-- with `vim.api.nvim_create_autocmd`
--
-- Or remove existing autocmds by their group name (which is prefixed with `lazyvim_` for the defaults)
-- e.g. vim.api.nvim_del_augroup_by_name("lazyvim_wrap_spell")
local augroup = vim.api.nvim_create_augroup("FileTypeIndent", { clear = true })

vim.api.nvim_create_autocmd("FileType", {
        group = augroup,
        pattern = "c",
        callback = function()
                vim.bo.tabstop = 8
                vim.bo.shiftwidth = 8
                vim.bo.softtabstop = 8
                vim.bo.expandtab = true
        end,
})

vim.api.nvim_create_autocmd("FileType", {
        group = augroup,
        pattern = "python",
        callback = function()
                vim.bo.tabstop = 4
                vim.bo.shiftwidth = 4
                vim.bo.softtabstop = 4
                vim.bo.expandtab = true
        end,
})

vim.api.nvim_create_autocmd("FileType", {
        group = augroup,
        pattern = "nix",
        callback = function()
                vim.bo.tabstop = 2
                vim.bo.shiftwidth = 2
                vim.bo.softtabstop = 2
                vim.bo.expandtab = true
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

