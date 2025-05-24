return {
	"windwp/nvim-ts-autotag",
	dependencies = { "nvim-treesitter/nvim-treesitter" }, -- Treesitter is required
	config = function()
		require("nvim-ts-autotag").setup({
			filetypes = { "html" },
		})
	end,
}
