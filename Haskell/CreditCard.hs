{-# OPTIONS_GHC -Wall #-}

{-# LANGUAGE ViewPatterns #-}

module CreditCard where

getNextDigit :: Integer -> Integer
getNextDigit n = (n `div` 10)

getCurDigit :: Integer -> Integer
getCurDigit n = (n `mod` 10)

 
toDigitsRev :: Integer -> [Integer]
toDigitsRev n
    | n <= 0 = []
    | otherwise =  getCurDigit(n) : toDigitsRev(getNextDigit(n)) 


-- toDigits(getNextDigit(n)) : [getCurDigit(n)] , error
-- see https://stackoverflow.com/questions/1817865/haskell-and-differences
toDigits :: Integer -> [Integer]
toDigits n
    | n <= 0 = []
    | otherwise = toDigits(getNextDigit(n)) ++  [getCurDigit(n)]

doubleEveryOtherHelper :: [Integer] -> [Integer]
doubleEveryOtherHelper [] = []
doubleEveryOtherHelper (x : []) = [x]
doubleEveryOtherHelper (x : (y : zs)) = [x,2 * y] ++ doubleEveryOtherHelper(zs)

getListRev :: [Integer] -> [Integer]
getListRev [] = []
getListRev (x : zs) = getListRev(zs) ++ [x]

doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther x = getListRev(doubleEveryOtherHelper(getListRev(x)))

sumDigitsHelper :: [Integer] -> Integer
sumDigitsHelper [] = 0
sumDigitsHelper (x : zs) = x + sumDigits(zs)

sumDigits :: [Integer] -> Integer
sumDigits [] = 0
sumDigits (x : zs) = sumDigitsHelper(toDigits(x)) + sumDigits(zs)


validate :: Integer -> Bool
validate n =  sumDigits(doubleEveryOther(toDigits(n))) `mod` 10 == 0







