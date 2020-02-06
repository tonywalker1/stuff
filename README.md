# stuff

Miscellaneous, random, eclectic C++ code and other stuff. ;-)

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
  * **exception:** Ease defining new exceptions, formatting exception messages,
  checking preconditions/postconditions/invariants, handling nested exceptions,
  etc.
  * **unicode** Encoding detection and fast conversions of ASCII saved as
  UTF-16/32.

**io**
  * **filesystem:** Transparent file compression, functional-like algorithms
  for files and directories, etc.

# Dependencies

See the code for a definitive list, but as for now:
* Boost (https://www.boost.org/)
  * Filesystem
  * IOStreams
* Catch2 (https://github.com/catchorg/Catch2)
* libfmt (https://github.com/fmtlib/fmt)

# Compilers and Platforms

Compilers
* GCC
* Clang

Platforms
* Linux (I use Debian Stable)

# Getting Started

...

# Helping

I would love suggestions, fixes, and other contributions. I would be
particularly interested in help supporting other platforms.
Feel free to discuss major additions/contributions.

See CONTRIBUTING for more information.
