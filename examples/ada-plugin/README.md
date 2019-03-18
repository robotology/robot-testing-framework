The example shows how to develop a test case using
Ada programing language which can be executed using
the Robot Testing Framework `robottestingframework-testrunner`.

Compilation
-----------
Build the project using gnat build system by specifying
the Robot Testing Framework root directory in `RobotTestingFramework_ROOT`.
For example:

```
    $ mkdir build plugin
    $ gprbuild -P mytest.gpr -XRobotTestingFramework_ROOT=/home/foo/robot-testing
```

Alternatively you can set the `RobotTestingFramework_ROOT` environment variable
to point to the RobotTestingFramework root directory; then build the plug-in:

```
    $ mkdir build plugin
    $ gprbuild -P mytest.gpr
```

Running the test case
---------------------
Simply use the `robottestingframework-testrunner` :

```
    $ robottestingframework-testrunner -v -t plugin/libmytest.so
```

