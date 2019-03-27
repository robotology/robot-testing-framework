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

package robottestingframework.Asserter is
    procedure Error(Message : String);
    procedure ErrorIf(Condition : Boolean;
                      Message : String);

    procedure Fail(Message : String);
    procedure FailIf(Condition : Boolean;
                     Message : String);

    procedure TestReport(Message : String);
    procedure TestCheck(Condition: Boolean;
                        Message : String);
    procedure TestFailIf(Condition: Boolean;
                        Message : String);

private
    procedure TestReport_Wrapper(Message : Interfaces.C.char_array);
    pragma Import (C, TestReport_Wrapper, "robottestingframework_test_report");

    procedure TestCheck_Wrapper(Condition : Interfaces.C.unsigned;
                                Message : Interfaces.C.char_array);
    pragma Import (C, TestCheck_Wrapper, "robottestingframework_test_check");


    procedure TestFailIf_Wrapper(Condition : Interfaces.C.unsigned;
                                Message : Interfaces.C.char_array);
    pragma Import (C, TestFailIf_Wrapper, "robottestingframework_test_fail_if");


    procedure Error_Wrapper(Message : Interfaces.C.char_array);
    pragma Import (C, Error_Wrapper, "robottestingframework_assert_error");

    procedure Fail_Wrapper(Message : Interfaces.C.char_array);
    pragma Import (C, Fail_Wrapper, "robottestingframework_assert_fail");

end robottestingframework.Asserter;
