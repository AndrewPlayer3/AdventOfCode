import System.IO
import System.Environment
import Control.Monad
import Data.List
import Data.Char

-- Req 1: Has adjacent numbers
-- Req 2: Is in the range
-- Req 3: ...
-- [236491..713787]

part_one l = do
  let ls = [x | x <- l, has_adjacent (show x), doesnt_decrease (show x)]
  let len = length ls
  print len

part_two l = do
  let ls = [x | x <- l, p2_has_adjacent (show x), doesnt_decrease (show x)]
  let len = length ls
  print len

has_adjacent n = length(group n) /= (length n) 

p2_has_adjacent n 
  | l /= [] = True
  | otherwise = False
  where l = [x | x <- (group n), (length x) == 2]

doesnt_decrease n = (sort n) == n