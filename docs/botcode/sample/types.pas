program botcode

uses position

Type
   BotType = set of (Ant, Grunt, Terminator);

   Bot = Record
      id: Number
      model: BotType
      pos: Position
      damage: Number
   end
  


function arrays
var
  a: array[1..5] of Char // One dimentional array
  a2d: array[10..20, 10..20] of Decimal // Two dimentional array
begin
  a[1] := 'A'
  a := "hello"
  a2d[12,13] := 3.1
end


var
  myBot: Bot
  someVar: Decimal

begin // "main" function

  myBot.id := 1
  myBot.model := Terminator
  myBot.pos.x := 10
  myBot.pos.y := 10

end

