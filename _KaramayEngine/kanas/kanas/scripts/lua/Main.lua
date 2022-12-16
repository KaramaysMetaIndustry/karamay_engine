
kanas = require('kanas')

--widget.__index = function(t, v)
--    print("set v")
--end

TestMetaParent = 
{
    
}


TestMeta = {

    super = TestMetaParent,
    
    getters = 
    {
        public_v = function(t)
            print("public_v getter")
            return nil
        end
    },

    setters = 
    {
        public_v = function(t, v)
            print("public_v setter: " .. v)
        end
    },
    
    __index = function(t, k)

        local getter = TestMeta.getters[k]

        if getter ~= nil and type(getter) == "function" then
            return getter(t)
        end

        return TestMeta.getters[k](t)

    end,

    __newindex = function(t, k, v)
        TestMeta.setters[k](t, v)
    end

}


frame = 
{
    super = nil,

    test = function(self, v)
        return a;
    end

}


widget = 
{
    super = frame,

    test = function(self, v)
        return 1;
    end

}



test_oda = function()
    
    local t = {}
    setmetatable(t, TestMeta)

    t.public_v = 1
    
    print(t.public_v)
    
    
    --local w = widget.new()
    
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

    --print(w)
    --
    --kanas.clog("replace : " .. w.replace(w, w))
    --
    --local result = w:replace(w)
    --
    --if result ~= nil then
    --   print("replace : " .. result)
    --end
    

end

test_oda()

