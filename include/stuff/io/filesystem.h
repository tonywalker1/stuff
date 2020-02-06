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

#ifndef STUFF_IO_FILESYSTEM_H
#define STUFF_IO_FILESYSTEM_H

#include <stuff/core/byte_array.h>
#include <stuff/core/exception.h>
#include <boost/filesystem.hpp>
#include <string>
#include <string_view>

// Use Boost until std::filesystem matures.
namespace fs = boost::filesystem;

namespace stuff::io {

    STUFF_DEFINE_EXCEPTION(filesystem_error, generic_error);

    // Alias for a vector of paths.
    using path_array = std::vector<fs::path>;

    // File compression types for functions below.
    enum class compression_type {none, bzip2, gzip};

    // Read an entire file as text or binary data.
    byte_array  read_as_bytes(const fs::path& filename,
        compression_type ct = compression_type::none);
    std::string read_as_text(const fs::path& filename,
        compression_type ct = compression_type::none);

    // Apply f() to each directory in dir.
    // f() must be a unary function taking a path.
    template <typename F>
    void for_each_directory(const fs::path& dir, F f)
    {
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_directory(entry)) {
                f(entry.path());
            }
        }
    }

    // Apply f() to each file in dir.
    // f() must be a unary function taking a path.
    template <typename F>
    void for_each_file(const fs::path& dir, F f)
    {
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_regular_file(entry)) {
                f(entry.path());
            }
        }
    }

    // List all files in dir.
    // The returned list is not sorted.
    path_array list_files(const fs::path& dir);

    // Return the home directory for the current user.
    fs::path home_dir();

    // Given a path starting with a tilde (~), replace with the current user's
    // home directory.
    fs::path expand_home(std::string_view p);

} // namespace stuff::io

#endif // STUFF_IO_FILESYSTEM_H
