print("[Lua] : hello world from lua")

a = function()

    w = widget.new() -- 1
    w2 = widget.new()


    print("[Lua] : " .. w.calc(1, 2))
    print("[Lua] : " .. w.calc(11, 12))
    print("[Lua] : " .. w.calc(23, 2))
    print("[Lua] : " .. w.calc(27, 22))

   print("[Lua] : getv " .. w:getv())

   print("[Lua] : replace " .. w:replace(w))

end


a()
