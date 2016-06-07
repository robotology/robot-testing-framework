with RTF; use RTF;
With RTF.Asserter;
With MyTest; use MyTest;
with Ada.Numerics.discrete_Random;

package body MyTest is

   package Rand_Int is new Ada.Numerics.Discrete_Random(Positive);
   gen : Rand_Int.Generator;

   function RandomNumber(n: in Positive) return Integer is
   begin
      return Rand_Int.Random(gen) mod n;  -- or mod n+1 to include the end value
   end RandomNumber;
    
    procedure Create is 
    begin
        SetTest(new MyTest, "MyTest");
    end;

    function Setup (Self : in out MyTest;
                    Parameters : String) return Boolean is
        pragma Unreferenced (Self);
        pragma Unreferenced (Parameters);
    begin
        Rand_Int.Reset(gen);
        Asserter.TestReport("Preparing setup...");
        return True;
    end Setup;

    procedure TearDown (Self : in out MyTest) is
         pragma Unreferenced (Self);  
    begin
        Asserter.TestReport("Tearing down...");
    end;

    procedure Run (Self : in out MyTest) is
        pragma Unreferenced (Self);
        n1 : Integer;
        n2 : Integer;
    begin
        for I in Integer range 1 .. 10 loop
            n1 :=  RandomNumber(10);
            n2 :=  RandomNumber(10);
            Asserter.TestCheck(n1>n2, 
                               Integer'Image(n1) & " is bigger than " & Integer'Image(n2) & ".");
        end loop;
        
        --Asserter.TestCheck(5>3, "5 is bigger than 3.");
        --Asserter.TestCheck(5<3, "5 is smaller than 3.");
    end;

    
end MyTest;

