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

with Interfaces.C;

package robottestingframework.TestCase is

    type TestCase is abstract tagged private;
    type TestCase_Access is access all TestCase'Class;

    --  primitive operation, will be inherited upon derivation
    function Setup (Self : in out TestCase;
                    Parameters : String) return Boolean;
    procedure TearDown (Self : in out TestCase) is null;
    procedure Run (Self : in out TestCase) is abstract;

    procedure SetTest(Test : TestCase_Access;
                      Name : String := "Unknown");

    procedure SetName(Name : String);


private
    type TestCase is abstract tagged null record;
    Instance : TestCase_Access;

    procedure SetName_Wrapper(Message : Interfaces.C.char_array);
    pragma Import (C, SetName_Wrapper, "robottestingframework_test_setname");


    subtype VarCString is Interfaces.C.char_array(Interfaces.C.size_t);
    function SetupTest(Parameters : VarCString)
                       return Interfaces.C.unsigned;
    pragma Export (C, SetupTest, robottestingframework.Test_Setup_Symbol);

    procedure TearDownTest;
    pragma Export (C, TearDownTest, robottestingframework.Test_TearDown_Symbol);

    procedure RunTest;
    pragma Export (C, RunTest, robottestingframework.Test_Run_Symbol);

end robottestingframework.TestCase;
