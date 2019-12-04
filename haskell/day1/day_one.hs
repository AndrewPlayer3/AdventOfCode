import System.IO
import System.Environment
import Control.Monad
import Data.List
import Data.Char

readInt::String->Int
readInt = read

main = do
    contents <- readFile "input.txt"
    let list = map readInt . words $ contents
    let part_one = sum [(x`div`3)-2|x<-list]
    let total = 0
    let part_two = sum [(part_two_sum total c) | c <- list]
    print part_one
    print part_two
    
part_one_sum l = sum [(x`div`3)-2|x<-l] 

part_two_sum t c 
    | i <= 0 = t
    | otherwise = part_two_sum (t+i) i
    where i = (c`div`3)-2

