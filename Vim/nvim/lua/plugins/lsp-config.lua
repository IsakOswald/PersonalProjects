return {
	-- Mason for LSP/DAP/formatter installation
	{
		"williamboman/mason.nvim",
		config = function()
			require("mason").setup()
		end,
	},

	-- mason-lspconfig for automatic LSP setup
	{
		"williamboman/mason-lspconfig.nvim",
		config = function()
			require("mason-lspconfig").setup({
				ensure_installed = { "lua_ls", "pyright", "clangd" }, -- Core language servers
				automatic_installation = false,           -- Manual control
			})
		end,
	},

	-- nvim-lspconfig with borderless diagnostics
	{
		"neovim/nvim-lspconfig",
		config = function()
			local lspconfig = require("lspconfig")

			-- Lua LSP configuration
			lspconfig.lua_ls.setup({
				on_attach = function(client, bufnr)
					-- Hover documentation keymap
					vim.keymap.set("n", "K", vim.lsp.buf.hover, {
						buffer = bufnr,
						desc = "Show documentation",
					})
				end,
			})

			-- ===== DIAGNOSTICS CONFIGURATION =====
			vim.opt.updatetime = 250 -- Faster hover trigger

			-- Borderless floating diagnostics
			vim.diagnostic.config({
				virtual_text = false, -- Disable inline diagnostics
				float = {
					border = "none", -- No border
					style = "minimal",
					source = "always", -- Show originating LSP
					header = "", -- No header
					prefix = function(diagnostic)
						-- Nerd Font icons for severity levels
						local icons = {
							[vim.diagnostic.severity.ERROR] = " ", -- Error
							[vim.diagnostic.severity.WARN] = " ", -- Warning
							[vim.diagnostic.severity.INFO] = " ", -- Information
							[vim.diagnostic.severity.HINT] = "󰌶 ", -- Hint
						}
						return icons[diagnostic.severity] or ""
					end,
				},
			})

			-- C++
			lspconfig.clangd.setup({
				on_attach = function(client, bufnr)
					vim.keymap.set("n", "<leader>cr", function()
						local file = vim.fn.expand("%:p")
						vim.cmd(
							"w | term clang++ -std=c++20 "
							.. file
							.. " -o "
							.. file:gsub("%.cpp$", "")
							.. " && "
							.. file:gsub("%.cpp$", "")
						)
						vim.cmd("startinsert")
					end, { buffer = bufnr })
				end,
			})

			-- Python
			lspconfig.pyright.setup({
				on_attach = function(client, bufnr)
					vim.keymap.set("n", "<leader>pr", function()
						vim.cmd("w | term python " .. vim.fn.expand("%:p"))
						vim.cmd("startinsert")
					end, { buffer = bufnr })
				end,
			})
			-- Color scheme for diagnostics
			vim.cmd([[
        " Error (red)
        highlight DiagnosticFloatingError guifg=#FF8080 guibg=#2E1E1E
        " Warning (yellow/orange)
        highlight DiagnosticFloatingWarn  guifg=#FFCC66 guibg=#2E2B1E
        " Info (blue)
        highlight DiagnosticFloatingInfo  guifg=#66B3FF guibg=#1E2E2E
        " Hint (green)
        highlight DiagnosticFloatingHint  guifg=#66FF99 guibg=#1E2E1E
      ]])

			-- Automatic diagnostic popups on hover
			vim.api.nvim_create_autocmd("CursorHold", {
				callback = function()
					local opts = {
						focusable = false,
						border = "none",
						scope = "cursor",
					}
					if #vim.diagnostic.get(0, { lnum = vim.api.nvim_win_get_cursor(0)[1] - 1 }) > 0 then
						vim.diagnostic.open_float(0, opts)
					end
				end,
			})
		end,
	},
}
