With RTF.Asserter; use RTF.Asserter;
with Interfaces.C; use Interfaces.C;

package body RTF.Asserter is
    
    procedure Error(Message : String) is 
    begin
        Error_Wrapper(To_C(Message));
    end;

    procedure ErrorIf(Condition : Boolean;
                      Message : String) is
    begin
         if not Condition then 
            Error_Wrapper(To_C(Message));  
        end if;      
    end;

    procedure Fail(Message : String) is
    begin
        Fail_Wrapper(To_C(Message));  
    end;

    procedure FailIf(Condition : Boolean;
                     Message : String) is 
    begin
         if not Condition then 
            Fail_Wrapper(To_C(Message));  
        end if;      
    end;
                     
    procedure TestReport(Message : String) is
    begin
        TestReport_Wrapper(To_C(Message));
    end;

    procedure TestCheck(Condition: Boolean; 
                        Message : String) is
    Cond : Interfaces.C.unsigned := 1; 
    begin 
        if not Condition then 
            Cond := 0;
        end if;   
        TestCheck_Wrapper(Cond, To_C(Message));
    end;

end RTF.Asserter;

