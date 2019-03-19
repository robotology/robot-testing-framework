[![Release](https://img.shields.io/github/tag/robotology/robot-testing.svg?label=Release)](https://github.com/robotology/robot-testing/tags)
[![License](https://img.shields.io/badge/Licence-LGPL-blue.svg)](http://robotology.github.io/robot-testing/index.html)
[![Build Status](https://travis-ci.org/robotology/robot-testing.svg?branch=master)](https://travis-ci.org/robotology/robot-testing)
[![Coverage Status](https://coveralls.io/repos/github/robotology/robot-testing/badge.svg?branch=master)](https://coveralls.io/github/robotology/robot-testing?branch=master)

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](http://robotology.github.io/robot-testing/documentation/robottestingframework_plugin_example.html)
[![Language](https://img.shields.io/badge/Language-ADA-blue.svg)](https://github.com/robotology/robot-testing/tree/master/examples/ada-plugin)
[![Language](https://img.shields.io/badge/Language-Python-blue.svg)](http://robotology.github.io/robot-testing/documentation/robottestingframework_python_plugin_example.html)
[![Language](https://img.shields.io/badge/Language-Ruby-blue.svg)](http://robotology.github.io/robot-testing/documentation/robottestingframework_ruby_plugin_example.html)
[![Language](https://img.shields.io/badge/Language-Lua-blue.svg)](http://robotology.github.io/robot-testing/documentation/robottestingframework_lua_plugin_example.html)



Robot Testing Framework
=======================
Robot Testing Framework is a generic and multi-platform testing framework for
the [test driven development (TDD)](https://en.wikipedia.org/wiki/Test-driven_development)
which is initially designed for the robotic systems.
However, it can be used for any TDD system.
The framework provides functionalities for developing and running unit tests in
a language and middleware independent manner. The test cases are developed as
independent plug-ins (i.e., using scripting languages or built as dynamically
loadable libraries) to be loaded and executed by an automated test runner.
Moreover, a fixture manager prepares the setup (e.g., running robot interfaces,
simulator) and actively monitors that all the requirements for running the tests
are satisfied during the execution of the tests.
These functionalities along with other facilities such as the test result
collector, result formatter and remote interface allow for rapid development of
test units to cover different levels of system testing (see the block diagram).

![robottestingframework-arch](/doc/robottestingframework_arch.png)


Installation
------------
Robot Testing Framework library does not depend on any external library.
The Robot Testing Framework framework has a robottestingframework-testrunner
utility (see Running test case plug-ins using robottestingframework-testrunner)
to easily run the test cases which are built as plug-ins.
Test cases can be organized in test suites using simple XML files.
The robottestingframework-testrunner uses TinyXml library for parsing the suite
XML files.
Robot Testing Framework build system check for the installation of TinyXml and,
in case, it cannot find any installed version of TinyXml library, it uses the
internal version which is delivered with the Robot Testing Framework.

- **On Linux/Mac:** The installation is easy, straightforward and uses the CMake
  build system.
```
    $ git clone https://github.com/robotology/robot-testing.git
    $ cd robot-testing
    $ mkdir build; cd build
    $ cmake ../; make
    $ make install  # Optional!
```

- **On Windows:** The installation is easy, straightforward and uses the CMake
  build system.
  Get [CMake for windows](https://cmake.org/download/) if you have not yet
  installed.
  Then simply run the CMake and, set the project (robot-testing) root folder and
  the desired build folder.
  Configure and generate project solution for your favorite IDE (e.g. Visual
  Studio 17).
  Then open the solution from your IDE and build the project.

Configuration
-------------
The only thing you need to configure is the `RobotTestingFramework_DIR`
environment variable so that CMake can find Robot Testing Framework libraries
and header files.

- on Linux/Mac:
```
    $ echo 'export RobotTestingFramework_DIR=<path to the Robot Testing Framework build director>' >> ~/.bashrc
    $ echo 'export PATH=$PATH:$RobotTestingFramework_DIR/bin' >> ~/.bashrc
```

- on Windows:
```
    C:\> setx.exe RobotTestingFramework_DIR "<path to the Robot Testing Framework build director>"
    C:\> setx.exe PATH "%PATH%;%RobotTestingFramework_DIR%/<Release/Debug>/bin"
```

*Notice:* If you have **not** installed Robot Testing Framework in the standard
system path (e.g., on Linux without `make install`) then You need to expand your
system `PATH` environment variable.


Enabling Python, Ruby, Lua, ... Plugins
----------------------------------------
To use Robot Testing Framework with other languages,
 - first you need to install their development packages (e.g. for Python on
   Linux you need `python-dev`, for Ruby: `ruby-dev` or for
   Lua: `liblua5.x-dev`).
 - then you can enable the desired language into Robot Testing Framework CMake
   (e.g. `ENABLE_PYTHON_PLUGIN=ON` for enabling python)
 - compile and build Robot Testing Framework


Tutorials and Examples
-----------------------
* [*Some example codes for using Robot Testing Framework classes.*]( http://robotology.gitlab.io/docs/rtf/master/examples.html)

* [*Using plug-in to develop test cases.*](http://robotology.gitlab.io/docs/rtf/master/robottestingframework_plugin_example.html)

* [*Using Lua plug-in to develop test cases.*](http://robotology.gitlab.io/docs/rtf/master/robottestingframework_lua_plugin_example.html)

* [*Using Python plug-in to develop test cases.*](http://robotology.gitlab.io/docs/rtf/master/robottestingframework_python_plugin_example.html)

* [*Using Ruby plug-in to develop test cases.*](http://robotology.gitlab.io/docs/rtf/master/robottestingframework_ruby_plugin_example.html)

* [*Running test case plug-ins using robottestingframework-testrunner*](http://robotology.gitlab.io/docs/rtf/master/robottestingframework-testrunner.html)


Documentation
-------------
* [*See Doxygen generated documentation*](http://robotology.gitlab.io/docs/rtf/master/index.html)
* [*See Robot Testing Framework website*](http://robotology.github.io/robot-testing/index.html)

Authors
-------
* Ali Paikan ([*personal page*](http://alipaikan.com))
* Silvio Traversaro ([*personal page*](http://www.iit.it/en/people/silvio-traversaro.html))
* Lorenzo Natale ([*personal page*](http://nat.liralab.it/))
