require ('settings')
require ('keymaps')

-- Bootstrap lazy.nvim
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not (vim.uv or vim.loop).fs_stat(lazypath) then
  local lazyrepo = "https://github.com/folke/lazy.nvim.git"
  local out = vim.fn.system({ "git", "clone", "--filter=blob:none", "--branch=stable", lazyrepo, lazypath })
  if vim.v.shell_error ~= 0 then
    vim.api.nvim_echo({
      { "Failed to clone lazy.nvim:\n", "ErrorMsg" },
      { out, "WarningMsg" },
      { "\nPress any key to exit..." },
    }, true, {})
    vim.fn.getchar()
    os.exit(1)
  end
end
vim.opt.rtp:prepend(lazypath)

-- Make sure to setup `mapleader` and scope fi `maplocalleader` before
-- loading lazy.nvim so that mappings are correct.
-- This is also a good place to setup other settings (vim.opt)
vim.g.mapleader = " "
vim.g.maplocalleader = "\\"

-- Setup lazy.nvim
require("lazy").setup({
  spec = {
     { "morhetz/gruvbox" },

     --Telescope
         {
    'nvim-telescope/telescope.nvim', tag = '0.1.8',
    -- or                              , branch = '0.1.x',
      dependencies = { 'nvim-lua/plenary.nvim' }
    },
    
    --Tree sitter
    {
    'nvim-treesitter/nvim-treesitter', build = ':TSUpdate'
    },
       --NeoTree

        {   
  "nvim-neo-tree/neo-tree.nvim",
  branch = "v3.x",
  dependencies = {
    "nvim-lua/plenary.nvim",
    "nvim-tree/nvim-web-devicons", -- not strictly required, but recommended
    "MunifTanjim/nui.nvim",
    -- {"3rd/image.nvim", opts = {}}, -- Optional image support in preview window: See `# Preview Mode` for more information
  },
  lazy = false, -- neo-tree will lazily load itself
  ---@module "neo-tree"
  ---@type neotree.Config?

},
    

	

  },
  -- Configure any other settings here. See the documentation for more details.
  -- colorscheme that will be used when installing plugins.
  install = { colorscheme = { "habamax" } },
  -- automatically check for plugin updates
  checker = { enabled = true },
})

--Set color
vim.cmd("colorscheme gruvbox")  -- or replace 'gruvbox' with your chosen color scheme

-- Use telecope 
-- Initialize Telescope
local builtin = require('telescope.builtin')




-- Use Tree sitter.
require'nvim-treesitter.configs'.setup {
  -- Ensure the C++ parser is installed
  ensure_installed = {"cpp", "lua", "python"},

  highlight = {
    enable = true,  -- Enable Treesitter-based syntax highlighting
  },

  indent = {
    enable = true,  -- Enable Treesitter-based indentation
  },

  incremental_selection = {
    enable = true,  -- Enable incremental selection
  },

  auto_install = true,  -- Automatically install missing parsers when entering buffer
}

      
