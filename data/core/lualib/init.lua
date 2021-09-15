print("Initializing core libraries")
package.path = "./data/core/lualib/?.lua"
console = require('console')
serpent = require('serpent')
ui = require('ui')

function reload()
    console.log("Hot reloading")
    package.loaded.console = nil
    package.loaded.init = nil
    package.loaded.serpent = nil
    package.loaded.ui = nil
    require('init')
    console.log("Hot reloading - Complete")
end

print("Loaded!")
