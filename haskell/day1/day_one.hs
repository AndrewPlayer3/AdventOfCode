import System.IO
import System.Environment
import Control.Monad
import Data.List
import Data.Char

readInt::String->Int
readInt = read

main = do
    contents <- readFile "input.txt"
    let i = map readInt . words $ contents
    let t = 0
    let j = sum [(part_two_sum t c) | c <- i]
    print j
    
part_one_sum l = sum [(x`div`3)-2|x<-l] 

part_two_sum t c 
    | i <= 0 = t
    | otherwise = part_two_sum (t+i) i
    where i = (c`div`3)-2

