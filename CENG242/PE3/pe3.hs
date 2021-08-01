module PE3 where

data Cell = SpaceCraft Int | Sand | Rock Int | Pit deriving (Eq, Read, Show)

type Grid = [[Cell]]
type Coordinate = (Int, Int)

data Move = North | East | South | West | PickUp | PutDown deriving (Eq, Read, Show)

data Robot = Robot { name :: String,
                     location :: Coordinate,
                     capacity :: Int,
                     energy :: Int,
                     storage :: Int } deriving (Read, Show)

-------------------------------------------------------------------------------------------
--------------------------------- DO NOT CHANGE ABOVE -------------------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------
-------------------------------------- PART I ---------------------------------------------

isInGrid :: Grid -> Coordinate -> Bool
isInGrid grid@(item:rest) (x,y) = if (x>=0&&y>=0) then (if (y<length grid && x<length item) then True else False) else False

-------------------------------------------------------------------------------------------

totalCount :: Grid -> Int
totalCount [] = 0
totalCount (item:rest) = totalCount rest + totalCountHelp item

totalCountHelp :: [Cell] -> Int
totalCountHelp [] = 0
totalCountHelp (x:xs) = isRock(x) + totalCountHelp xs

isRock::Cell->Int
isRock (Rock x)=x
isRock _=0

-------------------------------------------------------------------------------------------

coordinatesOfPits :: Grid -> [Coordinate]
coordinatesOfPits [] = []
coordinatesOfPits grid@(first:rest) = coordinatesOfPitsHelp1 grid (length grid-1) (length first-1) 0 0

{-
coordinatesOfPitsHelp :: [Cell] -> Int -> Int -> Int -> [Coordinate] 
coordinatesOfPitsHelp (item,rest) row column
-}

coordinatesOfPitsHelp1 :: Grid -> Int -> Int -> Int -> Int -> [Coordinate] 
coordinatesOfPitsHelp1 grid lastRow lastColumn row column 
    |column>lastColumn = []
    |row> lastRow      = coordinatesOfPitsHelp1 grid lastRow lastColumn 0 (column+1)
    |otherwise         = if (isPit ((grid !! row) !! column)) 
      then (column,row):coordinatesOfPitsHelp1 grid lastRow lastColumn (row+1) column
      else coordinatesOfPitsHelp1 grid lastRow lastColumn (row+1) column

isPit::Cell->Bool
isPit Pit=True
isPit _=False

-------------------------------------------------------------------------------------------

tracePath :: Grid -> Robot -> [Move] -> [Coordinate]
tracePath grid robot move = tracePath2 grid (location robot) move (energy robot)
--isInGrid
tracePath2 :: Grid -> Coordinate -> [Move] -> Int -> [Coordinate]
tracePath2 _ _ [] _ = []
tracePath2 _ current (_:movesLeft) 0 =current:(tracePath2 [] current movesLeft 0) 
tracePath2 grid current@(column,row) (move:movesLeft) energy
    |isPit ((grid !! row) !! column) = current:(tracePath2 [] current movesLeft 0)
    |move==PickUp  = current:(tracePath2 grid current (movesLeft) (max 0 (energy-5)))
    |move==PutDown = current:(tracePath2 grid current (movesLeft) (max 0 (energy-3)))
    |otherwise     = let next=makeMove current move
      in if (isInGrid grid next) 
        then (next:(tracePath2 grid next movesLeft (energy-1))) 
        else (current:(tracePath2 grid current movesLeft (energy-1)))

makeMove :: Coordinate -> Move -> Coordinate
makeMove (x,y) North = (x,y-1)
makeMove (x,y) South = (x,y+1)
makeMove (x,y) East  = (x+1,y)
makeMove (x,y) West  = (x-1,y) 

------------------------------------- PART II ----------------------------------------------

energiseRobots :: Grid -> [Robot] -> [Robot]
energiseRobots grid@(a:b) robots = energiseRobots2 (findCraft grid (length grid-1) (length a-1) 0) robots

energiseRobots2 :: Coordinate -> [Robot] -> [Robot]
energiseRobots2 _ [] = []
energiseRobots2 spaceCraft@(spaceX,spaceY) (robot@(Robot a coor@(robotX,robotY) b ener c):robotsLeft) = 
  let newEn=(max 0 (100-20*((abs (spaceX-robotX))+((abs (spaceY-robotY))))))
    in (Robot a coor b (min 100 (ener+newEn)) c):energiseRobots2 spaceCraft robotsLeft

findCraft :: Grid -> Int-> Int-> Int -> Coordinate
findCraft (x:xs) lastRow lastColumn row= let this=findCraft2 x lastColumn 0
  in if this==(-1) then 
      findCraft xs lastRow lastColumn (row+1) 
    else
      (this,row)

findCraft2 :: [Cell] -> Int -> Int -> Int
findCraft2 [] _ _ = -1
findCraft2 ((SpaceCraft _):_) _ column = column
findCraft2 (_:rest) lastColumn column = findCraft2 rest lastColumn (column+1)


-------------------------------------------------------------------------------------------

applyMoves :: Grid -> Robot -> [Move] -> (Grid, Robot)
applyMoves grid robot [] = (grid, robot)
applyMoves grid robot@(Robot _ _ _ 0 _) _ = (grid, robot)
applyMoves grid (Robot name loc@(robotX,robotY) cap ener stor) (move:movesLeft)
  |isPit ((grid !! robotY) !! robotX) = applyMoves grid (Robot name loc cap (ener-1) stor) movesLeft
  |move==PickUp  = if ener>4 then 
      (if cap>stor && isRock ((grid !! robotY) !! robotX) > 0 then
        applyMoves (gridPickUp grid robotY robotX) (Robot name loc cap (ener-5) (stor+1)) movesLeft
      else applyMoves grid (Robot name loc cap (ener-5) stor) movesLeft
      )
    else applyMoves grid (Robot name loc cap 0 stor) movesLeft
  |move==PutDown = if ener>2 then 
      (if stor>0 then
        applyMoves (gridPutDown grid robotY robotX) (Robot name loc cap (ener-3) (stor-1)) movesLeft
      else applyMoves grid (Robot name loc cap (ener-3) stor) movesLeft
      )
    else applyMoves grid (Robot name loc cap 0 stor) movesLeft
  |otherwise     = let next=makeMove loc move
    in if (isInGrid grid next)
      then applyMoves grid (Robot name next cap (ener-1) stor) movesLeft
      else applyMoves grid (Robot name loc  cap (ener-1) stor) movesLeft

      

gridPickUp  :: Grid -> Int -> Int -> Grid
gridPickUp (row:rest) 0 robotX = (gridPickUp2 row robotX):rest 
gridPickUp (row:rest) robotY robotX  = row:(gridPickUp rest (robotY-1) robotX)

gridPickUp2 :: [Cell] -> Int -> [Cell]
gridPickUp2 (Rock x:rest) 0 = (Rock (x-1)):rest
gridPickUp2 (item:rest) robotX = item:(gridPickUp2 rest (robotX-1))


gridPutDown :: Grid -> Int -> Int -> Grid
gridPutDown (row:rest) 0 robotX = (gridPutDown2 row robotX):rest 
gridPutDown (row:rest) robotY robotX  = row:(gridPutDown rest (robotY-1) robotX)

gridPutDown2 :: [Cell] -> Int -> [Cell]
gridPutDown2 (SpaceCraft x:rest) 0 = (SpaceCraft (x+1)):rest
gridPutDown2 (item:rest) robotX = item:(gridPutDown2 rest (robotX-1))















