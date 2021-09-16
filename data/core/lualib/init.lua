print("Initializing core libraries")
package.path = "./data/core/lualib/?.lua"

console = require('console')
ui = require('ui')
dump = require('inspect')


--Frequently used functions
log = console.log
clear = console.clear

root = {
    x = 100,
    y = 100,
    w = 50,
    h = 80,
    --dir = 1,
    children = {
        {
            text = "Test",
            color = { r = 200, g = 244, b = 10 },
            w = 50,
            h = 50,
        },
        {
            color = { r = 144, g = 255, b = 0 },
            w = 25,
            h = 25
        }
    }
}

function draw_child(child, parent, offset)
    child.children = child.children or {}
    local x = child.x or 0
    local y = child.y or 0
    -- If w or h is not specified
    -- we try to calculate the remaining space left
    local w = child.w or offset.w
    local h = child.h or offset.h
    local col = child.color or { r = 0, g = 0, b = 0, a = 255 }
    local trans = { x = x + offset.x, y = y + offset.y, w = w, h = h }

    draw_rect(trans.x, trans.y, trans.w, trans.h, col.r, col.g, col.b, col.a or 255)

    if child.text ~= nil then
        local text_r = 255
        if col.r > 144 then
            text_r = 0
        end

        local text_g = 255
        if col.g > 144 then
            text_g = 0
        end

        local text_b = 255
        if col.b > 144 then
            text_b = 0
        end

        -- TODO Can we do line wrapping?
        draw_text(tostring(child.text), trans.x, trans.y, 16, text_r, text_g, text_b, 255)
    end
    --{x=root.x,y=root.y,w=root.w,h=root.h}
    for i, v in pairs(child.children) do
        draw_child(v, child, trans)
    end
end

function draw()
    local dim = calc_dim(root)
    local dir = root.dir or "vertical"
    -- Draw itself
    if root.color ~= nil then
        draw_rect(dim.x, dim.y, dim.w, dim.h, 255, 0, 0, col.a or 255)
    end


    -- Create a transform table to offset children
    local offset = { x = root.x, y = root.y, w = root.w, h = root.h }
    for i, v in pairs(root.children) do
        draw_child(v, root, offset)
        local child_dim = calc_dim(v)
        offset.x = offset.x + child_dim.x
        offset.y = offset.y + child_dim.y
        if dir == "vertical" then
            offset.y = offset.y + child_dim.h
            offset.w = root.w
            offset.h = (root.y + root.h) - offset.y
        else
            offset.x = offset.x + child_dim.w
            offset.h = root.h
            offset.w = (root.x + root.w) - offset.x
        end
    end
end

function calc_dim(elem)
    local children = elem.children or {}
    local dir = elem.dir or "vertical"
    local x = elem.x or 0
    local y = elem.y or 0
    local w = elem.w or 0
    local h = elem.h or 0

    local acc_width = 0
    local acc_height = 0


    -- Add vertical of children and make w the max width of children
    for i, child in pairs(children) do
        child.children = child.children or {}
        local child_dim = calc_dim(child)
        local cw = child_dim.w
        local ch = child_dim.h

        if dir == "vertical" then
            -- Vertical Growth
            if child_dim.w > w then
                w = child_dim.w
            end
            acc_height = acc_height + child_dim.h
        else
            -- Horizontal Growth
            if child_dim.h > h then
                h = child_dim.h
            end
            acc_width = acc_width + child_dim.w
        end
    end

    if acc_width > w then
        w = acc_width
    end
    if acc_height > h then
        h = acc_height
    end

    return { x = x, y = y, w = w, h = h }
end

function reload()
    package.loaded.console = nil
    package.loaded.init = nil
    package.loaded.ui = nil
    require('init')
end

print("Loaded!")
