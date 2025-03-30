--Set leader key
vim.g.mapleader = ' '
vim.g.maplocalleadr = ' '
vim.keymap.set('t', '<Esc>', '<C-\\><C-n>', {noremap = true})  -- Escape exits terminal mode
--Disable the spacebar key's deafult behaviour in Normal and Visual mode
vim.keymap.set({ 'n', 'v' }, '<Space>', '<Nop>', { silent = true })

--For conciseness
local opts = {noremap = true, silent = true}

--Save a file with CTRL + w
vim.keymap.set('n', '<C-w>', '<cmd> w <CR>', opts)

--Quit file
vim.keymap.set('n', '<C-q>', '<cmd> q <CR>', opts)

--Delete single character without copying into register
vim.keymap.set('n', 'x', '"_x', opts)

--Navigate between splits easier
vim.keymap.set('n', '<C-k>', ':wincmd k<CR>', opts)
vim.keymap.set('n', '<C-j>', ':wincmd j<CR>', opts)
vim.keymap.set('n', '<C-h>', ':wincmd h<CR>', opts)
vim.keymap.set('n', '<C-l>', ':wincmd l<CR>', opts)

--Stay in visual mode after indent
vim.keymap.set('v', '<', '<gv', opts)
vim.keymap.set('v', '>', '>gv', opts)

--Keep last yanked when pasting
vim.keymap.set('v', 'p', '"-dP', opts)


