Robot Testing Framework (RTF)
============================

RTF is a generic testing framework for the test driven development 
of robotic systems. The framework provides functionalities for developing
and running unit tests in a language and middleware independent manner. The
test cases are developed as independent plug-ins (i.e., using scripting languages
or built as dynamically loadable libraries) to be loaded and executed by an 
automated test runner. Moreover, a fixture manager prepares the setup (e.g., 
running robot interfaces, simulator) and actively monitors that all the requirements
for running the tests are satisfied during the execution of the tests. These 
functionalities along with other facilities such as the test result collector, 
result formatter and remote interface allow for rapid development of test units
to cover different levels of testing robotic systems.

Installation
============
$ cd robot-testing-framework
$ mkdir build; cd build
$ cmake ../; make


Running Examples
================
$ cd build/bin
$ ./simple
$ ./simle_suit
$ ./simple_collector
$ ...



