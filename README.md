[![Release](https://img.shields.io/badge/Release-1.0.1-blue.svg)](http://robotology.github.io/robot-testing/index.html)
[![License](https://img.shields.io/badge/Licence-LGPL-blue.svg)](http://robotology.github.io/robot-testing/index.html)
[![Build Status](https://travis-ci.org/robotology/robot-testing.svg?branch=master)](https://travis-ci.org/robotology/robot-testing)
[![Coverage Status](https://coveralls.io/repos/github/robotology/robot-testing/badge.svg?branch=master)](https://coveralls.io/github/robotology/robot-testing?branch=master)


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
using testrunner) to easily run the test cases which are built as plug-ins. Test cases can be organized in test suits using simple XML files. The testrunner uses TinyXml library for parsing the suit XML files. RTF build system check for the installation
of TinyXml and, in case, it cannot find any installed version of TinyXml library, it uses the internal version which is delivered
with the RTF.

- **On Linux/Mac:** The installation is easy, straightforward and uses the CMake build system.
```
    $ git clone https://github.com/robotology/robot-testing.git
    $ cd robot-testing
    $ mkdir build; cd build
    $ cmake ../; make
    $ make install  # Optional!
```

- **On Windows:** The installation is easy, straightforward and uses the CMake build system. Get [Cmake for windows](https://cmake.org/download/) if you have not yet installed. Then simply run the Cmake and, set the project (robot-testing) root folder and the desired build folder. Configure and generate project solution for your favorite IDE (e.g. Visual Studio 13). Then open the solution from your IDE and build the project.   

Configuration
-------------
The only thing you need to configure is the RTF_DIR environment variable so that CMake can find RTF libraries and header files.

- on Linux/Mac:
```
    $ echo 'export RTF_DIR=<path to the RTF build director>' >> ~/.bashrc
    $ echo 'export PATH=$PATH:$RTF_DIR/bin' >> ~/.bashrc
```

- on Windows:
```
    C:\> setx.exe RTF_DIR "<path to the RTF build director>"
    C:\> setx.exe PATH "%PATH%;%RTF_DIR%/<Release/Debug>/bin"
```

*Notice:* If you have **not** installed RTF in the statndard system path (e.g., on Linx without `make install`) then You need to exapnd your system `PATH` environment variable. 


Enabling Python, Ruby, Lua, ... Plugins 
----------------------------------------
To use RTF with other languages, 
 - first you need to install their development packages (e.g. for Python on Linux you need `python-dev`, for Ruby: `ruby-dev` or for Lua: `liblua5.x-dev`). 
 - then you can enable the desired language into RTF Cmake (e.g. ENABLE_PYTHON_PLUGIN=ON for enabling python)
 - compile and build RTF 
 

Tutorials and Examples
-----------------------
* [*Some example codes for using RTF classes.*](http://robotology.github.io/robot-testing/documentation/examples.html)

* [*Using plug-in to develop test cases.*](http://robotology.github.io/robot-testing/documentation/rtf_plugin_example.html)

* [*Using Lua plug-in to develop test cases.*](http://robotology.github.io/robot-testing/documentation/rtf_lua_plugin_example.html)

* [*Using Python plug-in to develop test cases.*](http://robotology.github.io/robot-testing/documentation/rtf_python_plugin_example.html)

* [*Using Ruby plug-in to develop test cases.*](http://robotology.github.io/robot-testing/documentation/rtf_ruby_plugin_example.html)
 
* [*Running test case plug-ins using testrunner*](http://robotology.github.io/robot-testing/documentation/testrunner.html)


Documentation
-------------
* [*See Doxygen generated documentation*](http://robotology.github.io/robot-testing/documentation/index.html)
* [*See RTF website*](http://robotology.github.io/robot-testing/index.html)

Authors
-------
* Ali Paikan ([*personal page*](http://alipaikan.com))
* Silvio Traversaro ([*personal page*](http://www.iit.it/en/people/silvio-traversaro.html))
* Lorenzo Natale ([*personal page*](http://nat.liralab.it/))
