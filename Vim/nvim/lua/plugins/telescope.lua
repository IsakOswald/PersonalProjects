--Telescope
return {
	{
    'nvim-telescope/telescope.nvim', tag = '0.1.6',
    dependencies = { 'nvim-lua/plenary.nvim' },

  config = function()

  --Telescope
    local builtin = require('telescope.builtin')
  -- Leader search files
    vim.keymap.set('n', '<leader>sf', builtin.find_files, {})
  -- Leader search string
    vim.keymap.set('n', '<leader>ss', builtin.live_grep, {})

  end
	},
	{
		'nvim-telescope/telescope-ui-select.nvim',
		config = function()
			require("telescope").setup ({
			  extensions = {
				["ui-select"] = {
				  require("telescope.themes").get_dropdown {
				  }
				}
			  }
			})
			require("telescope").load_extension("ui-select")
		end
	},

  }


