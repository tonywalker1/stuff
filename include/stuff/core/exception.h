//
// Copyright (C) 2019-2020  Tony Walker
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef STUFF_CORE_EXCEPTION_H
#define STUFF_CORE_EXCEPTION_H

#include <fmt/format.h>
#include <stdexcept>
#include <string>

//
// Simplify the definition of new exception types.
//
// Having been influenced by Boost Exception, I tend to use exception types as
// "tags" that identify the error source rather than file and line. This macro
// simplifies defining new exception types.
//
// Parameters:
//   except       The new type (to be defined).
//   except_base  The base class for the new type.
//
// For example, the following defines a new exception named random_number_error
// that is derived from generic_error:
//   STUFF_DEFINE_EXCEPTION(random_number_error, generic_error);
//   try {
//       ...
//       throw random_number_error {"the answer is 42"};
//   }
//   catch (const random_number_error& e) {
//       std::cerr << to_string(e) << '\n';
//   }
//
#define STUFF_DEFINE_EXCEPTION(except, except_base) \
    struct except : public except_base { \
        explicit except(const char* msg) : except_base(msg) {} \
        explicit except(const std::string& msg) : except_base(msg) {} \
    }

namespace stuff::core {

    //
    // Define generic_error: the base class for all other exception types used
    // in this library.
    //
    // For example, the following defines a new exception named
    // random_number_error that is derived from generic_error:
    //   STUFF_DEFINE_EXCEPTION(random_number_error, generic_error);
    //
    STUFF_DEFINE_EXCEPTION(generic_error, std::runtime_error);

    //
    // Convert all nested exception message(s) to a string.
    //
    // For example:
    //   catch (const std::exception& e) {
    //      std::cout << to_string(e) << '\n';
    //   }
    //
    std::string to_string(const std::exception& e);

} // namespace stuff::core

//
// Throw an exception with a formatted string.
//
// This library uses libfmt (will be included in C++20) to format exception
// messages. See the site for libfmt for documentation.
//
// Parameters:
//   except    The type of exception to throw.
//   var_args  The exception message with arguments.
//
// For example:
//   STUFF_THROW(universe_error, "the answer is {}", 42);
// or
//   STUFF_NESTED_THROW(universe_error, "the answer is {}", 42)
//
#define STUFF_THROW(except, ...) \
    throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#define STUFF_NESTED_THROW(except, ...) \
    std::throw_with_nested( \
        except(std::string(#except ": ") + fmt::format(__VA_ARGS__)))

//
// Test preconditions, postconditions, and invariants.
//
// If the given condition is false, the macro below will throw the given error
// with the given formatted message. I tend to use STUFF_ASSERT for invariants,
// STUFF_EXPECTS for preconditions, and STUFF_ENSURES for postconditions.
//
// Parameters:
//   cond      Condition to test and throw on false.
//   except    The type of exception to throw if cond is false.
//   var_args  The exception message with arguments.
//
// For example:
//   STUFF_EXPECTS(get_answer() == 42,
//       universe_error,
//       "the answer should be {}", 42);
//
#define STUFF_ASSERT(cond, except, ...) \
    (cond) \
        ? (void)(0) \
        : throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#define STUFF_EXPECTS(cond, except, ...) \
    (cond) \
        ? (void)(0) \
        : throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#define STUFF_ENSURES(cond, except, ...) \
    (cond) \
        ? (void)(0) \
        : throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#endif // STUFF_CORE_EXCEPTION_H
