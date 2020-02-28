//
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

#include <stuff/core/exception.h>

namespace stuff::core {

#ifdef __clang__
    #pragma clang diagnostic push
    #pragma ide diagnostic   ignored "InfiniteRecursion"
#endif
    void format_exception(
        std::string& str, const std::exception& e, size_t indent, size_t level)
    {
        // format the current exception
        if (level != 0) {
            str += "\n";
        }
        str += std::string(level * indent, ' ');
        str += e.what();

        // unwind any nested exceptions
        try {
            std::rethrow_if_nested(e);
        }
        catch (std::exception& e) {
            format_exception(str, e, indent, ++level);
        }
    }
#ifdef __clang__
    #pragma clang diagnostic pop
#endif

    std::string to_string(const std::exception& e, size_t indent)
    {
        std::string msg;
        format_exception(msg, e, indent, 0);
        return msg;
    }

} // namespace stuff::core
