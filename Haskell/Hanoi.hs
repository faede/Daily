{-# OPTIONS_GHC -Wall #-}

{-# LANGUAGE ViewPatterns #-}

module Hanoi where

type Peg = String
type Move = (Peg, Peg)
hanoi :: Integer -> Peg -> Peg -> Peg -> [Move]
hanoi n a b c
	| n <= 0  = []
	| n == 1  = [(a, b)]
	| otherwise = hanoi (n-1) a c b  ++ [(a, b)] ++ hanoi (n-1) c b a -- here using (n-1), not n - 1


hanoi2 :: Integer -> Peg -> Peg -> Peg -> Peg -> [Move]
hanoi2 n a b c d
	| n <= 0  = []
	| n == 1  = [(a, b)]
	| n == 2  = [(a, c), (a, b), (c, b)]
	| n == 3  = [(a, d), (a, c), (a, b), (c, b), (d, b)]
	| otherwise = hanoi2 (n-1) a c b d ++ [(a, b)] ++ hanoi2 (n-1) c b a d