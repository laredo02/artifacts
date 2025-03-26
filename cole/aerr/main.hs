

import qualified Data.Set as Set
import qualified Data.Map as Map
import Data.Maybe (fromMaybe)

type Var = Set.Set String
data SetExp =
  EmptySet
  | SetVar String
  | SetLit (Var)
  | Union SetExp SetExp
  | Intersection SetExp SetExp
  | Difference SetExp SetExp
type Equ = (String, SetExp)
type SysEqs = [Equ]
type State = Map.Map String Var

-- Variables used on systems of equations
fvsys :: SysEqs -> Var
fvsys [] = Set.empty
fvsys (x:xs) = Set.union (fveq x) (fvsys xs)
  where
    -- variables used on equations
    fveq :: Equ -> Var
    fveq (str, exp) = Set.union (Set.singleton str) (fv exp)
    -- variables used on expresions
    fv :: SetExp -> Var
    fv (EmptySet) = Set.empty
    fv (SetVar str) = Set.singleton str
    fv (SetLit lit) = Set.empty
    fv (Union e1 e2) = Set.union (fv e1) (fv e2)
    fv (Intersection e1 e2) = Set.intersection (fv e1) (fv e2)
    fv (Difference e1 e2) = Set.difference (fv e1) (fv e2)

semsys :: SysEqs -> State -> Map.Map String Var
semsys [] sigma = Map.empty
semsys (x:xs) sigma = Map.insert (fst x) (semeq x sigma) (semsys xs sigma)
  where
    semeq :: Equ -> State -> Var
    semeq (str, exp) state = sem exp state
    sem :: SetExp -> State -> Var
    sem (EmptySet) sigma = Set.empty
    sem (SetVar str) sigma = fromMaybe Set.empty (Map.lookup str sigma)
    sem (SetLit setStr) sigma = setStr
    sem (Union e1 e2) sigma = Set.union (sem e1 sigma) (sem e2 sigma)
    sem (Intersection e1 e2) sigma = Set.intersection (sem e1 sigma) (sem e2 sigma)
    sem (Difference e1 e2) sigma = Set.difference (sem e1 sigma) (sem e2 sigma)

-- generate an initial state
settomap :: Ord k => Set.Set k -> Map.Map k (Set.Set String)
settomap set = Map.fromSet (const Set.empty) set

-- Solve the given equation
exp1 :: SetExp
exp1 = Union (SetVar "Y") (SetVar "Z")
exp2 :: SetExp
exp2 = SetLit (Set.fromList ["3"])
exp3 :: SetExp
exp3 = Difference (SetVar "V") (SetLit (Set.fromList ["1", "2"]))
exp4 :: SetExp
exp4 = Union (Intersection (SetVar "X") (SetVar "Y")) (SetLit (Set.fromList ["1"]))
eq1 :: Equ
eq1 = ("X", exp1)
eq2 :: Equ
eq2 = ("Y", exp2)
eq3 :: Equ
eq3 = ("Z", exp3)
eq4 :: Equ
eq4 = ("V", exp4)
syst1 = [eq1, eq2, eq3, eq4]
state1 :: State
state1 = settomap (fvsys syst1)

lfp system state
  | state == nextstate = state
  | otherwise = lfp system nextstate
  where
    nextstate = (semsys system state)

main :: IO ()
main = do
  putStrLn (show (lfp syst1 state1))


