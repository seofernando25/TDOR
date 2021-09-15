local ui = {}

--region ui.Panel

ui.Pane = {
    visible = 1,
    enabled = 1,
    id = "", --unique reference to pane using
    anchors = {
        min_x = 0,
        min_y = 0,
        max_x = 1,
        maxy = 1
    },
    padding = {
        left = 0,
        right = 0,
        top = 0,
        bottom = 0
    },
    color = { 0, 0, 0, 0 },
    children = {},
    parent = nil,
    event_listeners = {}
}

function ui.Pane:New(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function ui.Pane:AddEventListener(type, fun)
    self.event_listeners[type] = self.event_listeners[type] or {}

    -- Prevent from adding event listener twice
    for _, v in pairs(self.event_listeners[type]) do
        if v == fun then
            return
        end
    end

    table.insert(self.event_listeners[type], fun)
end

function ui.Pane:RemoveEventListener(type, fun)
    for i, v in pairs(self.event_listeners[type]) do
        if v == fun then
            table.remove(self.event_listeners[type], i)
            return
        end
    end
end

function ui.Pane:DispatchEvent(type)
    for _, v in pairs(self.event_listeners[type]) do
        v(type)
    end
end

--endregion

--region Label

ui.Label = ui.Pane:New({
    text = "",
    color = { 255, 255, 255, 255 }, --default text is white
})


--endregion


return ui