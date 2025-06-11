--This is used for when we open a function () it tells us the arugments we can use.
return {
	"ray-x/lsp_signature.nvim",
	event = "LspAttach", -- Load when LSP attaches
	config = function()
		require("lsp_signature").setup({
			bind = true,
			handler_opts = {
				border = "rounded",
			},
			hint_enable = false,
		})
	end,
}
