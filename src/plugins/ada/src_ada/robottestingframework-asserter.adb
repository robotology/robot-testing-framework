-- Robot Testing Framework
--
-- Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
--
-- This library is free software; you can redistribute it and/or
-- modify it under the terms of the GNU Lesser General Public
-- License as published by the Free Software Foundation; either
-- version 2.1 of the License, or (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
-- Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Lesser General Public
-- License along with this library; if not, write to the Free Software
-- Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

With robottestingframework.Asserter; use robottestingframework.Asserter;
with Interfaces.C; use Interfaces.C;

package body robottestingframework.Asserter is

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

    procedure TestFailIf(Condition: Boolean;
                        Message : String) is
    Cond : Interfaces.C.unsigned := 1;
    begin
        if not Condition then
            Cond := 0;
        end if;
        TestFailIf_Wrapper(Cond, To_C(Message));
    end;

end robottestingframework.Asserter;
