With RTF.TestCase; use RTF.TestCase;
with Interfaces.C; use Interfaces.C;

package body RTF.TestCase is

   function Setup (Self : in out TestCase; 
                   Parameters : String) return Boolean is
        pragma Unreferenced (Self);
        pragma Unreferenced (Parameters);
    begin
        return True;
    end Setup;

    procedure TearDown (Self : in out TestCase) is null;

    procedure SetTest(Test : TestCase_Access;
                      Name : String := "Unknown") is
    begin
        Instance := Test;
        setName(Name);
    end;

    procedure setName(Name : String) is 
    begin
        SetName_Wrapper(To_C(Name));
    end;

    function SetupTest(Parameters : VarCString) 
                       return Interfaces.C.unsigned is
        Ret : Interfaces.C.unsigned := 0;
    begin
        if Instance.All.Setup(To_Ada(Parameters)) then
            Ret := 1; 
        end if;
        return Ret;
    end;

    procedure TearDownTest is 
    begin
        Instance.All.TearDown;
    end;

    procedure RunTest is 
    begin 
        Instance.All.Run; 
    end;

end RTF.TestCase;

