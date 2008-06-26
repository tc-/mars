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
typecheck :: ProgramFile -> Err ProgramFile
typecheck p@(Prog n u v fs) = evalStateT (checkProg p) emptyCxt

-- Creates an empty context
emptyCxt :: ([Env],Map Ident FType)
emptyCxt = ([empty],empty)

-- Adds an empty scope to the context
addScope :: Context ()
addScope = do
           (es,fs) <- get
           put ((empty:es),fs)

-- Removes the last scope from the context
rmScope :: Context ()
rmScope = do
          (es,fs) <- get
          case es of
                  (s:[]) -> error "Error -1: No scope to remove."
                  (s:ss) -> put (ss,fs)


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
                     Just _ -> fail ("Error 1: Function " ++ printTree id ++ " already declared.")
                     Nothing -> let fs' = insert id (args,vars,stms) fs
                                    in do
                                       put (es,fs')
                                       return ()


-- Typecheck functions
checkFuncs :: [Function] -> Context [Function]
checkFuncs [] = return []
checkFuncs (f:fs) = do
                    f' <- checkFunc f
                    fs' <- checkFuncs fs
                    return (f':fs')

checkFunc :: Function -> Context Function
checkFunc (Fun id args vars (Blk stms)) = do
                                          addScope
                                          addDeclare args
                                          addDeclare vars
                                          stms' <- checkStatements stms
                                          rmScope
                                          return (Fun id args vars (Blk stms'))

-- Adds variables to current scope
addDeclare :: Declare -> Context ()
addDeclare NoDecl = return ()
addDeclare (VarDecl vars) = addVars vars


addVars :: [Vars] -> Context ()
addVars []             = return ()
addVars ((VDec i t):v) = do
                         addIdents i t
                         addVars v

addIdents :: [Ident] -> Type -> Context ()
addIdents [] _ = return ()
addIdents (i:ids) t = do
                      addVar i t
                      addIdents ids t

addVar :: Ident -> Type -> Context ()
addVar i t = do
              (e:es,fs) <- get
              case lookup i e of
                              Just _ -> fail ("Error 2: Variable " ++ printTree i ++
                                              " already declared in current scope.")
                              Nothing -> let e' = insert i t e in do
                                                                  put (e':es,fs)
                                                                  return ()

-- Typecheck statements
checkStatements :: [Stm] -> Context [Stm]
checkStatements [] = return []
checkStatements (s:ss) = do
                         s'  <- checkStatement s
                         ss' <- checkStatements ss
                         return (s':ss')

checkStatement :: Stm -> Context Stm
checkStatement (SBlc (Blk stms)) = do
                                    stms' <- checkStatements stms
                                    return (SBlc (Blk stms'))
checkStatement _ = undefined
{-
   SAss SpecExpNP Exp
 | SIf IfStm
 | SIs SpecExpNP SpecExpNP
 | SCs SpecExpNP [CaseStm]
-}