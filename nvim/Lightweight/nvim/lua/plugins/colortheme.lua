--return {
-- Change to shaunsingh's Nord theme
--    "shaunsingh/nord.nvim",
--    lazy = false, -- Load the plugin immediately
--    priority = 1000, -- Ensure it's loaded first
--    config = function()
--        -- Set the color scheme to Nord
--        vim.cmd("colorscheme nord")
--    end,
--}

--return {
--    "axvr/photon.vim",
--    lazy = false,
--    priority = 1000,
--    config = function()
--        -- Enable true color support
--        vim.opt.termguicolors = true
--        -- Set the colorscheme to Photon
--        vim.cmd("colorscheme photon")
--    end,
--}

return {
    {
        "rebelot/kanagawa.nvim",
        lazy = false, -- Load immediately
        priority = 1000, -- Load first
        config = function()
            require("kanagawa").setup({
                compile = false, -- Set to true to compile for faster load (optional)
                undercurl = true,
                commentStyle = { italic = true },
                functionStyle = {},
                keywordStyle = { italic = false },
                statementStyle = { bold = true },
                typeStyle = {},
                transparent = false, -- Enable for transparent bg
                dimInactive = false, -- Dim inactive windows
                terminalColors = true,
                theme = "wave", -- Options: "wave", "dragon", "lotus"
                background = {
                    dark = "wave", -- Theme for dark mode
                    light = "lotus", -- Theme for light mode
                },
            })

            vim.cmd("colorscheme kanagawa")
        end,
    },
}
