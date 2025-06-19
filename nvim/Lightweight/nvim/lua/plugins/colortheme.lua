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
    "tanvirtin/monokai.nvim",
    lazy = false,
    priority = 1000,
    config = function()
        -- Enable true color support
        vim.opt.termguicolors = true

        -- Load the monokai colorscheme
        vim.cmd("colorscheme monokai")
    end,
}
