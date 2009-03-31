program vectors

var
  someVar: Decimal
  vec1: Vector
  vec2: Vector
  vec3: Vector

begin

  vec1.x := 10             // Assignment of components x, y, z.
  vec1.y := 10
  vec1.z := 0

  vec2 := vec1             // Vector assignment
  vec2.length := 1         // Set length of vector, angle is preserved.
  
  vec3 := vec2 + vec1      // Vector addition
  vec3 := vec2 - vec1      // Vector subtraction
  someVar := vec3 dot vec2 // Scalar product of vec3 and vec2.
  vec3 := vec3 cross vec2  // Cross product of vec3 and vec2.
  
  vec3.angle := 180        // Set angle, length is preserved.
  vec3.x := -vec3.x

end

