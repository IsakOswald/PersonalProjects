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
    "loctvl842/monokai-pro.nvim",
    lazy = false,                    -- load immediately
    priority = 1000,                 -- make sure it's the first colorscheme
    config = function()
        vim.opt.termguicolors = true -- ensure true color is on before anything
        require("monokai-pro").setup({
            filter = "octagon",      -- or "octagon", "machine", etc.
        })
        vim.cmd("colorscheme monokai-pro") -- apply the colorscheme
    end,
}
