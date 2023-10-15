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

## Naming conventions

#### **Strict Adherence Required**: It is paramount to strictly adhere to the following naming conventions for our C++ codebase. In order to uphold the highest standards of code consistency and readability, we have a zero-tolerance policy for deviations from these conventions. Reviews will not be accepted if they contain incorrect formatting.

This section describes general naming conventions:


| Kind                               | Convention        | Example                | Description                                          |
| ---------------------------------- | ------------------ | ---------------------- | ---------------------------------------------------- |
| Classes                            | `PascalCase`      | `MyClass`              | Class names should use PascalCase.                  |
| Structs                            | `PascalCase`      | `MyStruct`             | Struct names should also use PascalCase.            |
| Methods/Member Functions           | `PascalCase`      | `MyMethod`             | Method names should use PascalCase.                 |
| Public Member Variables             | `PascalCase`      | `MyPublicVariable`     | Public member variable names should use PascalCase. |
| Protected Member Variables          | `m_PascalCase`    | `m_MyProtectedVariable` | Protected member variable names should start with 'm' and use PascalCase. |
| Private Member Variables            | `m_CamelCase`     | `m_myPrivateVariable`   | Private member variable names should start with 'm' and use camelCase. |
| Static Member Variables             | `s_PascalCase`    | `s_MyStaticVariable`   | Static member variable names should start with 's' and use PascalCase. |
| Local Variables                     | `camelCase`       | `myLocalVariable`      | Local variable names should use camelCase.           |
| Function Parameters                 | `camelCase`       | `myParameter`          | Function parameter names should use camelCase.      |
| Enumerations and Enum Members       | `PascalCase`      | `MyEnum`, `OptionOne`  | Enumeration names and members should use PascalCase. |
| Namespaces                          | `PascalCase`      | `MyNamespace`          | Namespace names should use PascalCase.               |
| Macros/Preprocessor Constants       | `ALL_CAPS`         | `MY_MACRO_CONSTANT`    | Macros and preprocessor constants should use ALL_CAPS. |
| Type Aliases (using `using`)        | `PascalCase`     | `using MyType = int;`  | Type aliases created using `using` should use PascalCase. |
| File Names                          | `PascalCase`      | `MyFileName.cpp`       | File names should use PascalCase.                    |
| Header Guard Macros (in headers)   | `ALL_CAPS`         | `MY_HEADER_GUARD_H`    | Header guard macros in header files should use ALL_CAPS. |
| Boolean Variables                   | `is/has/can + Verb` | `isReady`, `hasData`, `canModify` | Boolean variable names should use a prefix like 'is', 'has', or 'can', followed by a verb or description. |
| Getter and Setter Functions         | `GetVariable`, `SetVariable` | `GetAge`, `SetScore` | Getter and setter functions should use GetVariable and SetVariable naming for variable access. |
| Boolean Functions (Returning a Boolean) | `Is/Has/Can + Verb` | `IsValid`, `HasPermission` | Boolean functions that return a boolean value should use Is, Has, or Can as a prefix, followed by a verb or description. |
| Iterators                            | `it + Description`, `it` | `itBegin`, `itEnd`, `it` | Iterator names should use 'it' as a prefix, followed by a description. 'it' by itself can be used for generic iterators. |

#### **Commit Convention:** All commits should be in English and include a descriptive message that provides clear and concise information about the changes made.

#### **Branch Name Convention:** Branch names should be informative and reflect the purpose of the branch. Follow a convention like `feature_feature_name` or `bugfix_issue_description` to provide context.

#### **Pull Request (PR) Structure:** PRs should include a clear and concise description, summarizing the purpose and changes. The PR body should provide detailed information, context, and testing steps. Each PR should be linked to the related issue (if applicable).

**Branch Management:**

- **Master Branch:** The `master` branch should always represent the production-ready code. No direct commits or pushes to this branch are allowed. All changes to `master` should be made through a Pull Request (PR) after thorough review and testing.

- **Development (Dev) Branch:** The `dev` branch is the main development branch. It serves as a staging area for ongoing work and is where feature branches are merged for integration and testing. Only stable and tested code should be merged into the `dev` branch.

Please ensure that the `master` and `dev` branches are kept clean, with only production-ready and thoroughly tested code making its way into the `master` branch. Development work and feature testing should primarily take place in feature branches created from `dev`.
