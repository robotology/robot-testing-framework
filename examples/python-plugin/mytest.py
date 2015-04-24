'''
 Copyright (C) 2015 iCub Facility
 Authors: Ali Paikan
 CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
'''
 
'''
 rtf module is automatically imported by the python plugin loader
 to invoke the corresponding test case methods. To develop a new 
 test case simply implement the following class; (setup and tearDown 
 methods are optional) :

 class TestCase:
     def setup(self, param):
         return True

     def run(self):

     def tearDown(self):


 The following methods are for reporting, failure or assertions: 

 rtf.setName(name)             : sets the test name (defualt is the test filename)
 rtf.testReport(msg)           : reports a informative message
 rtf.testCheck(condition, msg) : reports a failure message
 rtf.assertError(msg)          : throws an error exception with message
 rtf.asserFail(msg)            : throws a failure exception with message
'''

class TestCase:
    # setup is called before the test's run to setup 
    # the user defined fixture
    # @return Boolean (True/False uppon success or failure)
    def setup(self, param):
        rtf.testReport("Preparing setup...")
        return True
   
    # The implementation of the test goes here
    def run(self):
        rtf.testReport("Checking bigger...")
        rtf.testCheck(5>3, "5 is not bigger than 3.")
        rtf.testReport("Checking smaller...")
        rtf.testCheck(5<3, "5 is not smaller than 3.")

    # tearDown is called after the test's run to tear down
    # the user defined fixture
    def tearDown(self):
        rtf.testReport("Tearing down...")


        
