vim.wo.number = true --Make line numbers default
vim.o.relativenumber = true -- Set relative line numbers
vim.o.clipboard = 'unnamedplus' -- Sync clipboard for nvim and OS
vim.o.wrap = false --Display lines as one long line
vim.o.linebreak = true -- Companion to wrap, dont split words
vim.o.mouse = 'a' --Enable the mouse
vim.o.autoindent = true --Copy indent from current line when creating a new one
vim.o.ignorecase = true -- Case insensitive searching
vim.o.smartcase = true --Smart case
vim.o.shiftwidth = 4 --The number of spaces inserted for each indentation
vim.o.tabstop = 4 --Insert n spaces for a tab
vim.o.softtabstop = 4 --Number of spaces that a tab counts for
vim.o.expandtab = true --Converts tabs to spaces
-- For more use Henry Misc github repo options.lua.
