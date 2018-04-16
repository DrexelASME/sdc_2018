# ASME SDC 2018 - Formatting Style Guidelines

Formatting style that is being used for the 2018 Drexel ASME SDC robot. Doxygen is an auto-documentation generator for 
UNIX systems. The examples folder gives C++ and Python examples of how to properly document code to work with doxygen 
auto code documentation generator. 

## Table of Contents
- [Formatting Guidelines](#format)
- [Install Doxygen](#install)
- [Package Organization](#organization)
- [Generate Documentation](#generate)

## Revisions List
Full Name | Email | Date | Revision | Description
--- | --- | --- | --- | ---
Frederick Wachter | wachterfreddy@gmail.com | 2018-02-24 | 0.0.0 | Initial document

<a id="format"/>

## Formatting Guidelines

Formatting rules are based on the [Google C++ Style Guidelines](https://google.github.io/styleguide/cppguide.html). 

**NOTE:** **_All files should have a max character counter per line set to 120._**

#### Include Files

Includes should be in alphabetical order and organized as shown below. There should be a space between standard libraries, third party libraries, and custom libraries.

```cpp
#include <standard_libraries>

#include <third_party_libraries>

#include <custom_libraries>
```

#### Naming Conventions

The following table lays out the naming convention used for all files. 

Object | Example
--- | ---
Variables | ``` underscore_variable_names ```
Constants | ``` CONSTANTS_ALL_CAPS ``` 
Defines | ``` DEFINES_ALL_CAPS ```
Floats | ``` 1.0 ``` (add period for whole numbers)
Functions | ``` camelCaseFunctions ```
Classes | ``` CamelCaseClasses ```
Structs | ``` CamelCaseStructs ```
Namespaces | ``` underscore_namespace_names ```
Files | ``` underscore_file_names ```

#### Function Inputs

Function inputs should use the convention shown below. Function inputs that are not modified should be passed by 
reference while function inputs that are modified in the function (modification remains after function call) should be 
passed in as a pointer. An example is shown below the table.

Object | Pointer Type
--- | ---
Unmodified Function Inputs | Pass by Reference
Modified Function Inputs | Pointers

```cpp
void namespace_name::myFunction(int &input, int *output) {
	*output = input;
}
```

#### Header Guards

Header guards should be used on all header files. Below is an example of how to use a header guard.

```cpp
#ifndef FILE_NAME_H_
#define FILE_NAME_H_

// Code goes here

#endif /* FILE_NAME_H_ */
```

#### Commenting

Commenting should only be done if a the opertation of a section or line of code is not obvious to a reader. In most 
cases, variable names and using proper white spacing should provide the user with enough information to understand 
each section and line of code without a comment.

[Back to top](#top)

<a id="install"/>

## Install Doxygen

Run the command below in the terminal window in order to download Doxygen.

```bash
sudo apt-get install doxygen
```

[Back to top](#top)

<a id="organization"/>

## Package Organization

The package organization is expected to be the same as below.

	- <project_name>
		- <project_name>.ino
		- documentation
			- doxygen_config.conf
		... (other files)

[Back to top](#top)

<a id="generate"/>

## Generate Documentation

To generate the documentation from the code in the package directory, run the command below from within the _
documentation_ directory.

```bash
doxygen doxygen_config.conf
```

[Back to top](#top)


