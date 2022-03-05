// Copyright (C) 2022 Redwan
// 
// This file is part of Owl.
// 
// Owl is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Owl is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Owl.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _FRAMEWORK_SYSTEM_FS_MOD_H_
#define _FRAMEWORK_SYSTEM_FS_MOD_H_

#include "framework/prims/inc.h"
#include "common/defs/inc.h"

#define FRAMEWORK_SYSTEM_FS

typedef struct {
    FILE*       inner;
}
wfile_t;


result_t w_file_open(
    wfile_t* OUT wfile,
    str_t    IN  path, 
    str_t    IN  mode
);


result_t w_file_write(
    wfile_t*   IN wfile,
    bytes_t    IN buffer,
    size_t     IN size
);


result_t w_file_size(
    wfile_t* IN  wfile
);


result_t w_file_read(
    wfile_t*   IN  wfile,
    bytes_t    OUT buffer,
    size_t     IN  size
);


result_t w_file_close(
    wfile_t* IN wfile
);


result_t w_file_serialize(
    wfile_t* IN  wfile,
    bytes_t  OUT buffer,
    size_t   IN  capacity
);


#endif // _FRAMEWORK_SYSTEM_FS_MOD_H_
