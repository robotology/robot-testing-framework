
With RTF.TestCase;   use RTF.TestCase;

package MyTest is

    type MyTest is new TestCase with null record;

    overriding function Setup (Self : in out MyTest;
                               Parameters : String) return Boolean;
    overriding procedure TearDown (Self : in out MyTest);
    overriding procedure Run(Self : in out MyTest);

    procedure Create;
    pragma Export (C, Create, RTF.Test_Create_Symbol);

end MyTest;

