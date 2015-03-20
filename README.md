Robot Testing Framework (RTF)
============================
RTF stands for Robot Testing Framework. It is a generic and multi-platform testing framework for the test driven development (TDD)
which is initially designed for the robotic systems. However, it can be used for any TDD system.
The framework provides functionalities for developing and running unit tests in a language and middleware independent manner. The
test cases are developed as independent plug-ins (i.e., using scripting languages or built as dynamically loadable libraries) to be
loaded and executed by an automated test runner. Moreover, a fixture manager prepares the setup (e.g., running robot interfaces,
simulator) and actively monitors that all the requirements for running the tests are satisfied during the execution of the tests.
These functionalities along with other facilities such as the test result collector, result formatter and remote interface allow
for rapid development of test units to cover different levels of system testing.



Installation
------------
RTF library does not depend on any external library. The RTF framework has a testrunner utility (see Running test case plug-ins
using testrunner) to easily run the test cases which are built as plug-ins. Test cases can be organized in test suits using a
simple XML files. The testrunner uses TinyXml library for parsing the suit XML files. RTF build system check for the installation
of TinyXml and, in case, it cannot find any installed version of TinyXml library, it uses the internal version which is delivered
with the RTF.


Compile and Build
-----------------
The installation is easy, straightforward and uses Cmake building system.
```
    $ cd robot-testing
    $ mkdir build; cd build
    $ cmake ../; make
```

and optionally:
```
    $ make install
```

Configuration
-------------
The only thing you need to configure is the \c RTF_DIR environment variable so that cmake can find RTF libraries and header files.

For example on Linux/Mac:
```
    $ echo 'export RTF_DIR=<path to the RTF build director>' >> ~/.bashrc
```

Alternatively you can add the RTF 'bin' directory to your system PATH variable.


Tutorials
---------
* Using plug-in to develop test cases. (http://robotology.github.io/robot-testing/rtf_plugin_example.html)
* Running test case plug-ins using testrunner. (http://robotology.github.io/robot-testing/testrunner.html)



Documentation
-------------
* See http://robotology.github.io/robot-testing/index.html.


