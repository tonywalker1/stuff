// MIT License
//
// Copyright (c) 2019 Tony Walker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef STUFF_EXCEPTION_H
#define STUFF_EXCEPTION_H

#include <fmt/format.h>
#include <stdexcept>
#include <string>

// Exception Handling
//
// Having been influenced by Boost Exception, I tend to use exception types as
// "tags" that identify the error source rather than file and line.
// For example:
//   STUFF_DEFINE_EXCEPTION(random_number_error, generic_error);
// ...
//   double get_random_double(double lower, double upper)
//   {
//       ...
//       FX_ENSURES(lower <= val, random_number_error, "some message");
//       FX_ENSURES(val < upper, random_number_error, "some message");
//       ...
//   }
// This will generate the following message:
//  "random_number_error: some message"
//
// You can use STUFF_* macros below to throw (possibly nested) exceptions, and
// then unwind them with to_string().

// Define new exception types, see generic_error below.
#define STUFF_DEFINE_EXCEPTION(except, except_base) \
    struct except : public except_base \
    { \
        except(const char* msg)        : except_base(msg) {} \
        except(const std::string& msg) : except_base(msg) {} \
    }


namespace stuff {

    // Default error and base classes for all other exceptions.
    STUFF_DEFINE_EXCEPTION(generic_error, std::runtime_error);

    // Unwind any nested expections.
    std::string to_string(const std::exception& e);

} // namespace stuff


// Throw an exception with a formatted string.
#define STUFF_THROW(except, ...) \
    throw except(std::string(#except ": ") \
        + fmt::format(__VA_ARGS__))

#define STUFF_NESTED_THROW(except, ...) \
    std::throw_with_nested(except(std::string(#except ": ") \
        + fmt::format(__VA_ARGS__)))


// Test preconditions, postconditions, and invariants.
#define STUFF_ASSERT(cond, except, ...) \
    if (!(cond)) \
        STUFF_THROW(except, fmt::format(__VA_ARGS__))

#define STUFF_EXPECTS(cond, except, ...) \
    if (!(cond)) \
        STUFF_THROW(except, fmt::format(__VA_ARGS__))

#define STUFF_ENSURES(cond, except, ...) \
    if (!(cond)) \
        STUFF_THROW(except, fmt::format(__VA_ARGS__))

#endif // STUFF_EXCEPTION_H
