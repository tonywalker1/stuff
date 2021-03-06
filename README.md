# NOTICE:

What a year 2020 has been (not in a positive way)! I have finally have the 
time to return to this project. As such, I have been convinced to make some 
major structural changes AND actually do some innovative things with the 
library.

This has a few major implications:
1. I will start splitting the library into small (mostly) standalone libraries.
2. I will relicense the code to something less restrictive (probably MIT).
3. I will leave this library here for a while, but unmaintained. **Eventually, 
   I will remove this library.**

# stuff

A library of miscellaneous, random, eclectic C++ code and other stuff. ;-)

# Introduction

This library is my attempt to collect code I have written over the years into
a shareable and reusable form. At the moment, I have no real agenda or plan
other than for this library to be useful. Also, I don't intend for this library
to solve some grand problem. It will probably always be a collection of useful
but random stuff.

If you find this library useful, I would love to hear about it!

# Goals

* Use the latest C++ standard, techniques, and practices.
* Prefer the standard library, libraries on track for standardization, or Boost.

# Library Contents
(May be slightly out-of-date. See code for definitive list of contents.)

**algorithm**
  * **output:** Simplify dumping containers. Great for debugging.
  * **random:** Simple wrapper for generating random integers and real numbers.

**container**
  * **byte_array** Array of bytes. Useful for handling Unicode, compressed   
  data, etc.
  * **string_array** Array of strings (for convenience, clarity, and brevity).

**core**
  * **exception:** Ease defining new exceptions, formatting exception messages,
  checking preconditions/postconditions/invariants, handling nested exceptions,
  etc.
  * **units** Compile-time conversions for memory buffers, etc.

**datetime**
  * **types** Wrapper for types (as C++20 evolves) and bake-in nanoseconds.
  * **datetime** Various, useful date/time operations.
  * **financial** Date/time operations related to financial data.

**io**
  * **filesystem:** Transparent file compression, functional-like algorithms
  for files and directories, etc.

**string**
  * **convert** Fast string to integer/floating point conversions.
  * **split** Fast string tokenizing.

**unicode**
  * **detect** Encoding detection.
  * **convert** Fast conversions of ASCII saved as UTF-16/32.

# Dependencies

See the code for a definitive list, but as for now:
* Boost (https://www.boost.org/)
  * Convert
  * Filesystem
  * IOStreams
  * Optional
* Catch2 (https://github.com/catchorg/Catch2)
* Date (Accepted for C++20; https://github.com/HowardHinnant/date)
* libfmt (Accepted for C++20; https://github.com/fmtlib/fmt)

# Compilers and Platforms

Compilers
* GCC
* Clang

Platforms
* Linux (I use Debian Stable)

# Build Options

* **STUFF_WITHOUT_TESTS** [Default: OFF]  Do not build tests when ON.
* **STUFF_WITHOUT_BENCHMARKS** [Default: OFF]  Do not build benchmarks when ON.

To use the above build options with CMake, do the following:
```
cmake -D<option>=ON|OFF .. && make -j
```


# Getting Started

...

# Helping

I would love suggestions, fixes, and other contributions. I would be
particularly interested in help supporting other platforms.
Feel free to discuss major additions/contributions.

See CONTRIBUTING for more information.
