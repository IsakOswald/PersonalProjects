return {
    "nvim-neo-tree/neo-tree.nvim",
    branch = "v3.x",
    dependencies = {
        "nvim-lua/plenary.nvim",
        "nvim-tree/nvim-web-devicons", -- not strictly required, but recommended
        "MunifTanjim/nui.nvim",
    },
    config = function()
        -- Your configuration options go here
        require("neo-tree").setup({
            indent = {
                indent_size = 2,
                padding = 1, -- extra padding on left-hand side
                -- indent guides
                with_markers = true,
                indent_marker = '│',
                last_indent_marker = '└',
                highlight = 'NeoTreeIndentMarker',
                -- expander config, needed for nesting files
                with_expanders = nil, -- if nil and file nesting is enabled, will enable expanders
                expander_collapsed = '',
                expander_expanded = '',
                expander_highlight = 'NeoTreeExpander',
            },
        })

        -- Key mappings
        vim.cmd [[nnoremap \ :Neotree reveal<cr>]]
        vim.keymap.set('n', '<leader>n', ':Neotree toggle position=left<CR>', { noremap = true, silent = true }) -- focus file explorer
    end,
}

