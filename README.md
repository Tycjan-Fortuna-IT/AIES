***

# Getting Started
Fully supported and tested on Visual Studio 2022 and Ubuntu 22.04 LTS clang compiler.

## <ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/Tycjan-Fortuna-IT/AIES.git`.

If the repository was previously cloned non-recursively, use `git submodule update --init` to clone necessary submodules.

## <ins>**2. Prerequisites:**</ins>
- Visual Studio 2022 with C++ 20 support
- [Premake 5.0-beta2](https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip)


## <ins>**3. Building the project:**</ins>
- Run `scripts/WindowsBuild.bat` to generate Visual Studio 2022 solution.
- Open the solution file `ImageProcessing.sln` in Visual Studio 2022.
- Select the desired configuration (e.g. `Debug`).
- Run obtained `.exe` file.
