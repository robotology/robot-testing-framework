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

With robottestingframework.TestCase; use robottestingframework.TestCase;
with Interfaces.C; use Interfaces.C;

package body robottestingframework.TestCase is

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

end robottestingframework.TestCase;
