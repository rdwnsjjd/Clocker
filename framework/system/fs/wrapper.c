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

#include <stdio.h>

#include "inc.h"


result_t w_file_open(
    wfile_t* OUT wfile,
    str_t    IN  path, 
    str_t    IN  mode
) {
    soft_assert_ret_res(
        path IS_NOT_EQ INVALID_HNDL,
        "Invalid argument (path is null)!"
    );

    soft_assert_ret_res(
        mode IS_NOT_EQ INVALID_HNDL,
        "Invalid argument (mode is null)!"
    );

    wfile->inner = fopen(path, mode);
    soft_assert_ret(
        wfile->inner IS_NOT_EQ INVALID_HNDL,
        err(ek_openf),
        "Opening file failed (os error: %s)!", 
        strerror(errno)
    );

    return ok(_((handle_t) wfile));
}


result_t w_file_write(
    wfile_t*   IN wfile,
    bytes_t    IN buffer,
    size_t     IN size
) {
    soft_assert_ret_res(
        buffer IS_NOT_EQ INVALID_HNDL,
        "Invalid argument (buffer is null)!"
    );

    soft_assert_wrn(
        size IS_NOT_EQ 0,
        "The given buffer size is 0!"
    );

    for (index_t idx = 0; idx < size; idx++) {
        soft_assert_ret(
            fputc(buffer[idx], wfile->inner) IS_NOT_EQ EOF,
            err(ek_unexpected_eof),
            "Putting byte into file failed (os error: %s)!",
            strerror(errno)
        );
    }

    return ok(_(size));
}


result_t w_file_size(
    wfile_t* IN  wfile
) {
    size_t tmp = ftell(wfile->inner);

    fseek(wfile->inner, 0L, SEEK_END);
    size_t size = ftell(wfile->inner);
    fseek(wfile->inner, tmp, SEEK_SET);

    return ok(_(size));
}


result_t w_file_read(
    wfile_t*   IN  wfile,
    bytes_t    OUT buffer,
    size_t     IN  size
) {
    soft_assert_ret_res(
        buffer IS_NOT_EQ INVALID_HNDL,
        "Invalid argument (buffer is null)!"
    );

    soft_assert_wrn(
        size IS_NOT_EQ 0,
        "The given buffer size is 0!"
    );

    result_t file_size = w_file_size(wfile);
    soft_assert_res_ret_res(
        file_size,
        "Getting file size failed!"
    );

    soft_assert_ret(
        size IS_SMALLER_OR_EQ res_get_data(file_size).size,
        err(ek_unexpected_eof),
        "The given buffer read size exceeds the file size (buffer size: %ld while file size: %ld)!",
        size, res_get_data(file_size).size
    );

    for (index_t idx = 0; idx < size; idx++) {
        buffer[idx] = fgetc(wfile->inner);
    }

    return ok(_(size));
}


result_t w_file_close(
    wfile_t* IN wfile
) {

    soft_assert_ret(
        fclose(wfile->inner) IS_NOT_EQ EOF,
        err(ek_openf),
        "Closing file failed (os error: %s)!", 
        strerror(errno)
    );

    return ok(G_NONE);
}


result_t _file_serialize(
    FILE*    IN  file,
    bytes_t  OUT buffer,
    size_t   IN  capacity
) {
    // TODO

    return err(ek_not_impl);
}


result_t w_file_serialize(
    wfile_t* IN  wfile,
    bytes_t  OUT buffer,
    size_t   IN  capacity
) {
    // TODO

    return err(ek_not_impl);
}