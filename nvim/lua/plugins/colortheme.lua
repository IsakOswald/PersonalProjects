return {
	-- Change to Mofiqul's Dracula theme
	"Mofiqul/dracula.nvim",
	lazy = false, -- Load the plugin immediately
	priority = 1000, -- Ensure it's loaded first
	config = function()
		-- Set the color scheme to Dracula
		vim.cmd("colorscheme dracula")
	end,
}
