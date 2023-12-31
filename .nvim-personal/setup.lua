local opts = { remap = false, silent = true }

-- Workspace Settings --
-- ================== --
vim.fn.execute(":set nornu")
vim.fn.execute(":set nonumber")
vim.fn.execute(":set signcolumn=no")

-- Running Configuration --
-- ===================== --
function launch_command(command) 
    vim.fn.execute("vs +term\\ "  .. command:gsub("%\\", "\\\\"):gsub(" ", "\\"))
end

vim.keymap.set("n", "\\b", function()
    -- vim.fn.execute(":w")
    launch_command([[cmd\build.bat]])
    vim.fn.execute("wincmd x")
    vim.fn.execute("wincmd l")
end, opts)

vim.keymap.set("n", "<f5>", function()
    -- vim.fn.execute(":w")
    launch_command([[cmd\\build.bat && cmd\run.bat]])
    vim.fn.execute("wincmd x")
    vim.fn.execute("wincmd l")
end, opts)

-- vim.keymap.set("n", "<f6>", function()
--     -- vim.fn.execute(":w")
--     vim.fn.execute("term cmd\\build.bat && cmd\\debug.bat")
-- end, opts)

-- Keyboard Shortcuts --
-- ================== --

vim.keymap.set("n", "<C-\\>", function()
    vim.fn.execute("vs")
end, opts)
vim.keymap.set("n", "<C-S-\\>", function()
    vim.fn.execute("vs")
    vim.fn.execute("wincmd l")
end, opts)
