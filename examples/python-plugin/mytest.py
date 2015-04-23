'''
 Copyright (C) 2015 iCub Facility
 Authors: Ali Paikan
 CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
'''
 
'''
 TestCase table is used by the lua plugin loader
 to invoke the corresponding methods:

 TestCase.setup = function(options) ... return true end
 TestCase.run = function() ... end 
 TestCase.tearDown = function() ... end 

 The following methods are for reporting, failure or assertions: 

 TestCase.setName(name)             : sets the test name
 TestCase.testReport(msg)           : reports a informative message
 TestCase.testCheck(condition, msg) : reports a failure message
 TestCase.assertError(msg)          : throws an error exception with message
 TestCase.asserFail(msg)            : throws a failure exception with message
'''

import rtf

class TestCase:
    def setup(self, param):
        print 'Seting up ...'
        rtf.setName("Ali")
        return True

    def tearDown(self):
        print 'tearing Down ...'


    def run(self):
        print 'Running ...'
        
