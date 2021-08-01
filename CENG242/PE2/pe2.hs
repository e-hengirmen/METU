module PE2 where

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------

-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

--------------------------
-- Part I: Time to inf up!

-- naturals: The infinite list of natural numbers. That's it!
naturals :: [Integer]
naturals = [0..]

-- interleave: Interleave two lists, cutting off on the shorter list.
interleave :: [a] -> [a] -> [a]
interleave _ [] = []
interleave [] _ = [] 
interleave (a:as) (b:bs) = (a:b:(interleave as bs)) 

-- integers: The infinite list of integers. Ordered as [0, -1, 1, -2, 2, -3, 3, -4, 4...].
integers :: [Integer]
integers = 0:(interleave [-1,-2..] [1..])

--------------------------------
-- Part II: SJSON Prettification

-- splitOn: Split string on first occurence of character.
splitOn :: Char -> String -> (String, String)
splitOn spl s = splitOn2 spl s ""

splitOn2 :: Char -> String -> String -> (String, String)
splitOn2 spl [] left = (left,"")
splitOn2 spl (c:s) left | spl==c = (left,s)
                        | otherwise = splitOn2 spl s (left++[c])

-- tokenizeS: Transform an SJSON string into a list of tokens.
tokenizeS :: String -> [String]
tokenizeS s = tokenizeS2 s []

tokenizeS2 :: String -> [String] -> [String]
tokenizeS2 [] s2 = s2
tokenizeS2 (c:s1) s2 |c=='{' || c=='}' || c==':' || c==',' = [c]:(tokenizeS2 s1 s2)
                     |c=='\'' = let (s22,s11) = splitOn '\'' s1
                                in s22:(tokenizeS2 s11 s2)
                     |otherwise = tokenizeS2 s1 s2

-- prettifyS: Prettify SJSON, better tokenize first!
prettifyS :: String -> String
prettifyS sl = prettifyS2 (tokenizeS sl) "" 0

prettifyS2 :: [String] -> String -> Int -> String
prettifyS2 [] _ _ = ""
prettifyS2 ("{":sl) indents len =                   let indents2=' ':' ':' ':' ':indents
                                                    in ('{':'\n':indents2)++(prettifyS2 sl indents2 (len+4))
prettifyS2 ("}":sl) (' ':' ':' ':' ':indents) len = '\n':indents++ '}':(prettifyS2 sl indents (len-4))
--prettifyS2 ("}":sl) _ len =                         '}':(prettifyS2 sl "" 0)
prettifyS2 (s:sl) indents len |s==","    =          (',':'\n':indents)++(prettifyS2 sl indents len)
                              |s==":"    =          ':':' ':(prettifyS2 sl indents len)
                              |otherwise =          ('\'':s)++ '\'':(prettifyS2 sl indents len)

-- Good luck to you, friend and colleague!

