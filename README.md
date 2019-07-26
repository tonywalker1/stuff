# stuff

Miscellaneous, random, eclectic C++ code and other stuff. ;-)

# Introduction

This library is my attempt to collect code I have written over the years into
a shareable and reusable form. At the moment, I have no real agenda or plan
other than for this library to be useful. Also, I don't intend for this library
to solve some grand problem. It will probably always be a collection of useful
but random stuff.

My only hopes/guidelines for this library are:
* Use the latest C++ standard, techniques, and practices.
* Prefer the standard library, libraries on track for standardization, or Boost.
* Compile with GCC and Clang.
* Work on any modern Linux (I use Debian).

If you find this library useful, I would love to hear about it!

I would love suggestions, fixes, and other contributions. Feel free to discuss
major additions/contributions. See CONTRIBUTING.

# Library Contents
(May be slightly out-of-date. See code for definitive list of contents.)

**core**
  * **exception:** Ease defining new exceptions, formatting exception messages, checking preconditions/postconditions/invariants, handling/outputing nested exceptions, etc.

**io**
  * **filesystem:**

# Dependencies

See the code for a definitive list, but as for now:
* Boost Filesystem (https://www.boost.org/)
* Catch2 (https://github.com/catchorg/Catch2)
* libfmt (https://github.com/fmtlib/fmt)

# Getting Started
