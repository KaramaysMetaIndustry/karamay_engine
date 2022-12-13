
kanas = require('kanas')

test_oda = function()
    
    local w = widget.new()
    
    -- local t = { ["aa"] = 112, ["wa"] = 11232, ["wwx"] = 45}
    
    -- for k, v in pairs(t) do
    --    print(k .. " : " .. v)
    -- end

    -- w:set_values(t);
    
    -- local result = w.calc(2, 10)
    
    -- if result == nil then
    --     return
    -- end
    
    -- kanas.log("w.calc : " .. result)
    -- kanas.log("w.calc : " .. w.calc(11, 12))
    -- kanas.log("w.calc : " .. w.calc(23, 2))
    -- kanas.log("w.calc : " .. w.calc(27, 22))
    
    local wx = w:get_v()
    kanas.log("get_v : " .. tostring(wx))
    
    kanas.log("replace : " .. w.replace(w, w))
    
    local result = w:replace(w)
    
    if result ~= nil then
       print("replace : " .. result)
    end
    

end

test_oda()
