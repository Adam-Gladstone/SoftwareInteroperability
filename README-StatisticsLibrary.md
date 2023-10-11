<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Adam-Gladstone/SoftwareInteroperability/">
    <img src="Images/statistics-library.png" alt="logo" width="80" height="80">
  </a>

  <h3 align="center">StatisticsLibrary</h3>

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
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
This is the final project (MediaCollectionWinUI, WeightsAndMeasuresConversion being the first two) in a series of (experimental) projects exploring various alternatives and combinations around Windows desktop application development. The technologies involved are UWP, WinUI3.0, XAML, C#, WinRT/C++. The intention has been to find a satisfactory 'modern' stack that moves away from C# Windows Forms + COM (or C++/CLI) + native C++.

The major difference between this and the previous projects is the use of C#/WinUI rather than C++/WinUI. This brings a host of advantages apart from just the productivity improvement you get when using a language like C# in an environment like Visual Studio 2022. In this project we use MVVM (binding, commanding, DI and IoC). 

Part of the motivation for this project was to update the stack used in my book [Software Interoperability](https://github.com/Apress/cplusplus-software-interoperability-for-windows-programmers). Here we connected a library written in C++ to Excel via a 'managed' C++/CLI component. In the StatisticsLibrary project and its companion [StatisticsViewer](https://github.com/Adam-Gladstone/SoftwareInteroperability) project, this is modernised to use C++17 wrapped in a Windows Runtime Component which is then consumed by C# applications (console and Windows desktop). 

In a previous attempt, we had written a C++ WinUI desktop application StatsViewerWinUI. Inside this (in the Models section) we wrote runtime classes that wrapped the native C++ classes (as we statically link to the StatisticsLibrary) and functions. This acted as a translation/conversion type layer between the WinUI C++ XAML and the native C++. This also meant that we could bind directly the windowing code (XAML C++) to C++ functions.

The problem with this approach was the C++ WinUI3.0 layer. There is no designer (unlike for WPF and UWP applications - but you can get used to it). However, even if there were a designer we would still be 'required' to build a lot of infrastructure (data services, navigation services and so on) in C++ because there is basically no 'out-of-the-box' support for MVVM and such. Contrast this with the template support that you can get using [Windows Community Toolkit](https://github.com/CommunityToolkit/WindowsCommunityToolkit) template wizards for both WPF and importantly for UWP - implying that we can use C++/WinRT with the project. The bottom line is that writing a sophisticated desktop application in C++/WinUI doesn't work well (see the additional issues we had with the MediaCollectionWinUI port). 

As a result of the above, we developed these projects as an alternative stack as follows:
- the user interface in written in C# (using WinUI 3). This is [StatisticsViewer project](https://github.com/Adam-Gladstone/SoftwareInteroperability).
- A separate Windows Runtime Component (StatisticsLibraryWRC) wraps the functionality that we want to expose. This is similar to the StatsCLR component described in my book, and it sits in the same relationship to C# and C++. We build a WRC and a separate C# project to create/build the projection and publish the package. This means that we can consume StatisticsLibraryWRC from a C# desktop application. This has the benefits of using C#, the benefits of using C# WinUI3.0, and not much extra work writing the wrapper using WinRT mechanisms (and distributing this as a .winmd component).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Projects
#### StatisticsLibrary (Universal Windows)
------------------------------------------
This project references the exact same common source and headers written in C++17 that were used to build StatsLib in the [SoftwareInteroperability project](https://github.com/Adam-Gladstone/SoftwareInteroperability). However the static library project is configured as a UWP library (instead of just a plain old Win32 static library).

#### StatisticsLibraryWRC (Universal Windows)
---------------------------------------------
This is a C++ Windows Runtime Component. It is a wrapper component that translates native C++ types into the WinRT space and vice-versa. By doing this the types are made available to C# (and XAML) which means the windows controls can bind directly to these entities.

The interfaces to the underlying native C++ classes are written in IDL 3.0. The (MIDL?) compiler will generate the actual C++ source and header files with stubs for functions using WinRT types and public member variables. To these implementation types we add a private member representing the underlying C++ type. The calls are then forwarded to the C++ type. This is exactly the same releationship that we used in the StatsCLR project but the wrapper type was written in C++/CLI rather than pure C++ (with the use of the WinRT library). 

#### StatisticsLibraryProjection
--------------------------------
In order to use this Windows Runtime Component (above) we need to package it in a C# NuGet project (C# Static Library). As part of the build process we compile the C++ WinRT component to a .winmd component and it is published to a local directory that we can reference in the Manage Package sources.

We consume it in a separate solution (https://github.com/Adam-Gladstone/SoftwareInteroperability).

<p align="right">(<a href="#readme-top">back to top</a>)</p>


### Built With
* Visual Studio 2022
* C++17

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started
The project can be downloaded from the GitHub repository in the usual way.

### Prerequisites
* Boost 1.81
* Windows.CppWinRT version="2.0.220608.4"
* Windows.CsWinRT version="2.0.3"
* Windows.SDK.BuildTools" version="10.0.22621.756"
* WindowsAppSDK" version="1.4.230913002"

### Installation
No specific installation requirements. The StatisticsLibrary depends on Boost 1.81.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage
Open the solution file. Check that the Debug x64 Solution configuration and package is set. Rebuild all. Once the components are built, select the C# project and select Publish... . Set the publishing directory as required. You will need to set this directory in the NuGet package sources in order for the component to be picked up.

A note about versioning.
In general, a specific version number is in the form Major.Minor.Patch[-Suffix], where the components have the following meanings:
- Major: Breaking changes
- Minor: New features, but backwards compatible
- Patch: Backwards compatible bug fixes only
- -Suffix (optional): a hyphen followed by a string denoting a pre-release version (following the Semantic Versioning or SemVer 1.0 convention).

In the StatisticsLibraryProjection project, the .nuspec document specifies the version (0.1.0-prerelease) and the target framework (e.g. "net6.0-windows10.0.22000.0"). When the component is published the path is synthesised from this (e.g. .\statisticslibrary\statisticslibraryprojection\nuget\net6.0-windows10.0.22000.0\publish\win-x64). It is this path that PackageSources needs to be aware of in the NuGet package manager.

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

Project Link: [StatisticsLibrary](https://github.com/Adam-Gladstone/SoftwareInteroperability)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Helpful resources

* [Choose an Open Source License](https://choosealicense.com)
* [Img Shields](https://shields.io)
* [GitHub Pages](https://pages.github.com)
* [Font Awesome](https://fontawesome.com)
* [React Icons](https://react-icons.github.io/react-icons/search)

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
