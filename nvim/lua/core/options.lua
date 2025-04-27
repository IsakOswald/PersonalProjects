-- Make sure no more than 10 options are displayed (auto-completions popup)
vim.opt.pumheight = 10
-- Make line numbers default
vim.opt.number = true

-- You can also add relative line numbers, to help with jumping.
vim.opt.relativenumber = true

-- Set nerd fonts (maybe move to options).
vim.g.have_nerd_font = true

-- Enable mouse mode, can be useful for resizing splits for example!
vim.opt.mouse = "a"

-- Don't show the mode, since it's already in the status line [ Should have lualine installed probably ]
vim.opt.showmode = false

-- Enable break indent
vim.opt.breakindent = true

-- Save undo history
vim.opt.undofile = true

-- Case-insensitive searching UNLESS \C or one or more capital letters in the search term
vim.opt.ignorecase = true
vim.opt.smartcase = true

-- Keep signcolumn on by default
vim.opt.signcolumn = "yes"

-- Decrease update time
vim.opt.updatetime = 250

-- Decrease mapped sequence wait time
vim.opt.timeoutlen = 300

-- Configure how new splits should be opened
vim.opt.splitright = true
vim.opt.splitbelow = true

-- Show which line your cursor is on
vim.opt.cursorline = true

vim.opt.clipboard = "unnamedplus" -- Sync clipboard between OS and Neovim. (default: '')

vim.opt.wrap = false -- Display lines as one long line (default: true)

vim.opt.linebreak = true -- Companion to wrap, don't split words (default: false)

vim.opt.autoindent = true -- Copy indent from current line when starting new one (default: true)

vim.opt.shiftwidth = 4 -- The number of spaces inserted for each indentation (default: 8)

vim.opt.tabstop = 4 -- Insert n spaces for a tab (default: 8)

vim.opt.softtabstop = 4 -- Number of spaces that a tab counts for while performing editing operations (default: 0)

vim.opt.expandtab = true -- Convert tabs to spaces (default: false)

vim.opt.smarttab = true

-- Minimal number of screen lines to keep above and below the cursor.
vim.opt.scrolloff = 10

--Fix Cpp indet issue with :: in structs.
-- C++: use Vim’s C-indent and disable colon-triggered re-indent
vim.api.nvim_create_autocmd("FileType", {
	pattern = "cpp",
	callback = function()
		-- Enable C/C++–style indentation
		vim.opt_local.autoindent = true
		vim.opt_local.smartindent = true
		vim.opt_local.cindent = true -- use Vim’s mature C indent :contentReference[oaicite:1]{index=1}

		-- 4-space tabs
		vim.opt_local.shiftwidth = 4
		vim.opt_local.tabstop = 4
		vim.opt_local.softtabstop = 4
		vim.opt_local.expandtab = true

		-- Prevent re-indent when typing ':' (so 'std::' stays indented)
		vim.opt_local.cinkeys:remove(":") -- stops ':' from retriggering indent :contentReference[oaicite:2]{index=2}

		-- Extra safety: never yank indent on '::' global-scope operator
		vim.opt_local.cinoptions:append("L0") -- disable legacy '::' to col 1 rule :contentReference[oaicite:3]{index=3}
	end,
})
