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
#include <boost/optional.hpp>
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
    // use this class, see
    //   split_string(std::string_view, char, Function)
    // and
    //   split_string(std::string_view, char)
    // below.
    //
    class string_tokenizer {
    public:
        //
        // Note: non-owning constructor (and class). The string to which view
        // points, must outlive the instance of string_tokenizer.
        //
        explicit string_tokenizer(std::string_view view);

        std::string_view next(char sep = ' ');

        [[nodiscard]] inline bool is_done() const noexcept { return m_is_done; }

        [[nodiscard]] inline std::string_view head() const noexcept
        {
            return m_head;
        }

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
    // f() must take a std::string_view.
    //
    // Note: Non-owning.
    //
    template <typename Function>
    inline void split_string(std::string_view view, char sep, Function f)
    {
        string_tokenizer stok {view};
        do {
            f(stok.next(sep));
        } while (!stok.is_done());
    }

    //
    // Using the given separator, tokenize the string and return each token in
    // a stuff::core::string_view_array.
    // Of the methods to tokenize a string, this is the slowest.
    //
    string_view_array split_string(std::string_view view, char sep);

    //
    // Fast conversion of a string to a number.
    //
    // This function returns the number wrapped in boost::optional. This gives
    // you control over how to handle errors. For a function with different
    // semantics, see to_number(std::sring_view view, T missing) below.
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
    // You can build and run stuff/benchmarks/core/stuff_core_benchmarks to
    // obtain performance numbers for your system.
    //
    template <typename T>
    inline boost::optional<T> to_number(std::string_view view)
    {
        boost::cnv::spirit cnv;
        return boost::convert<T>(view, cnv).value();
    }

    //
    // Fast conversion of a string to a number.
    //
    // Unlike the function above, an empty string will not be treated as an
    // error. For this function, the value given by missing will be returned
    // instead. Using zero, for example, can be really useful when parsing
    // a CSV file with empty columns.
    //
    // Unlike the function above, this function will throw on error.
    //
    template <typename T>
    inline T to_number(std::string_view view, T missing)
    {
        if (view.empty()) {
            return missing;
        }
        auto result = to_number<T>(view);
        STUFF_EXPECTS(result, string_conversion_error,
            "can not convert \"{}\" to an integer", view);
        return result.value();
    }

} // namespace stuff::core

#endif // STUFF_CORE_STRING_H
