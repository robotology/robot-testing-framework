--
-- Copyright (C) 2014 Ali Paikan (ali.paikan@gmail.com).
--
--   Redistribution and use in source and binary forms, with or without
--   modification, are permitted provided that the following conditions
--   are met:
--
--   Redistributions of source code must retain the above copyright
--   notice, this list of conditions and the following disclaimer.
--
--   Redistributions in binary form must reproduce the above copyright
--   notice, this list of conditions and the following disclaimer in the
--   documentation and/or other materials provided with the
--   distribution.
--
--   Neither the name of Texas Instruments Incorporated nor the names of
--   its contributors may be used to endorse or promote products derived
--   from this software without specific prior written permission.
--
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
-- "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
-- LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
-- A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
-- OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
-- SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
-- LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
-- DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
-- THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
-- (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
-- OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--
-------------------------------------------------------------------------
with Interfaces.C;

package RTF.TestCase is

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
    pragma Import (C, SetName_Wrapper, "rtf_test_setname");


    subtype VarCString is Interfaces.C.char_array(Interfaces.C.size_t);
    function SetupTest(Parameters : VarCString) 
                       return Interfaces.C.unsigned;
    pragma Export (C, SetupTest, RTF.Test_Setup_Symbol);

    procedure TearDownTest;
    pragma Export (C, TearDownTest, RTF.Test_TearDown_Symbol);

    procedure RunTest;
    pragma Export (C, RunTest, RTF.Test_Run_Symbol);

end RTF.TestCase;

