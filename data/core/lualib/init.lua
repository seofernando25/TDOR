print("Initializing core libraries")
package.path = "./data/core/lualib/?.lua"

console = require('console')
ui = require('ui')
dump = require('inspect')

--Frequently used functions
log = console.log
clear = console.clear

function nb()
    local obj = ui.Panel:New()
    return obj
end

a = ui.Panel:New()
b = ui.Panel:New()
a:AddChild(b)
ui.AddElement(a)

function reload()
    package.loaded.console = nil
    package.loaded.init = nil
    package.loaded.ui = nil
    require('init')
end

print("Loaded!")
