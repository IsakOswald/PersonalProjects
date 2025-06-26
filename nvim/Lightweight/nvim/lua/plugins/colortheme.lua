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
    "owickstrom/vim-colors-paramount",
    lazy = false,
    priority = 1000,
    config = function()
        vim.opt.termguicolors = true
        vim.cmd("colorscheme paramount")

        -- Override the background to a dark grey (adjust hex as you like)
        vim.api.nvim_set_hl(0, "Normal", { bg = "#1e1e1e" })
    end,
}
