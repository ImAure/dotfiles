-- Keymaps are automatically loaded on the VeryLazy event
-- Default keymaps that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/keymaps.lua
-- Add any additional keymaps here
vim.keymap.set("i", "jk", "<Esc>")
vim.keymap.set("i", "Jk", "<Esc>")
vim.keymap.set("i", "JK", "<Esc>")
vim.keymap.set("i", "jK", "<Esc>")

vim.keymap.set("i", "/*", "/*  */<Left><Left><Left>")
