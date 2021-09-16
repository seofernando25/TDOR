local ui = {
    elements = {}
}

--region ui base functions

function ui.AddElement(element)
    table.insert(ui.elements, element)
end

--endregion



--region ui.Panel

-- TODO Decide if I wan't to create getters and setters for all this shite or just initialize the whole "object"

ui.Panel = {
    visible = 1,
    enabled = 1,
    id = "",
    rect = {
        x = 0,
        y = 0,
        w = 10,
        h = 10
    },
    align = "top-left",
    color = { 255, 255, 255, 255 },
    children = {},
    parent = nil,
    event_listeners = {}
}

function ui.Panel:New(super)
    super = super or {}
    setmetatable(super, self)
    ui.Panel.__index = self
    return super
end

function ui.Panel:GetRect()
    return self.rect
end

function ui.Panel:SetRect(x, y, w, h)
    self.rect = {
        x = x,
        y = y,
        w = w,
        h = h
    }
end

function ui.Panel:AddChild(child)
    child.parent = self
    table.insert(self.children, child)
end

function ui.Panel:RemoveChild(child)
    for i, v in pairs(self.children) do
        if v == child then
            table.remove(self.children, i)
            child.parent = nil
            return
        end
    end
end

function ui.Panel:AddEventListener(type, fun)
    self.event_listeners[type] = self.event_listeners[type] or {}

    -- Prevent from adding event listener twice
    for _, v in pairs(self.event_listeners[type]) do
        if v == fun then
            return
        end
    end

    table.insert(self.event_listeners[type], fun)
end

function ui.Panel:RemoveEventListener(type, fun)
    for i, v in pairs(self.event_listeners[type]) do
        if v == fun then
            table.remove(self.event_listeners[type], i)
            return
        end
    end
end

function ui.Panel:DispatchEvent(type)
    for _, v in pairs(self.event_listeners[type]) do
        v(type)
    end
end

--endregion

--region Label

ui.Label = ui.Panel:New({
    text = "",
    color = { 255, 255, 255, 255 }, --default text is white
})


--endregion



return ui