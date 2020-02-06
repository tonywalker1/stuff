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

#include <stuff/io/filesystem.h>
#include <stuff/io/detail/iops.h>
#include <cstdlib>
#include <fstream>
#include <string>

namespace stuff::io {

    byte_array read_as_bytes(const fs::path& filename, compression_type ct)
    {
        try {
            return detail::read_entire_file<byte_array>(
                filename.native().c_str(),
                ct,
                std::ifstream::binary);
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(filesystem_error,
                "error reading \"{}\"", filename.native());
        }
    }

    std::string read_as_text(const fs::path& filename, compression_type ct)
    {
        try {
            return detail::read_entire_file<std::string>(
                filename.native().c_str(),
                ct,
                std::ifstream::in);
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(filesystem_error,
                "error reading \"{}\"", filename.native());
        }
    }

    fs::path home_dir()
    {
        const char* env = std::getenv("HOME");
        if (env == nullptr)
            STUFF_THROW(filesystem_error, "home directory lookup failed");
        return fs::path(env);
    }

    fs::path expand_home(std::string_view p)
    {
        try {
            if (p == "~") {
                return home_dir();
            }
            else if (p.substr(0, 2) == "~/") {
                p.remove_prefix(1);
                fs::path tmp {home_dir()};
                tmp.append(p.begin(), p.end());
                return tmp;
            }
            else {
                return fs::path {p.begin(), p.end()};
            }
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(filesystem_error,
                "failed to expand \"{}\"", p);
        }
    }

    /*
    fs::path expand_home(const fs::path& p)
    {
        try {
            if (p.size() == 0) {
                return fs::path {p};
            }
            else if (p.native().front() == '~') {
                return home_dir().concat(&p.native()[1]);
            }
            else {
                return fs::path {p};
            }
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(filesystem_error,
                "failed to expand \"{}\"", p.native());
        }
    }
    */
} // namespace stuff
