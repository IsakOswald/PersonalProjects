-- Set the number of spaces a tab character represents
vim.cmd("set tabstop=4")

-- Set the number of spaces a soft tab represents (used when pressing <Tab>)
vim.cmd("set softtabstop=4")

-- Set the number of spaces to use for each indentation level
vim.cmd("set shiftwidth=4")

-- Enable relative line numbering (shows line numbers relative to the current line)
vim.cmd("set relativenumber")

-- Enable absolute line numbering (the line number of the current line will be shown)
vim.cmd("set number")

-- Add some line space by setting the 'scrolloff' option to keep 5 lines visible around the cursor
vim.cmd("set scrolloff=5")

-- Disable line wrapping (long lines won't wrap to the next line)
vim.cmd("set nowrap")

vim.opt.clipboard = "unnamedplus"  -- Use system clipboard

vim.api.nvim_create_autocmd({ "CursorHold" }, {
    pattern = "*",
    callback = function()
        for _, winid in pairs(vim.api.nvim_tabpage_list_wins(0)) do
            if vim.api.nvim_win_get_config(winid).zindex then
                return
            end
        end
        vim.diagnostic.open_float({
            scope = "cursor",
            focusable = false,
            close_events = {
                "CursorMoved",
                "CursorMovedI",
                "BufHidden",
                "InsertCharPre",
                "WinLeave",
            },
        })
    end
})

