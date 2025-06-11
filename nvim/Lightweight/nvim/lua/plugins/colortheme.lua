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
--    "shaunsingh/nord.nvim",
--    lazy = false,
--    priority = 1000,
--    config = function()
--        -- Nord theme configuration
--        vim.g.nord_contrast = true
--        vim.g.nord_disable_background = true -- enable transparency
--        vim.g.nord_bold = true
--        vim.g.nord_italic = true

-- Apply the theme
--        require("nord").set()
--    end,
--}

--NOTE: Remember to toggle transparency in ITERM2 (can also se blur). Make sure to set it for fullscreen too.

return {
    "axvr/photon.vim",
    lazy = false,
    priority = 1000,
    config = function()
        -- Enable true color support
        vim.opt.termguicolors = true
        -- Set the colorscheme to Photon
        vim.cmd("colorscheme photon")
    end,
}
