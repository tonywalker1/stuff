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

#include <cstdlib>
#include <fstream>
#include <string>
#include <stuff/io/filesystem.h>

namespace stuff::io {

    namespace detail {

        istream_wrapper::istream_wrapper(
            const char* filename, std::ios_base::openmode mode)
        : basic_stream_wrapper {filename, mode}
        {
        }

        istream_wrapper::istream_wrapper(
            const fs::path& filename, std::ios_base::openmode mode)
        : basic_stream_wrapper {filename.native().c_str(), mode}
        {
        }


    } // namespace detail

    container::byte_array read_as_bytes(
        const fs::path& filename, compression_type ct)
    {
        try {
            return detail::read_entire_file<container::byte_array>(
                filename.native().c_str(), ct, std::ifstream::binary);
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(
                filesystem_error, "error reading \"{}\"", filename.native());
        }
    }

    std::string read_as_text(const fs::path& filename, compression_type ct)
    {
        try {
            return detail::read_entire_file<std::string>(
                filename.native().c_str(), ct, std::ifstream::in);
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(
                filesystem_error, "error reading \"{}\"", filename.native());
        }
    }

    path_array list_files(const fs::path& dir)
    {
        path_array manifest;
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_regular_file(entry)) {
                manifest.push_back(entry.path());
            }
        }
        return manifest;
    }

    fs::path home_dir()
    {
        const char* env = std::getenv("HOME");
        if (env == nullptr) {
            STUFF_THROW(filesystem_error, "home directory lookup failed");
        }
        return fs::path(env);
    }

    fs::path expand_home(std::string_view p)
    {
        try {
            if (p == "~") {
                return home_dir();
            }
            if (p.substr(0, 2) == "~/") {
                p.remove_prefix(1);
                fs::path tmp {home_dir()};
                tmp.append(p.begin(), p.end());
                return tmp;
            }
            // otherwise, return a copy of the given path
            return fs::path {p.begin(), p.end()};
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(filesystem_error, "failed to expand \"{}\"", p);
        }
    }

} // namespace stuff::io
