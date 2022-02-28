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

#ifndef _INC_DEFS_BASIC_DEFS_H_
#define _INC_DEFS_BASIC_DEFS_H_


#ifndef __unix__ 
    #error "sorry! this project is just for unix-like machines use!"
#endif

#define loop            while(1)
#define STATIC          static
#define INLINE          static inline

#define IN
#define OUT

#define MUT
#define PUB
#define UNSAFE

#define NO_RET  __attribute__((noreturn))


#define DEFAULT_STACK_SIZE          64
#define DEFAULT_TREE_CHILD          64


#endif // _INC_DEFS_BASIC_DEFS_H_
