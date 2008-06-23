-- dc-Ankan
module TypeChecker( typecheck ) where

import AbsMars
import PrintMars
import ErrM

import Prelude hiding (lookup)

import Control.Monad.State
import Data.Map as M

type Env = Map Ident Type

-- Function type = args vars statements
type FType = (Declare,Declare,[Stm])

type CtxState = ([Env],Map Ident FType)
type Context a = StateT CtxState Err a

-- entry point
typecheck :: ProgramFile -> ProgramFile
typecheck p@(Prog n u v fs) = p

-- check an entire program
checkProg :: ProgramFile -> Context ProgramFile
checkProg p@(Prog n u v fs) = do
                              addFuncs fs
                              fs'' <- checkFuncs fs
                              return (Prog n u v fs)

-- add all functions of a program to our context
addFuncs :: [Function] -> Context ()
addFuncs [] = return ()
addFuncs (f:fs) = do
                  addFunc f
                  addFuncs fs

-- adds a function to the context
addFunc :: Function -> Context ()
addFunc (Fun id args vars (Blk stms)) = do
   (es,fs) <- get
   case lookup id fs of
                     Just _ -> fail ("Function " ++ printTree id ++ " already declared.")
                     Nothing -> let fs' = insert id (args,vars,stms) fs
                                    in do
                                       put (es,fs')
                                       return ()

checkFuncs :: [Function] -> Context [Function]
checkFuncs [] = return []
checkFuncs (f:fs) = do
                    f' <- checkFunc f
                    fs' <- checkFuncs fs
                    return (f':fs')

checkFunc :: Function -> Context Function
checkFunc _ = undefined