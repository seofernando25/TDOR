-- CLI variable assigning
local console = {
    screen_buffer = ""
}

function console.write(obj)
    console.screen_buffer = console.screen_buffer .. tostring(obj)
end

function console.log(obj)
    console.screen_buffer = console.screen_buffer .. tostring(obj) .. "\n"
end

function console.clear()
    console.screen_buffer = ""
end

return console