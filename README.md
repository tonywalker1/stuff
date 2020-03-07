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

**core**
  * **byte_array** Array of bytes. Useful for handling Unicode, compressed
  data, etc.
  * **datetime** Date/time convenience functions, fast I/O, etc.
  * **exception:** Ease defining new exceptions, formatting exception messages,
  checking preconditions/postconditions/invariants, handling nested exceptions,
  etc.
  * **string_array** Array of strings (for convenience, clarity, and brevity).
  * **string** Fast string conversions, tokenizing, etc.
  * **unicode** Encoding detection and fast conversions of ASCII saved as
  UTF-16/32.
  * **units** Compile-time conversions for memory buffers, etc.

**io**
  * **filesystem:** Transparent file compression, functional-like algorithms
  for files and directories, etc.

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
