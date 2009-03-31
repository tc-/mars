unit Ant

Type

   // IORecord: This is used by the compiler. Reading or writing any of the 
   // vars will be compiled into io read/write operations. Writing to any 
   // readonly var will produce a compile warning.
   
   // TrackedEngineIO: Engines connected to double larva tracks, left and right.
   TrackedEngineIO = IORecord
     MaximumAcceleration  : Readonly Decimal  // Maximum acceleration in m/s^2.
     CurrentSpeed         : Readonly Decimal  // Curent speed in m/s.
     Acceleration         : Vector            // Current acceleration of the two tracks.
   end
   
   SensorObject = Record
     ObjectID      : Number  // ObjectID of object seen by sensor or < 0 if not vaild.
     Location      : Vector  // Vector pointing at object, relative to own position.
   end
   
   ProximitySensorIO = IORecord
     NumObjectsInRange : Readonly Number        // The number or objects seen by sensor
     CurrentObjectNum  : Number                 // The index of the object curently visible in CurrentObject
     CurrentObject     : Readonly SensorObject  // An object seen by sensor, once read CurrentObjectNum 
                                                // will automatically be incresed.
   end


interface

const
  MemorySize  : Number          := 1024
  CPUSpeed    : Number          := 10
  
  // IO interface
  Sensor      : ProximitySensorIO  := 0 // Assign io index.
  Engine      : TrackedEngineIO    := 1


implementation


var
  Obj: SensorObject

  
begin

  Sensor.CurrentObjectNum := 0 // This should be compiled into io read index 0 address 4
  Obj := Sensor.CurrentObject
  while Obj.ObjectID >= 0 begin
    // Do something
    Obj := Sensor.CurrentObject
  end
  
end


