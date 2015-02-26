tree = {
  key=0,
  balance=0,
  parent,
  left,
  right,  

  SELF = 0,
  LEFT = 1,
  RIGHT = -1,

  ------------------------------------------------------
  new = function(self, o)
    o = o or {}
    setmetatable(o, { __index = self } )
   return o
  end,

  ------------------------------------------------------
  search = function(self, val) 
    if not self or self.key == val then 
      return self
    elseif val < self.key then
      return self.left:search(val)      
    else
      eturn self.right:search(val)
    end
  end,

  ------------------------------------------------------
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

  ------------------------------------------------------
  minimum = function(self) 
    if not self.left then
      return self
    else 
      return self.left:minimum()
    end
  end,

  ------------------------------------------------------
  successor = function(self,root)
    -- if there is some way to the right
    if self.right then 
      return self.right:minimum()
    end
    -- search for right predecessor
    dad = self.parent    
    local son = self
    while dad and son == dad.right do
      if dad == root then
        return nil
      end
      son = dad 
      dad = dad.parent
    end
    return dad
  end,

  ------------------------------------------------------
  insert = function(self, val)
    local nod,dir = self:place(val)
    if dir == self.LEFT then
      nod.left = tree:new{key = val, parent = nod}
      newnode = nod.left
    elseif dir == self.RIGHT then
      nod.right = tree:new{key = val, parent = nod}
      newnode = nod.right
    end
    if newnode  then 
        nod:rebalance(dir)
    end
    return newnode
  end,

  ------------------------------------------------------
  delete = function(self,val)
    local nod = self:search(val)
    if nod then
    --TODO
    end
  end,

  ------------------------------------------------------
  foreach = function(self, func)
    local victim = self:minimum()
    while victim and victim ~= self.parent do
      func(victim)
      victim = victim:successor(self)
    end
  end,

  ------------------------------------------------------
  out = function(self)
    print(self,"key: ",self.key,"h: ",self:height(), "balance: ", self.balance)
  end,

  ------------------------------------------------------
  getroot = function(self)
      root = self
      while root.parent do
          root = root.parent
      end
      return root
  end,

  ------------------------------------------------------
  outbranch = function(self)
    print "__tReE__"
    self:foreach(self.out)
  end,
  
  ------------------------------------------------------
  outtree = function(self)
    print "__tReE__"
    local root = self:getroot()
    root:foreach(self.out)
  end,

  ------------------------------------------------------
  height = function(self)
    local nod = self
    h = 0
    while nod do
      h = h + 1
      nod = nod.parent
    end
    return h 
  end,

  isleaf = function(self)
    return not self.right and not self.left
  end,

  ------------------------------------------------------
  maxheight = function(self)
    max = 0 
    local test_h = function(self)
      if self:isleaf() then 
        local h = self:height()
        if h > max then
          max = h
        end
      end
    end
    self:foreach(test_h)
    return max
  end,

  ------------------------------------------------------
  getbalance = function(self)
    return self.left:maxheight() - self.right:maxheight() 
  end,

  ------------------------------------------------------
  rotate_left = function(self)    
    local dad = self.parent
    local bigson = self.right 

    self.right = bigson.left
    if self.right then      
      self.right.parent = self
    end
    
    bigson.left = self
    self.parent = bigson

    bigson.parent = dad

    if not dad then return end

    if dad.right == self then 
      dad.right = bigson
    else
      dad.left = bigson
    end
  end,
  
  ------------------------------------------------------
  rotate_right = function(self)    
    local dad = self.parent
    local bigson = self.left

    self.left = bigson.right
    if self.left then
      self.left.parent = self
    end
    
    bigson.right= self
    self.parent = bigson

    bigson.parent = dad

    if not dad then return end

    if dad.right == self then 
      dad.right = bigson
    else
      dad.left = bigson
    end
  end,

  ------------------------------------------------------
  rebalance = function(self, dir)
    if dir ~= self.RIGHT and dir ~= self.LEFT then error("wrong dir") end

    if self.left and self.right then 
        self.balance = 0
        return
    end

    local dad = self.parent
    self.balance = (dir == self.RIGHT) and -1 or 1

    while dad do
      if self == dad.left then

        if dad.balance == 1 then 
          if self.balance == -1  then 
            -- Left Right Case
            self:rotate_left() 
          end
          -- Left Left Case
          dad:rotate_right()
          break 
        end

        -- no height increase for dad 
        if dad.balance == -1 then
          dad.balance = 0 
          break
        end
        
        -- Height increases at dad so continue
        dad.balance = 1 

      else -- self == dad.right

        if dad.balance == -1 then 
          if self.balance == 1 then 
            -- Right Left Case
            self:rotate_right() 
          end
          -- Right Right Case
          dad:rotate_left()
          break 
        end

        -- no height increase for dad 
        if dad.balance == 1 then
          dad.balance = 0 
          break 
        end
        
        -- Height increases at dad so continue
        dad.balance = -1 

      end
      self = dad
      dad = self.parent
    end
  end,
}


t = tree:new{key = 10}
n1 = t:insert(1)
n100 = t:insert(100)
n_m5 = t:insert(-5)
n5 = t:insert(5)


n6 = t:insert(6)

t:outtree()
