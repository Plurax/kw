[![Build Status](http://jenkins.familie-uhlich.de:443/buildStatus/icon?job=kw)](http://jenkins.familie-uhlich.de:443/buildStatus/icon?job=kw)

# kw
JSON + shared libraries = your c++ execution salad... 

This project is currently a work in progress.

# Purpose
For prototyping IoT applications, it is often needed to do some event 
processing with timers or other event sources. To enable developers to get fast into the job of 
the focussed sensor implementations, this library was created.
Furthermore the lib offers the possibility to configure applications via JSON configs and load 
parts of the application from shared libraries, to get more flexibility.

# Build

For building you need boost. The json lib is integrated as submodule.

```bash
apt-get install libboost-all-dev
git clone ...
git submodule init
git submodule update --depth 1
mkdir build
cd build
cmake ..
make
```

After that you will have the shared object of the library libkw.so and an executable kwRunner available in `build/lib` and `build/bin`.
There is a configuration file available which contains already another handler library. If you run the executable without this you will at least get not found outputs on the console.
Assuming you are in `build/bin` you can verify this via:

```bash
./kwRunner ../../config/ExampleConfig.cfg
```
