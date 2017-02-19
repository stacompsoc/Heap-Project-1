import Data.Monoid

data Point = Point Float Float deriving (Show)

data Entity = Entity { mass :: Float
                     , velocity :: Float
                     , position :: Point
                     , acceleration :: Float
                     } deriving (Show)

newtype World = World [Entity] deriving(Show)

instance Monoid World where
  mempty = World []
  mappend w1 w2 = World (a ++ b) where World a = w1
                                       World b = w2
  mconcat ws = World [e | World es <- ws, e <- es]

  
--step :: World -> World
--step w = wMap updateEntitiy w where updateEntitiy = (update w)

--update :: World -> Entity -> Entity
--update w e =   

wMap :: (Entity -> Entity) -> World -> World
wMap f (World []) = World []
wMap f (World (e:es)) = (World [(f e)]) <> (wMap f (World es))  

constantG :: Float
constantG = 6.67408e-11

gravitionalForce :: Num a => a -> a -> V2 Float -> V2 Float 
gravitionalForce m1 m2 r = (constantG*m1*m2)/r**2  

getDir :: Point -> Point -> V2 Float
getDir (Point x1 y1) (Point x2 y2) = V2 (x2-x1) (y2-y1) 

-- TODO: getDistance 
-- TODO: finish effect

effect :: Entity -> Entity -> V2 Float
effect (Entity m1 _ p1 _) (Entity m2 _ p2 _) =   
  
testWorld :: World
testWorld = World[x, y] where x = Entity 10 2 (Point 0 0) 9.8 
                              y = Entity 10 2 (Point 0 10) (-9.8)

freeze :: Entity -> Entity
freeze (Entity m _ p _) = Entity m 0 p 0

