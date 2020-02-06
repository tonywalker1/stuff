// Copyright (C) 2019, 2020  Tony Walker
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
//       STUFF_EXPECTS(lower <= val, random_number_error, "some message");
//       STUFF_EXPECTS(val < upper, random_number_error, "some message");
//       ...
//   }
// This will generate the following message:
//  "random_number_error: some message"
//
// You can use STUFF_* macros below to throw (possibly nested) exceptions, and
// then unwind them with to_string().
//

#ifndef STUFF_CORE_EXCEPTION_H
#define STUFF_CORE_EXCEPTION_H

#include <fmt/format.h>
#include <stdexcept>
#include <string>

//
// Define new exception types, see generic_error below.
// For example:
//   STUFF_DEFINE_EXCEPTION(random_number_error, generic_error);
//
//   try {
//       ...
//       throw random_number_error {"the answer is 42"};
//   }
//   catch (const random_number_error& e) {
//       std::cerr << to_string(e) << '\n';
//   }
//
#define STUFF_DEFINE_EXCEPTION(except, except_base) \
    struct except : public except_base \
    { \
        explicit except(const char* msg)        : except_base(msg) {} \
        explicit except(const std::string& msg) : except_base(msg) {} \
    }


namespace stuff::core {

    // Default error and base class for all other exceptions.
    STUFF_DEFINE_EXCEPTION(generic_error, std::runtime_error);

    // Unwind any nested expections.
    // For example:
    //   catch (const std::exception& e) {
    //       std::cout << to_string(e) << '\n';
    //   }
    std::string to_string(const std::exception& e);

} // namespace stuff::core


//
// Throw an exception with a formatted string.
// Uses libfmt, see the site for libfmt for documentation.
// For example:
//   STUFF_THROW(universe_error, "the answer is {}", 42);
//
#define STUFF_THROW(except, ...) \
    throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#define STUFF_NESTED_THROW(except, ...) \
    std::throw_with_nested(except(std::string(#except ": ") \
        + fmt::format(__VA_ARGS__)))


//
// Test preconditions, postconditions, and invariants.
// For example:
//   STUFF_EXPECTS(get_answer() == 42,
//       universe_error,
//       "the answer should be {}", 42);
//
#define STUFF_ASSERT(cond, except, ...) \
    if (!(cond)) \
        throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#define STUFF_EXPECTS(cond, except, ...) \
    if (!(cond)) \
        throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#define STUFF_ENSURES(cond, except, ...) \
    if (!(cond)) \
        throw except(std::string(#except ": ") + fmt::format(__VA_ARGS__))

#endif // STUFF_CORE_EXCEPTION_H
