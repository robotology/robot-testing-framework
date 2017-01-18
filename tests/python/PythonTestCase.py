'''
 Copyright (C) 2015 iCub Facility
 Authors: Ali Paikan
 CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
'''
 
'''
 RTF module is automatically imported by the python plugin loader
 to invoke the corresponding test case methods. To develop a new 
 test case simply implement the following class; (setup and tearDown 
 methods are optional) :

 class TestCase:
     def setup(self, param):
         return True

     def run(self):

     def tearDown(self):


 The following methods are for reporting, failure or assertions: 

 RTF.setName(name)             : sets the test name (defualt is the test filename)
 RTF.testReport(msg)           : reports a informative message
 RTF.testCheck(condition, msg) : reports the test message and marks the test as failed if condition is false
 RTF.assertError(msg)          : throws an error exception with message
 RTF.asserFail(msg)            : throws a failure exception with message
'''

class TestCase:
    # setup is called before the test's run to setup 
    # the user defined fixture
    # @return Boolean (True/False uppon success or failure)
    def setup(self, param):
        RTF.setName("PythonTestCase")
        return True
   
    # The implementation of the test goes here
    def run(self):
        RTF.testCheck(5>3, "Cheking RTF.testCheck")
        #RTF.testReport("Cheking RTF.testFailIf")
        #RTF.testFailIf(, "testFailIf")

    # tearDown is called after the test's run to tear down
    # the user defined fixture
    def tearDown(self):
       pass 

        
