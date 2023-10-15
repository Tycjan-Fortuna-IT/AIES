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

## Conventions

#### **Strict Adherence Required**: It is paramount to strictly adhere to the following naming conventions for our C++ codebase. In order to uphold the highest standards of code consistency and readability, we have a zero-tolerance policy for deviations from these conventions. Reviews will not be accepted if they contain incorrect formatting.

#### Code Formatting
1. **Indentation**: Use a consistent indentation style of 4 spaces for each level of indentation. Do not use tabs for indentation.

```cpp
// Good
if (condition) {
    // Code block
}

// Bad
if (condition) {
        // Inconsistent indentation
}
```

2. **Braces**: Place opening braces on the same line as the function or control structure, and use clear and consistent placement of closing braces.

```cpp
// Good
if (condition) {
    // Code block
} else {
    // Alternate block
}

// Bad
if (condition)
{
    // Inconsistent brace placement
}
```

3. **Spacing**: Maintain a single space between keywords and parentheses.

```cpp
// Good
for (int i = 0; i < count; ++i) {
    // Code block
}

// Bad
for(int i=0;i<count;++i) {
    // Inconsistent spacing
}
```

4. **Functions**: Utilize descriptive names for functions, following the camelCase convention. Begin function names with a verb that describes their action.

```cpp
// Good
void calculateSum(int a, int b);
bool isFileEmpty(std::string fileName);

// Bad
int ab();
bool ef();
```

5. **Line Length**: Limit lines to a maximum of 80-120 characters to ensure readability. If a line exceeds this limit, break it into multiple lines and use appropriate indentation.

```cpp
// Good
longVariableName = anotherVariable + aThirdVariable +
                  aFourthVariable + aFifthVariable;

// Bad
longVariableName = anotherVariable + aThirdVariable + aFourthVariable +
                  aFifthVariable; // Line is too long
```

6. **Comments**: Use comments to explain non-trivial sections of code, but avoid over-commenting simple and self-explanatory code. Place comments above the code they describe and use a consistent comment style (e.g., double slashes for single-line comments and `/* ... */` for multi-line comments).

```cpp
// Good
// Calculate the average of two numbers
float average = (num1 + num2) / 2;

/* This is a multi-line comment
   explaining a complex algorithm. */
int result = complexAlgorithm(input);

// Bad
int x = 10; // Set x to 10
```

7. **Whitespace**: Use whitespace for better code readability. Add blank lines between functions, logical sections, and include necessary space around operators and keywords.

```cpp
// Good
void function1() {
    // Code
}

void function2() {
    // Code
}

// Bad
void function1() {
    // Code
}
void function2() {
    // Code
}
```

8. **File Organization**: Organize your code files logically. Place related functions and classes in the same file and use consistent file naming conventions. Group related header and source files together.

9. **Include Guards**: Use include guards to prevent multiple inclusions of the same header file. The format for include guards should be `#pragma once` or `#ifndef/#define/#endif`.

```cpp
// Good
#pragma once

#ifndef MY_HEADER_H
#define MY_HEADER_H

// Header content

#endif // MY_HEADER_H

// Bad
#ifndef HEADER_H
#define HEADER_H

// Header content

#endif
```
#### Additional Guidelines

10. **C++11 Features**: If possible, prefer using modern C++11 or later features and conventions, such as auto, range-based for loops, and smart pointers.

11. **Consistent Line Endings**: Ensure consistent line endings (e.g., LF for Unix and Linux, CRLF for Windows) in your code files to prevent platform-specific issues.

12. **Comments**: Include clear and concise comments to explain complex code logic, algorithm choices, and non-obvious implementation details.

13. **Documentation**: Maintain up-to-date and comprehensive documentation for all classes, functions, and public interfaces.

14. **Code Organization**: Organize code logically into meaningful functions and classes. Avoid overly long functions and classes.

15. **Error Handling**: Handle exceptions and errors gracefully with meaningful error messages.

16. **Testing**: Develop unit tests for all functions and classes to ensure code correctness or `just test` provided functionality.

### This section describes general naming conventions:

| Kind                               | Convention        | Example                | Description                                          |
| ---------------------------------- | ------------------ | ---------------------- | ---------------------------------------------------- |
| Classes                            | `PascalCase`      | `MyClass`              | Class names should use PascalCase.                  |
| Structs                            | `PascalCase`      | `MyStruct`             | Struct names should also use PascalCase.            |
| Methods/Member Functions           | `PascalCase`      | `MyMethod`             | Method names should use PascalCase.                 |
| Public Member Variables             | `PascalCase`      | `MyPublicVariable`     | Public member variable names should use PascalCase. |
| Protected Member Variables          | `m_PascalCase`    | `m_MyProtectedVariable` | Protected member variable names should start with 'm' and use PascalCase. |
| Private Member Variables            | `m_PascalCase`     | `m_MyPrivateVariable`   | Private member variable names should start with 'm' and use PascalCase. |
| Static Member Variables             | `s_PascalCase`    | `s_MyStaticVariable`   | Static member variable names should start with 's' and use PascalCase. |
| Local Variables                     | `camelCase`       | `myLocalVariable`      | Local variable names should use camelCase.           |
| Function Parameters                 | `camelCase`       | `myParameter`          | Function parameter names should use camelCase.      |
| Enumerations and Enum Members       | `PascalCase`, `ALL_CAPS`      | `MyEnum`, `OptionOne`, `UP`  | Enumeration names and members should use PascalCase or if short ALL_CAPS. |
| Namespaces                          | `PascalCase`      | `MyNamespace`          | Namespace names should use PascalCase.               |
| Macros/Preprocessor Constants       | `ALL_CAPS`         | `MY_MACRO_CONSTANT`    | Macros and preprocessor constants should use ALL_CAPS. |
| Type Aliases (using `using`)        | `PascalCase`     | `using MyType = int;`  | Type aliases created using `using` should use PascalCase. |
| File Names                          | `PascalCase`      | `MyFileName.cpp`       | File names should use PascalCase. And should match class name (if applicable)                  |
| Boolean Variables                   | `is/has/can + Verb` | `isReady`, `hasData`, `canModify` | Boolean variable names should use a prefix like 'is', 'has', or 'can', followed by a verb or description. |
| Getter and Setter Functions         | `GetVariable`, `SetVariable` | `GetAge`, `SetScore` | Getter and setter functions should use GetVariable and SetVariable naming for variable access. |
| Boolean Functions (Returning a Boolean) | `Is/Has/Can + Verb` | `IsValid`, `HasPermission` | Boolean functions that return a boolean value should use Is, Has, or Can as a prefix, followed by a verb or description. |
| Iterators                            | `it + Description`, `it` | `itBegin`, `itEnd`, `it` | Iterator names should use 'it' as a prefix, followed by a description. 'it' by itself can be used for generic iterators. |
| Function Overloads                 | `FunctionName` and `FunctionName` | If you have multiple function overloads, maintain the function name in PascalCase. Overloads should be distinguished by their parameter lists, not by altering the function name.
| Constants                          | `ALL_CAPS`         | `PI`, `MAX_VALUE`        | Constants should use ALL_CAPS and provide descriptive names. They are often used for values that should not change during the program's execution.
| Global Variables                   | `g_PascalCase`     | `g_GlobalValue`        | Global variables should be avoided, but if necessary, they should start with 'g' to signify their global scope.
| Template Parameters                | `T`, `U`, `V`, etc. | Template parameters are typically represented with single uppercase letters such as `T`, `U`, and `V`.
| Lambda Functions                   | `camelCase`        | `myLambdaFunction`      | Lambda function names should use camelCase. They are essentially function objects and should follow the same conventions as local functions.
| User-Defined Literals              | `operator ""` + `PascalCase` | User-defined literals use the `operator ""` syntax followed by a PascalCase identifier. For example, `operator ""MyLiteral`.
| Function Objects (Functors)        | `PascalCase`       | Functors or function objects should use PascalCase for their names. These are classes or structs that provide `operator()` overloads and act like functions.
| Non-member, Non-friend Functions   | Non-member, non-friend functions should have names that are meaningful and describe their functionality. Consider using camelCase or PascalCase, depending on the context.
| Compiler Directives (e.g., `#ifdef`, `#ifndef`) | Compiler directives should use `ALL_CAPS`. These are preprocessor instructions, and clear naming enhances code readability.
| `constexpr` Variables and Functions | PascalCase for variables and PascalCase or camelCase for functions | constexpr int MyConstExprVariable, constexpr int myFunction() | Variables and functions declared as constexpr should use PascalCase for their names. For functions camelCase.

#### **Commit Convention:** All commits should be in English and include a descriptive message that provides clear and concise information about the changes made.

#### **Branch Name Convention:** Branch names should be informative and reflect the purpose of the branch. Follow a convention like `feature_feature_name` or `bugfix_issue_description` to provide context.

#### **Pull Request (PR) Structure:** PRs should include a clear and concise description, summarizing the purpose and changes. The PR body should provide detailed information, context, and testing steps. Each PR should be linked to the related issue (if applicable).

**Branch Management:**

- **Master Branch:** The `master` branch should always represent the production-ready code. No direct commits or pushes to this branch are allowed. All changes to `master` should be made through a Pull Request (PR) after thorough review and testing.

- **Development (Dev) Branch:** The `dev` branch is the main development branch. It serves as a staging area for ongoing work and is where feature branches are merged for integration and testing. Only stable and tested code should be merged into the `dev` branch.

Please ensure that the `master` and `dev` branches are kept clean, with only production-ready and thoroughly tested code making its way into the `master` branch. Development work and feature testing should primarily take place in feature branches created from `dev`.
