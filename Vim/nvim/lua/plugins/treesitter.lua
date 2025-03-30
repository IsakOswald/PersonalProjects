return{
  "nvim-treesitter/nvim-treesitter", build = ":TSUpdate",
   --Treesitter
  config = function()
    local config = require("nvim-treesitter.configs")
    config.setup({
      ensure_installed = {"lua", "javascript", "cmake", "dockerfile", "python"},
      highlight = { enable = true },
      indent = { enable = true }
})
  end
  
}


  
  
  
