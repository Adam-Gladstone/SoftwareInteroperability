# Build & Run Notes

## Introduction
There are a number of different ways to use the [emscripten toolchain](https://emscripten.org/docs/building_from_source/toolchain_what_is_needed.html) depending on the desired output. In this case we are interested in a JavaScript/Wasm output that can be referenced in an html page.
The input is a C++ library - ```StatsLib```, built with clang.

### Setting emscripten environment variables
From Powershell:

- ```dir env: ```		List all environment variables
- ```$Env:EMSDK```	Retrieve the emscripten sdk path


Navigate to the root of the project and run:
- ```.$Env:EMSDK\emsdk_env.ps1```

## Using emcc directly
From the project root directory:

- ```cd lib```
- ```.$Env:EMSDK\emsdk_env.ps1```


### Debug Build
```
emcc --bind module.cpp Conversion.cpp Functions.cpp Classes.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/DataManager.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/DescriptiveStatistics.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/StatisticalTests.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/StatisticsLibrary.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/TimeSeries.cpp -O0 -o StatsLibScript.js -sENVIRONMENT="web" -I D:/Libraries/boost_1_91_0/ -I D:/Development/Projects/C++/SoftwareInteroperability/Common/include/ -std=c++20 -sNO_DISABLE_EXCEPTION_CATCHING --no-entry
copy "StatsLibScript.js" "../web/Debug/StatsLibScript.js"
copy "StatsLibScript.wasm" "../web/Debug/StatsLibScript.wasm"
```

### Release Build - O3
```
emcc --bind module.cpp Conversion.cpp Functions.cpp Classes.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/DataManager.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/DescriptiveStatistics.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/StatisticalTests.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/StatisticsLibrary.cpp D:/Development/Projects/C++/SoftwareInteroperability/Common/source/TimeSeries.cpp -O3 -o StatsLibScript.js -sENVIRONMENT="web" -I D:/Libraries/boost_1_91_0/ -I D:/Development/Projects/C++/SoftwareInteroperability/Common/include/ -std=c++20 -sNO_DISABLE_EXCEPTION_CATCHING --no-entry
copy "StatsLibScript.js" "../web/Release/StatsLibScript.js"
copy "StatsLibScript.wasm" "../web/Release/StatsLibScript.wasm"
```

Once built, ```cd ../web```, open up a browser and if using Visual Studio Code, press the run live-server *Go Live* button.

## Using CMake
The project can also be built using CMake. Currently it is only configured to build debug outputs. From the project root, make a build directory, run the cmake configure command and then build:

```
mkdir build
cd build
emcmake cmake .. 
cmake --build .
```

## Using the Visual Studio emscripten template
For convenience, there is also a Visual Studio emscripten template-based project: StatsLibScript. Open the SoftwareInteroperability.sln. Select the StatsLibScript as the startup project. Build the Debug or Release configuration.
Press F5 to run: the 'WebAssembly Debugger' service is not available (and I am investigating this), but an http server can be launched manually as follows:
1) Open PowerShell from the \web folder: "../SoftwareInteroperability/StatsLibScript/web"
2) Run a local python server: ```python -m http.server 6931```
3) Start the browser. Enter ```localhost:6931``` in the address bar.
4) Navigate to index.html - this contains the link to StatsLibScript.js and StatsLibScript.wasm.
