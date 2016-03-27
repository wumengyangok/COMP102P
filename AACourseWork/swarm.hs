graph :: [(Int, [Int])]
graph = [(1, [2, 5, 6]), (2, [1, 3, 4]), (3, [2, 4, 5, 6]), (4, [2, 3, 5, 6]), (5, [1, 3, 4, 6]), (6, [1, 3, 4, 5])]
graph' = [(1, [2, 5, 6]), (2, [1, 3, 4]), (3, [2, 5]), (4, [2, 6]), (5, [1, 3, 6]), (6, [1, 4, 5])]

reduce :: [Int] -> Int -> [Int]
reduce xs n = [x | x <- xs, elem x (snd (graph' !! (n - 1)))]

iterator :: [[Int]] -> [Int] -> [Int] -> [Int] -> [[Int]]
iterator s [] x r = s
iterator s (v:p) x r = 
    (ampleSwarm [] (reduce p v) (reduce x v) (v:r)) ++ (iterator [] p (v:x) r)

ampleSwarm :: [[Int]] -> [Int] -> [Int] -> [Int] -> [[Int]]
ampleSwarm s p x r 
    | (null p) && (null x) = (reverse r:s)
    | (null p)             = s
    | otherwise            = iterator s p x r