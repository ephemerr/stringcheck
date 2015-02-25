tree = {
    key=0,
    parent,
    left,
    right,

    SELF = 0,
    LEFT = 1,
    RIGHT = 2,

    new = function(self, o)
        o = o or {}
        setmetatable(o, { __index = self } )
      return o
    end,

    search = function(self, val) 
        if not self or self.key == val then 
            return self
        elseif val < self.key then
            return self.left:search(val)            
        else
            return self.right:search(val)
        end
    end,


    place = function(self, val) 
        if self.key == val then 
            return self, self.SELF
        elseif val < self.key then
            if not self.left then 
                return self, self.LEFT
            else
                return self.left:place(val)            
            end
        else
            if not self.right then 
                return self, self.RIGHT
            else
                return self.right:place(val)
            end
        end
    end,

    minimum = function(self) 
        if not self.left then
            return self
        else 
            return self.left:minimum()
        end
    end,

    successor = function(self)
        -- if there is some way to the right
        if self.right then 
            return self.right:minimum()
        end
        -- search for right predecessor
        dad = self.parent        
        son = self
        while dad and son == dad.right do
            son = dad 
            dad = dad.parent
        end
        return dad
    end,

    insert = function(self, val)
        nod,dir = self:place(val)
        print(nod.key,dir,val)
        if dir == self.LEFT then
            nod.left = tree:new{key = val, parent = nod}
        elseif dir == self.RIGHT then
            nod.right = tree:new{key = val, parent = nod}
        end
    end,

    delete = function(self,val)
        nod = self:search(val)
        if nod then
        --TODO
        end
    end

    foreach = function(self, func)
        victim = self:minimum()
        while victim do
            func(victim)
            victim = victim:successor()
        end
    end,

    out = function(self)
        print(self.key)
    end,

    outtree = function(self)
        self:foreach(self.out)
    end,
}

t = tree:new{key = 10}
t.left = tree:new{key=1,parent=t}
t.right = tree:new{key=100,parent=t}

t:insert(-5)
t:insert(5)
t:insert(6)
t:insert(55)
t:insert(555)



t:outtree()
