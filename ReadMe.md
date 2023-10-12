<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Adam-Gladstone/SoftwareInteroperability/">
    <img src="Images/software-80.png" alt="logo" width="80" height="80">
  </a>

  <h3 align="center">SoftwareInteroperability</h3>

  <p align="center">
    <br />
    <a href="https://github.com/Adam-Gladstone/SoftwareInteroperability"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Adam-Gladstone/SoftwareInteroperability/issues">Report Bug</a>
    ·
    <a href="https://github.com/Adam-Gladstone/SoftwareInteroperability/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#projects">Projects</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#features">Features</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
_SoftwareInteroperability_ is a set of projects that form a companion to the book: _C++ Software Interoperability for Windows Programmers: Connecting C++ code to C#, R and Python clients._

The purpose of the projects is to demonstrate how to connect a simple C++ codebase to 
- C# (and .NET) using C++/CLI
- R using Rcpp
- Python using raw python, boost.python and pybind11. 

The C++ codebase consists of a small library of statistics functions (descriptive statistics, simple linear regression, and hypothesis testing). The projects demonstrate building wrapper components that expose the C++ functionality to other client languages.

### Update
I have added two further projects:
- [StatisticsLibrary](README-StatisticsLibrary.md)
- [StatisticsViewer](README-StatisticsViewer.md)

These projects together provide an updated alternative to using the C++/CLI for connecting native C++ to .NET. This is developed in the projects __StatsLib__, __StatsCLR__, and __StatsClient__. The __StatsExcel__ project also makes use of the .NET wrapper component but from an Excel AddIn. The new projects use the same common codebase but create a Windows Runtime Component wrapper around the native C++ library. This is then consumed in a C# desktop application written with WinUI 3.0.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Projects
A brief description of each of the projects follows:

* __Common__ contains two subdirectories: \include and \source. These contain the common header and source files that form the core of the C++ statistics library.
* __Data__ contains a number of small datasets that we use at various points for testing.
* __StatsATLCOM__ is a side-project that illustrates an alternative approach to connecting C++ to .NET, using COM.
* __StatsCLR.UnitTests__ is a C# unit test library that tests the basic statistics functionality from .NET.
* __StatsCLR__ is a C++/CLI wrapper. This component connects the C++ static library (StatsLib) to C# (and .NET).
* __StatsClient__ is a basic C# console application that exercises the functionality from the statistics library via the StatsCLR wrapper component with a minimal user interface.
* __StatsConsole__ is a Windows console application. This application demonstrates the basic functionality of the statistics library with a minimal user interface.
* __StatsConsoleCB__ is a Windows console application project using CodeBlocks. This is useful to debug C++ code using gdb on Windows.
* __StatsDll__ is a dynamic-link library version of the statistics library.
* __StatsExcel__ is a C# library project. This component connects Excel to the StatsCLR wrapper component and allows Excel to use the functionality available in the statistics library.
* __StatsLib__ is a static link library version of the statistics library. Both this and the previous component share the same C++ source code.
* __StatsLibCB__ is the CodeBlocks project that we use for building the R/RStudio ABI compatible static library. 
* __StatsLibCM__ is a CMake equivalent of the StatsLibCB project. It allows building the library from Visual Studio in place of CodeBlocks.
* __StatsLibTest__ is a Windows console application. We use this specifically as a unit-testing application based on GoogleTest.
* __StatsPython__ is a Visual Studio Code Python project containing a number of scripts that use the statistics library functionality.
* __StatsPythonBoost__ is a Boost.Python wrapper. This component connects C++ code to Python.
* __StatsPythonPyBind__ is a PyBind wrapper. This component connects C++ code to Python.
* __StatsPythonRaw__ is a CPython wrapper. This component connects C++ code to Python. The reason for having three components that do essentially the same thing is to cover different approaches to connecting C++ to Python.
* __StatsR__ is the Rcpp wrapper, built using Rtools via RStudio. 
* __StatsViewer__ is a Windows MFC application. This application is used to demonstrate using the functionality available in the statistics library in a GUI application.

The following projects build and distribute a windows runtime component: *StatisticsLibraryWRC*
* __StatisticsLibrary__
* __StatisticsLibraryWRC__
* __StatisticsLibraryProjection__

This project is described here [StatisticsLibrary](README-StatisticsLibrary.md)

The following projects consume the *StatisticsLibraryWRC* component
* __StatisticsConsole__
* __StatisticsViewerWinUI__

This project is described here [StatisticsViewer](README-StatisticsViewer.md)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* Visual Studio 2019
* C++17
* Boost 1.81

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

The project can be downloaded from the GitHub repository in the usual way.

### Prerequisites
Boost 1.81

The solution makes use of the following packages
* Accord 3.8.0
* Accord.Controls 3.8.0
* Accord.IO 3.8.0
* Accord.MachineLearning 3.8.0
* Accord.Math 3.8.0
* Accord.Statistics 3.8.0
* CommunityToolkit.Mvvm 8.2.1
* CommunityToolkit.UinUI.UI.Controls.DataGrid 7.1.2
* Excel-DNA 1.6.0
* ExcelDna.AddIn 1.6.0
* ExcelDna.Integration 1.6.0
* Microsoft.Extensions.DependencyInjection 7.0.0
* Microsoft.googletest.v140.windesktop.msvcstl.rt-dyn 1.8.1.7
* Microsoft.NETCore.UniversalWindowsPlatform 6.2.14
* Microsoft.Windows.CppWinRT 2.0.230706.1
* Microsoft.Windows.CsWinRT 2.0.3
* Microsoft.Windows.SDK.BuildTools 10.0.25188-preview
* Microsoft.WindowsAppSDK 1.4.231008000
* MSTest.TestAdapter 3.0.2
* MSTest.TestFramework 3.0.2
* SharpZipLib 1.4.2
* System.Buffers 4.5.1
* System.Memory 4.5.5
* System.Numerics.Vectors 4.5.0
* System.Runtime.CompilerServices.Unsafe 6.0.0
* System.Threading.Tasks.Extensions 4.5.4
* WinUIEx 2.3.1
* ZedGraph 5.1.7

Additionally, for developing the R package, we use R 4.3.1, rtools 4.3 and RStudio.

For the python development, we use Python 3.9.

### Installation
There are no specific installation requirements.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Features
The wrapper components make use of:
* C++/CLI for connecting to C# (.NET).
* Rcpp for connecting to R.
* Boost.Python and PyBind for connecting to Python.
* WinRT/C++ for connecting a C# WinUI3.0 desktop application to a C++ static library.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ROADMAP -->
## Roadmap

Future directions:
- [ ] Add Changelog

See the [open issues](https://github.com/Adam-Gladstone/SoftwareInteroperability/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the GPL-3.0 License. See `LICENSE.md` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Adam Gladstone - (https://www.linkedin.com/in/adam-gladstone-b6458b156/)

Project Link: [SoftwareInteroperability](https://github.com/Adam-Gladstone/SoftwareInteroperability)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Helpful resources

* [Img Shields](https://shields.io)
* [GitHub Pages](https://pages.github.com)
* [Icons8](https://icons8.com/icons/set/software)
* [Font Awesome](https://fontawesome.com)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- PROJECT SHIELDS -->

[![Issues][issues-shield]][issues-url]
[![GPL-3 License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[issues-shield]: https://img.shields.io/github/issues/Adam-Gladstone/SoftwareInteroperability.svg?style=for-the-badge
[issues-url]: https://github.com/Adam-Gladstone/SoftwareInteroperability/issues

[license-shield]: https://img.shields.io/github/license/Adam-Gladstone/SoftwareInteroperability.svg?style=for-the-badge
[license-url]: https://github.com/Adam-Gladstone/SoftwareInteroperability/LICENSE.md

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/adam-gladstone-b6458b156/
