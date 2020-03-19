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

#ifndef STUFF_CONTAINER_BYTE_ARRAY_H
#define STUFF_CONTAINER_BYTE_ARRAY_H

#include <vector>

namespace stuff::container {

    //
    // Provide an alias to a collection of bytes; primarily for binary blobs,
    // compressed data, etc.
    //
    using byte_array = std::vector<char>;

} // namespace stuff::container

#endif // STUFF_CONTAINER_BYTE_ARRAY_H
