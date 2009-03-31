unit botcodeunit


interface // declaration of unit interface

function exportedFunc1( var num: Number ) : Number
function exportedFunc2

const // constant declaration block visible to users of the unit
  pi: Decimal := 3.14 // declaraion of fixed point deciaml number

var // visible to users of the unit
  global: Number // global variable


implementation // implementation of unit interface


const // constant declaration block invisible to users of the unit
  mpi: Decimal := 3.14 // declaraion of fixed point deciaml number

var // invisible to users of the unit
  mglobal: Number // global variable



function exportedFunc1( var num: Number ) : Number
begin
  Result := 0
end

function exportedFunc2
begin
end

function notExportedFunc2
begin
end



begin // run before "main" function is called

end

