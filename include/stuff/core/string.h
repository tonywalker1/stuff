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

#ifndef STUFF_CORE_STRING_H
#define STUFF_CORE_STRING_H

#include <boost/convert.hpp>
#include <boost/convert/spirit.hpp>
#include <string>
#include <stuff/core/exception.h>
#include <stuff/core/string_array.h>

namespace stuff::core {

    STUFF_DEFINE_EXCEPTION(string_conversion_error, generic_error);

    //
    // Non-owning string tokenizer (i.e., split a string into parts).
    //
    // Given a string and a separator, next() divides the string into a head
    // and tail: head is the portion before the separator and tail is the
    // portion after.
    //
    // Compared to the standard C/C++ functions (e.g., strtok) for tokenizing a
    // string, this class is safe but still powerful and high-performance.
    // However, for a simpler way to split a string (and examples of how to
    // use this class, see:
    //   split_string(std::string_view, char, Function)
    // and
    //   split_string(std::string_view, char)
    // below.
    //
    class string_tokenizer {
    public:
        //
        // Construct an instance that will tokenize view.
        //
        // The string to which view points, must outlive this instance of
        // string_tokenizer.
        //
        explicit string_tokenizer(std::string_view view);

        //
        // Split the string into a head and tail by finding the first use of
        // the separator (sep).
        //
        std::string_view next(char sep = ' ');

        //
        // Has the entire string been tokenized?
        //
        [[nodiscard]] inline bool is_done() const noexcept { return m_is_done; }
        [[nodiscard]] inline explicit operator bool() const noexcept
        {
            return !m_is_done;
        }
        [[nodiscard]] inline bool operator!() const noexcept
        {
            return m_is_done;
        }

        //
        // The current head token; next() should be called for a valid result.
        //
        [[nodiscard]] inline std::string_view head() const noexcept
        {
            return m_head;
        }

        //
        // The current head token; next() should be called for a valid result.
        //
        [[nodiscard]] inline std::string_view tail() const noexcept
        {
            return m_tail;
        }

    private:
        bool             m_is_done;
        std::string_view m_head;
        std::string_view m_tail;

    }; // class string_tokenizer

    //
    // Using the given separator, tokenize a string and call f() on each token.
    // f() must take a std::string_view. Note: Non-owning.
    //
    // Parameters:
    //   view  String to tokenize.
    //   sep   Separator that divides each token.
    //   f     Function to call on each token.
    //
    template <typename Function>
    inline void split_string(std::string_view view, char sep, Function f)
    {
        string_tokenizer stok {view};
        do {
            f(stok.next(sep));
        } while (stok);
    }

    //
    // Using the given separator, tokenize the string and return each token in
    // a stuff::core::string_view_array. Note: Non-owning on input and output!!!
    // Of the methods to tokenize a string, this is the slowest.
    //
    // Parameters:
    //   view  String to tokenize.
    //   sep   Separator that divides each token.
    //
    // Returns:
    //   A string_view_array containing each token.
    //
    [[nodiscard]] string_view_array split_string(
        std::string_view view, char sep);

    //
    // Fast conversion of a string to a number.
    //
    // An empty string will not be treated as an error, instead the value given
    // by "missing" will be returned. Using zero, for example, can be
    // really useful when parsing a CSV file with empty columns.
    //
    // This function will throw on error.
    //
    // Years ago, I wrote code that beat the standard C/C++ library functions
    // substantially. As I started to migrate that code into this library, I
    // noticed that the standard library had improved substantially. Also, some
    // of the boost::convert converters were on par with my code. Because it is
    // always better to use code from better programmers, I switched to
    // boost::convert. There are a couple of lessons here, but one is that
    // C++ and Boost are always evolving. Periodically, I will benchmark some
    // of the best code and reserve the right to change the underlying
    // implementation!
    //
    // See stuff/benchmarks/core/stuff_core_benchmarks to obtain performance
    // numbers for your system.
    //
    // Parameters:
    //   T        Type of the number (e.g., int).
    //   view     String to convert to a number of type T.
    //   missing  Value to return if view is empty.
    //
    // Returns:
    //   Number of type T.
    //
    template <typename T>
    [[nodiscard]] inline T to_number(std::string_view view, T missing)
    {
        if (view.empty()) {
            return missing;
        }
        boost::cnv::spirit cnv;
        auto               result = boost::convert<T>(view, cnv);
        STUFF_EXPECTS(result, string_conversion_error,
            "can not convert \"{}\" to an integer", view);
        return result.value();
    }

    //
    // Same as above, but an empty string is considered an error.
    //
    template <typename T>
    [[nodiscard]] inline T to_number(std::string_view view)
    {
        boost::cnv::spirit cnv;
        auto               result = boost::convert<T>(view, cnv);
        STUFF_EXPECTS(result, string_conversion_error,
            "can not convert \"{}\" to an integer", view);
        return result.value();
    }

} // namespace stuff::core

#endif // STUFF_CORE_STRING_H
