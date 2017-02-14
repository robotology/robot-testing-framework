The example shows how to develop a test case using 
Ada programing language which can be executed using 
the RTF `testrunner`. 

Compilation
-----------
Build the project using gnat build system by specifying
the RTF root directory in `RTF_ROOT`. For example: 

```
    $ mkdir build plugin
    $ gprbuild -P mytest.gpr -XRTF_ROOT=/home/foo/robot-testing
```

Alternatively you can set the `RTF_ROOT` environment variable
to point to the RTF root directory; then build the plug-in: 

```
    $ mkdir build plugin
    $ gprbuild -P mytest.gpr
```

Running the test case
---------------------
Simply use the `testrunner` : 

```
    $ testrunner -v -t plugin/libmytest.so
```

