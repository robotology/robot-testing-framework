## YARP support in RTF 

### Compile and Build
To compile the YARP support in RTF, please enable the `ENABLE_MIDDLEWARE_PLUGINS` CMake options. 
Once you enable this option, the `ENABLE_YARP` option should be automatically enabled, if CMake is 
able to find YARP. After that, continue to compile RTF as usual. 

### Configuration
The YARP support in RTF build the fixture plugin for running yarpmanager application as fixtures.
To make sure that your test suites can find the `yarpmanager` fixture plugin, you should add to the 
platform library environment variable the build directory of the RTF plugins. For example, on a Linux 
machine, you can simply add this line to your `.bashrc` file:
~~~
echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<RTF_DIR>/lib' >> ~/.bashrc
~~~

Where RTF_DIR is the build or install directory of RTF. 
