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

With robottestingframework.TestCase;   use robottestingframework.TestCase;

package MyTest is

    type MyTest is new TestCase with null record;

    overriding function Setup (Self : in out MyTest;
                               Parameters : String) return Boolean;
    overriding procedure TearDown (Self : in out MyTest);
    overriding procedure Run(Self : in out MyTest);

    procedure Create;
    pragma Export (C, Create, robottestingframework.Test_Create_Symbol);

private
    function RandomNumber (n: in Positive) return Integer;

end MyTest;

