[![Build Status](https://jenkins.familie-uhlich.de/buildStatus/icon?job=kw)](https://jenkins.familie-uhlich.de/buildStatus/icon?job=kw)

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
There is a configuration file available which contains a basic handler from kw shared object itself.
Assuming you are in `bin` you can verify this via:

```bash
./kwRunner ../config/ExampleConfig.cfg
```

# Tests and coverage

Use 
```
cmake -DKW_Coverage=1 -DBuild_Type=Debug -DKW_BuildTests=1 ..
make
make test
make lcov_html
```
to build also tests and coverage.
