
kanas = require('kanas')

-- kanas.log("hello world")

test_oda = function()
    
    local w = widget.new()

    --local values = w:get_values();
    --
    --for k, v in pairs(values) do
    --    print(k .. " : " .. v)
    --end
    
    local t = { ["aa"] = 112, ["wa"] = 11232, ["wwx"] = 45}
    
    w:set_values(t);
    
    -- local result = w.calc(2, 10)
    --
    -- if result == nil then
    --     return
    -- end
    --
    -- kanas.log("w.calc : " .. result)
    -- kanas.log("w.calc : " .. w.calc(11, 12))
    -- kanas.log("w.calc : " .. w.calc(23, 2))
    -- kanas.log("w.calc : " .. w.calc(27, 22))
    --
    -- kanas.log("get_v : " .. w:get_v())
    --
    -- kanas.log("replace : " .. w.replace(w, w))
    --
    --local result = w:replace(w)
    --
    --if result ~= nil then
    --    print("replace : " .. result)
    --end
    

end

test_oda()