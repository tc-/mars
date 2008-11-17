program botcode

// Single line comment
{
  Multi line comment
}
(*
  Alternative multi line comment
*)

uses time, system // unit includes


const // constant declaration block
   pi: Decimal = 3.14 // declaraion of fixed point deciaml number

var // var declaration block outside function is treated as global
  global: Number // global variable


function functionWithReturnValueAndParams( var num: Number pos: Position ): Number forward // Forward declaration of function

function noReturnValueOrParameters()
var // Variable declaration block
  num: Number // Variable devlaration, type: Number
  pos1, pos2: Position // Multiple declarations
  i1, i2: Number
  b: Boolean // Boolean is an unsigned byte where 0 repressents false and everything else true
begin
  num := 1 // Assignment
  i1 := 0
  i2 := 1
  b := i1 = i2 // equal
  b := i1 <> i2 // not equal
  b := i1 < i2 // below
  b := i1 > i2 // above
  b := i1 <= i2 // below or equal
  b := i1 >= i2 // above or equal
  b := (i1 = i2) or (i1 <> i2) // logical or
  b := (i1 = i2) and (i1 <> i2) // logical and
  b := (i1 = i2) xor (i1 <> i2) // logical xor
  b := not (i1 <> i2) // logical not

  num := ~num // Bitwise not
  num := num or num // Bitwise or (Type is not Boolean)
  num := num and num // Bitwise and
  num := num xor num // Bitwise xor
  num := num shr 3 // Shift right
  num := num shl 3 // Shift left
end


function functionWithReturnValueAndParams( var num: Number pos: Position ): Number
var
  i: Number
begin
  Result := 3 // assign return value, this can be done from anyware in the function
  for i := 0 to 10 do begin
    if i < 3 then continue // step to next i
    else break // exit enclosing for, while or repeat loop 
  end
  if Result = 3 then begin // return can be read like a variable
    Result := 4
    return // return from function
  end
end


begin // "main" function

  for global := 1 to 10 do begin // basic for loop construct
    sleep(0)
  end

  for global := 10 downto 1 do begin // basic for loop construct, decrementing
    sleep(0)
  end

  repeat // loop construct similar to C do while
    sleep(0)
  until global = 0 // loop exits when global = 0 evaluates to true

end

