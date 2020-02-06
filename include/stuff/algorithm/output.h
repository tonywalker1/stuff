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

#ifndef STUFF_ALGORITHM_OUTPUT_H
#define STUFF_ALGORITHM_OUTPUT_H

#include <iostream>

namespace stuff::algorithm {

    // Send every item in a container to stdout.
    template <typename C>
    inline void to_stream(const C& container, std::ostream& os)
    {
        for (const auto& item : container) {
            os << item << '\n';
        }
    }

    template <typename C>
    inline void to_stdout(const C& container)
    {
        to_stream(container, std::cout);
    }

    template <typename C>
    inline void to_stderr(const C& container)
    {
        to_stream(container, std::cerr);
    }

} // namespace stuff::algorithm

#endif // STUFF_ALGORITHM_OUTPUT_H
