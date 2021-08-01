module PE1 where

import Text.Printf


-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

nameRecognition :: String -> Double
nameRecognition name = case name of "USD" -> 8.18
                                    "EUR" -> 9.62
                                    "BTC" -> 473497.31

convertTL :: Double -> String -> Double
convertTL money currency = getRounded (money/(nameRecognition currency))

-------------------------------------------------------------------------------------------

countOnWatch :: [String] -> String -> Int -> Int
countOnWatch schedule employee 0 = 0
countOnWatch (x:xs) employee days
    | x==employee = 1+countOnWatch xs employee (days-1)
    | otherwise = countOnWatch xs employee (days-1)
-------------------------------------------------------------------------------------------

encrypt :: Int -> Int
encrypt x = encryptHelp x 0 1

encryptHelp :: Int -> Int -> Int -> Int
encryptHelp 0 newNum _ = newNum
encryptHelp num newNum digit =encryptHelp (div num 10) (newNum+(newDigit (mod num 10))*digit) (digit*10)

newDigit :: Int -> Int
newDigit x
        |mod x 3==0 = (x-1)
        |mod x 4==0 = (x*2) `mod` 10
        |x==5 = 8
        |otherwise = mod (x+4) 10



-------------------------------------------------------------------------------------------

compoundInterests :: [(Double, Int)] -> [Double]
compoundInterests investments = [getRounded $ money*(1+interest (money,year)/12)^(12*year)|(money,year)<-investments]

interest :: (Double, Int) -> Double
interest (x,y)
         |y>=2 = 0.095+ if x>=10000 then 0.02 else 0
         |otherwise =0.09+ if x>=10000 then 0.015 else 0
