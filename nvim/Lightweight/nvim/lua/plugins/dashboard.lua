return {
	"goolord/alpha-nvim",
	dependencies = {
		"nvim-tree/nvim-web-devicons",
	},

	config = function()
		local alpha = require("alpha")
		local dashboard = require("alpha.themes.startify")

		dashboard.section.header.val = {
			[[ ________       ___   ___      ___  __         ___    ___ ]],
			[[|\   ____\     |\  \ |\  \    |\  \|\  \      |\  \  /  /|]],
			[[\ \  \___|_    \ \  \\_\  \   \ \  \/  /|_    \ \  \/  / /]],
			[[ \ \_____  \    \ \______  \   \ \   ___  \    \ \    / / ]],
			[[  \|____|\  \    \|_____|\  \   \ \  \\ \  \    \/  /  /  ]],
			[[    ____\_\  \          \ \__\   \ \__\\ \__\ __/  / /    ]],
			[[   |\_________\          \|__|    \|__| \|__||\___/ /     ]],
			[[   \|_________|                              \|___|/      ]],
		}
		alpha.setup(dashboard.opts)
	end,
}
