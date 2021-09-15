-- CLI variable assigning
local console = {
    screen_buffer = ""
}

function console.write(str)
    console.screen_buffer = console.screen_buffer .. str
end

function console.log(str)
    console.screen_buffer = console.screen_buffer .. str .. "\n"
end

return console