import System.IO
import System.Environment
import Control.Monad
import Data.List
import Data.Char

readInt::String->Int
readInt = read

codes = [1,12,2,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,10,19,2,6,19,23,1,23,5,27,1,27,13,31,2,6,31,35,1,5,35,39,1,39,10,43,2,6,43,47,1,47,5,51,1,51,9,55,2,55,6,59,1,59,10,63,2,63,9,67,1,67,5,71,1,71,5,75,2,75,6,79,1,5,79,83,1,10,83,87,2,13,87,91,1,10,91,95,2,13,95,99,1,99,9,103,1,5,103,107,1,107,10,111,1,111,5,115,1,115,6,119,1,119,10,123,1,123,10,127,2,127,13,131,1,13,131,135,1,135,10,139,2,139,6,143,1,143,9,147,2,147,6,151,1,5,151,155,1,9,155,159,2,159,6,163,1,163,2,167,1,10,167,0,99,2,14,0,0]

changeValAt ind new (x:xs)
    | ind == 0 = new:xs
    | otherwise = x:changeValAt (ind-1) new xs

run l i
    | (l !! i) == 99 = l
    | (l !! i) == 1 = run (changeValAt (l !! (i+3)) ((l !! (l !! (i+1))) + (l !! (l !! (i+2)))) l) (i+4)
    | (l !! i) == 2 = run (changeValAt (l !! (i+3)) ((l !! (l !! (i+1))) * (l !! (l !! (i+2)))) l) (i+4)
    | otherwise = run l (i+1) 

    
check_one l = [x | x <- [0..99], (run (changeValAt 2 x l) 0) !! 0 == 19690720]
check_two l = filter (\x -> check_one (changeValAt 1 x l) /= []) [0..99]


part_one = do
    run codes 0

part_two = do
    let i = (check_two codes) !! 0
    let c = changeValAt 1 i codes
    let j = (check_one c) !! 0
    (i * 100) + j