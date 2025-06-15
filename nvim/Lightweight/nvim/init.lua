-- [[ Import from other files ]]
require("core/keymaps")
require("core/options")
require("core/auto-commands")
--
-- [[ Install `lazy.nvim` plugin manager ]]
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not (vim.uv or vim.loop).fs_stat(lazypath) then
    local lazyrepo = "https://github.com/folke/lazy.nvim.git"
    local out = vim.fn.system({ "git", "clone", "--filter=blob:none", "--branch=stable", lazyrepo, lazypath })
    if vim.v.shell_error ~= 0 then
        error("Error cloning lazy.nvim:\n" .. out)
    end
end
vim.opt.rtp:prepend(lazypath)
-- [[ Configure and install plugins ]]
require("lazy").setup({
    require("plugins/colortheme"),
    require("plugins/neotree"),
    require("plugins/lualine"),
    require("plugins/treesitter"),
    require("plugins/telescope"),
    require("plugins/lspconfig"),
    require("plugins/autocomplete"),
    require("plugins/none-ls"),
    require("plugins/dashboard"),
    require("plugins/indent-guide"),
    require("plugins/misc"),
    require("plugins/lsp-argument-hints"),
    require("plugins/insert-scrolloff"),
})
