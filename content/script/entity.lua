---@class entity_t
---@field name  string
---@field value integer

---Exported module.
local M = {}

---@type string
M.name = "entity"

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
    {
        name = "Cat",
        value = 1,
    },
    {
        name = "Tiger",
        value = 51,
    },
    {
        name = "Elephant",
        value = 32,
    },
    {
        name = "Crocodile",
        value = 4,
    },
    {
        name = "Dog",
        value = 11,
    },
    {
        name = "Ant",
        value = 132,
    },
}

return M
