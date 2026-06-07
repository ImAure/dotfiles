-- Keymaps are automatically loaded on the VeryLazy event
-- Default keymaps that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/keymaps.lua
-- Add any additional keymaps here
vim.keymap.set({ "i", "t" }, "jk", "<Esc>")
vim.keymap.set({ "i", "t" }, "Jk", "<Esc>")
vim.keymap.set({ "i", "t" }, "JK", "<Esc>")
vim.keymap.set({ "i", "t" }, "jK", "<Esc>")

vim.keymap.set("n", "<leader>tt", ":botright 7split | terminal<CR>")
vim.keymap.set("t", "<Esc>", [[<C-\><C-n>]])

vim.keymap.set("i", "/*", "/*  */<Left><Left><Left>")

vim.keymap.set("n", "<leader>td", function()
        local current = vim.diagnostic.is_enabled()
        vim.diagnostic.enable(not current)
        vim.notify(
                current and "Diagnostics disabled"
                or "Diagnostics enabled"
        )
end, { desc = "Toggle diagnostics" })

vim.keymap.set("n", "h", "<Nop>")
vim.keymap.set("n", "j", "<Nop>")
vim.keymap.set("n", "k", "<Nop>")
vim.keymap.set("n", "l", "<Nop>")
vim.keymap.set("n", "<Left>", "<Nop>")
vim.keymap.set("n", "<Right>", "<Nop>")
vim.keymap.set("n", "<Up>", "<Nop>")
vim.keymap.set("n", "<Down>", "<Nop>")
