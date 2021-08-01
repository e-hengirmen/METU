module PE4 where

import Data.Maybe -- up to you if you want to use it or not

-- Generic DictTree definition with two type arguments
data DictTree k v = Node [(k, DictTree k v)] | Leaf v deriving Show

-- Lightweight Char wrapper as a 'safe' Digit type
newtype Digit = Digit Char deriving (Show, Eq, Ord) -- derive equality and comparison too!

-- Type aliases
type DigitTree = DictTree Digit String
type PhoneNumber = [Digit]


---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------


----------
-- Part I:
-- Some Maybe fun! Basic practice with an existing custom datatype.

-- toDigit: Safely convert a character to a digit
toDigit :: Char -> Maybe Digit
toDigit a 
  |a>='0' && a<='9' = Just (Digit a)
  |otherwise = Nothing


-- toDigits: Safely convert a bunch of characters to a list of digits.
--           Particularly, an empty string should fail.
toDigits :: String -> Maybe PhoneNumber
toDigits "" = Nothing
toDigits str = toDigitsHelp str []

toDigitsHelp :: String -> PhoneNumber -> Maybe PhoneNumber
toDigitsHelp [] list = Just (list)
toDigitsHelp (c:str) list = if c>='0' && c<='9' then toDigitsHelp str (list++[(Digit c)]) else Nothing
  


-----------
-- Part II:
-- Some phonebook business.

-- numContacts: Count the number of contacts in the phonebook...
numContacts :: DigitTree -> Int
numContacts  (Node list) = numContacts2 list

numContacts2 :: [(Digit, DigitTree)] -> Int
numContacts2 [] = 0 
numContacts2 ((_, Leaf _):xs) = 1+numContacts2 xs
numContacts2 ((_, Node list):xs) = numContacts2 list + numContacts2 xs



    
-- getContacts: Generate the contacts and their phone numbers in order given a tree. 
getContacts :: DigitTree -> [(PhoneNumber, String)]
getContacts (Node list) = getContacts2 list []

getContacts2 :: [(Digit, DigitTree)] -> PhoneNumber -> [(PhoneNumber, String)]
getContacts2 [] _ = []
getContacts2 ((dig, Leaf str):xs)  currentNumber = ((currentNumber++[dig]),str):(getContacts2 xs currentNumber)
getContacts2 ((dig, Node list):xs) currentNumber = (getContacts2 list (currentNumber++[dig]))++(getContacts2 xs currentNumber)

{-
getContacts a@() = getContacts2 a

getContacts2 :: [(k, DictTree k v)] -> PhoneNumber -> [(PhoneNumber, String)]
getContacts2 (Node list) currentNumber = undefined-}

-- autocomplete: Create an autocomplete list of contacts given a prefix
-- e.g. autocomplete "32" areaCodes -> 
--      [([Digit '2'], "Adana"), ([Digit '6'], "Hatay"), ([Digit '8'], "Osmaniye")]
autocomplete :: String -> DigitTree -> [(PhoneNumber, String)]
autocomplete "" _ = []
autocomplete str (Node list) = autocomplete2 str list

autocomplete2 :: String -> [(Digit, DigitTree)] -> [(PhoneNumber, String)]
autocomplete2 _ [] = []
autocomplete2 str@(_:_:_) ((_, Leaf _):xs)= autocomplete2 str xs
autocomplete2 (c1:[]) ((Digit c2, Node list):xs)
  |c1==c2 = getContacts2 list []
  |otherwise = autocomplete2 (c1:[]) xs
autocomplete2 (c1:[]) ((Digit c2, Leaf str):xs)
  |c1==c2 = [([],str)]
  |otherwise = autocomplete2 (c1:[]) xs
autocomplete2 str@(c1:rest) ((Digit c2, Node list):xs)
  |c1==c2 = autocomplete2 rest list
  |otherwise = autocomplete2 str xs

-----------
-- Example Trees
-- Two example trees to play around with, including THE exampleTree from the text. 
-- Feel free to delete these or change their names or whatever!

exampleTree :: DigitTree
exampleTree = Node [
    (Digit '1', Node [
        (Digit '3', Node [
            (Digit '7', Node [
                (Digit '8', Leaf "Jones")])]),
        (Digit '5', Leaf "Steele"),
        (Digit '9', Node [
            (Digit '1', Leaf "Marlow"),
            (Digit '2', Node [
                (Digit '3', Leaf "Stewart")])])]),
    (Digit '3', Leaf "Church"),
    (Digit '7', Node [
        (Digit '2', Leaf "Curry"),
        (Digit '7', Leaf "Hughes")])]

areaCodes :: DigitTree
areaCodes = Node [
    (Digit '3', Node [
        (Digit '1', Node [
            (Digit '2', Leaf "Ankara")]),
        (Digit '2', Node [
            (Digit '2', Leaf "Adana"),
            (Digit '6', Leaf "Hatay"),
            (Digit '8', Leaf "Osmaniye")])]),
    (Digit '4', Node [
        (Digit '6', Node [
            (Digit '6', Leaf "Artvin")])])]

