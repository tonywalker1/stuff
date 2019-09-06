// Copyright (C) 2019  Tony Walker
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

#ifndef STUFF_GZIP_H
#define STUFF_GZIP_H

#include <stuff/core/exception.h>
#include <stuff/io/filesystem.h>
#include <zlib.h>

namespace stuff {

    STUFF_DEFINE_EXCEPTION(gzip_error, generic_error);

    //
    class gzip_file {
    public:

        gzip_file(fs::path path, const char* mode = "r");

        gzip_file(const gzip_file&) = delete;
        gzip_file(gzip_file&&)      = delete;

        gzip_file& operator= (const gzip_file&) = delete;
        gzip_file& operator= (gzip_file&&) = delete;

        ~gzip_file();

        // void flush();

    private:

        gzFile m_handle;

    }; // class gzip_file

} // namespace stuff

#endif // STUFF_GZIP_H
