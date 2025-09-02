---@class entity_t
---@field name  string
---@field value integer

---Exported module.
local M = {}

---@type table<integer, entity_t>
M.data = {
    {
        name = "Snake",
        value = 20,
    },
    {
        name = "Bird",
        value = 14,
    },
}

return M