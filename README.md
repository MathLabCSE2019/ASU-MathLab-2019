![Screenshot](g1_cover.png)

### Contents
* [Overview](#overview)
* [Specifications](#specifications)
* [Phases](#phases)
* [Phase 1: Core Operations](#phase-1-core-operations)
* [Phase 2: Advanced Operations and Tuning](#phase-2-advanced-operations-and-tuning)
* [How to use ?](#how-to-use-)
* [Our Team](#our-team)
* [Contribution](#contribution)
* [Author](#author)
* [Licence](#licence)


## Overview

Implementation of a mathematical library software similar to Matlab and Octave .

## Specifications

* Development using **C/C++**
* Development under **Linux** OS like [Ubuntu](https://www.ubuntu.com/) or **Linux** Environment like [Cygwin](https://www.cygwin.com/)
* Production to **Linux** Server ([CentOS 6.7](https://www.centos.org/))
* Any **C/C++** IDE works under **Linux** (like [Code::Blocks](http://www.codeblocks.org/))
* [G++](https://gcc.gnu.org/) Compiler and Makefile are required
* Source controlling , Issues tracking and Documentation using ([Git](https://git-scm.com/)**/**[GitHub](https://github.com/))

## Phases

1. Core operations (3 Weeks)
2. Advanced Operations and Tuning (3 Weeks)
3. Advanced system operations (4 Weeks)

## Phase 1: Core Operations
### Requirements

* Implementation of C++ class for matrix
* Supporting dynamic creation and destruction of matrices of any size
* Supporting addition, subtraction, multiplication, transpose and division
* Processing input user commands and showing results directly
* Processing input file, showing each step result then exiting

### Targets

* Providing correct result identical to Matlab or Octave
* Fastest response time for large inputs

### Examples

```bash
A = [1.4 2.2 3.2; 4.4 5.4 6.4; 3.3 4.2 2.2];
B = [1.5 4.1 5.4; 3.1 4.2 1.2; 3.2 4.3 2.2];
C = A + B
D = A - B
E = A * B
F = A / B
G = A’
```

## Phase 2: Advanced Operations and Tuning

### Requirements

* Supporting mathematical functions (Trigonometric, Logarithmic, Roots, Power)
* Supporting mathematical expressions (Either with **dot** or not)
* Supporting flexible matrix parser (Accept matrix in matrix, expressions and variables)
* Supporting error handling (Do not crash for invalid input)

### Targets

* Providing correct result identical to Matlab or Octave
* Fastest response time for large inputs
* Supporting many mathematical operations

### Examples

In command line :

```bash
A = 5.5 + 12 * sin(0.4) + 2.2^4;
B = [1.2 2.3 A;[1.3 2.4;4.6 1.3],[3.2;7.8]];
C = [[B [3.4; 2.1; 3.5+9.1]]
1.2^3 3+1.2 15/(2.1+10*sin(0.12)) 1.2]
D = rand(4, 4)
E = eye(4, 4)
F = zeros(2, 3)
G = ones(3, 6)
L = (1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) -
12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6))
X = ((C*D .+ 4)./2.1 + sqrt(D))./C.^2
Y = (C^3 * sin(1./D))^(0.1)
```

## How to use ?

wr have three files : matrix.cpp , matrix.h , main.cpp and Makefile

### Compilation : Using 2 methods with command line

#### manual command :
```bash
g++ main.cpp matrix.cpp -o matrix
```
#### using the given makefile :
```bash
make matrix
```

### Running the code
```bash
./matrix example.m
```
where example.m is a test file with a given input inside

### User Interfacing
* User can input more lines to the command line the same as matlab and octave but it's not a must
* User can clear screen by typing ```clc```
* User can exit the software by typing ```exit``` , ```Exit``` or ```0``` or ```Quit``` or ```quit```
* If the user is stuck , he can type ```help``` to see all the software commands

## Our Team

Grouping is based on [responsibilities distribution of Phase 2](https://github.com/MathLabCSE2019/AsuMathLabG01/issues/2)

### Group 1
* Shimaa Hassan
* Mahmoud Hamdy
* Mohamed El Morsy
* Ahmed Tolba
* Mohamed El Morsy
* Menna Mohamed

### Group 2
* Menna Adel
* Nourhan Nasr

### Group 3
* Doaa Essam
* Hanan Samir

___

## Contribution

Anyone can contribute to this project in two conditions :

### Forking 
```Fork``` the project to your account and if you want to add your update , make a pull request

### Committment to our coding style
#### functions
In .h files
```bash
<return_type> <function_identifier> (<parameters_list>);
```

In .cpp files (if it's not a class)
```bash
<return_type> <function_identifier> (<parameters_list>) //function header
{
    //statements 
    //(function body)
}
```

In .cpp files (if it's a class)
```bash
<return_type> <class_identifier>::<function_identifier> (<parameters_list>) //function header
{
    //statements 
    //(function body)
}
```
#### loops
```bash
for(<initialization> ; <condition> ; <increment>)
{
    //body
}
```
```bash
while(<condition>)
{
    //body
}
```
```bash
if(<condition>)
{
    //do something
}
else if(<condition>)
{
    //do something
}
else
{
    //do something
}
```
___

## Author

* [Mahmoud Hamdy](https://github.com/Mahmoud-Hamdyy)

___

## Licence

This project is licensed under the Apache 2.0 License - see the [LICENSE.md](https://github.com/MathLabCSE2019/AsuMathLabG01/blob/add-license-1/LICENSE) file for details



