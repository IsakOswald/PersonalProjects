return {
    {
        -- Highlight, edit, and navigate code
        "nvim-treesitter/nvim-treesitter",
        build = ":TSUpdate",
        main = "nvim-treesitter.configs",
        opts = {
            ensure_installed = {
                "c",
                "cpp",
                "lua",
                "luadoc",
                "vim",
                "vimdoc",
                "query", -- for Treesitter queries, used internally

                -- Web development languages
                "html", -- HTML for markup
                "css", -- CSS stylesheets
                "javascript", -- JavaScript for web scripting

                -- Additional useful language
                "python", -- Python for backend/dev work + other
                "go",
            },
            auto_install = false, -- no need to auto-install stuff you don't want
            highlight = {
                enable = true,
                additional_vim_regex_highlighting = false,
            },
            indent = {
                enable = true,
                disable = { "c", "cpp", "html", "javascript", "go" },
            },
        },
    },
}
