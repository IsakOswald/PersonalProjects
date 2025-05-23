return {
    -- Change to shaunsingh's Nord theme
    "shaunsingh/nord.nvim",
    lazy = false, -- Load the plugin immediately
    priority = 1000, -- Ensure it's loaded first
    config = function()
        -- Set the color scheme to Nord
        vim.cmd("colorscheme nord")
    end,
}
