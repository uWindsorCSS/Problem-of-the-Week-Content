import Data.List.Split (splitOn)
import qualified Data.Map as Map

-- | Convert a string to an Int.
readInt :: String -> Int
readInt = read

-- | Compute the number of unique pairs in the corpus which sum to target.
pairSums :: [Int] -> Int -> Int
pairSums corpus target = snd $ foldl countPairs (Map.empty, 0) corpus
  where
    countPairs (mapping, seenSoFar) x =
      (Map.insertWith (+) x 1 mapping,
      seenSoFar + Map.findWithDefault 0 (target - x) mapping)

main = do
  nHoles <- readInt <$> getLine
  chestnuts <- map readInt <$> splitOn " " <$> getLine
  [c, s] <- map readInt <$> splitOn " " <$> getLine
  print $ pairSums chestnuts s >= c
