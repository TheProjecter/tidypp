/*
    tidypp - a c++ wrapper around HTML Tidy Lib
    Copyright (C) 2012  Francesco "Franc[e]sco" Noferi (francesco1149@gmail.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the
    Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
    Boston, MA  02110-1301, USA.
*/

#include "../include/tidypp/buffer.hpp"

namespace tidypp
{
    // buffer methods
    buffer::buffer() throw()
    {
        tidyBufInit(&data);
    }

    buffer::buffer(mem::allocator &allocator) throw()
    {
        tidyBufInitWithAllocator(&data, &allocator);
    }

    byte *buffer::ptr() throw()
    {
        return data.bp;
    }

    uint buffer::size() throw()
    {
        return data.size;
    }

    void buffer::alloc(uint size) throw()
    {
        tidyBufAlloc(&data, size);
    }

    void buffer::alloc(mem::allocator &allocator, uint size) throw()
    {
        tidyBufAllocWithAllocator(&data, &allocator, size);
    }

    void buffer::checkalloc(uint size, uint chunksize) throw()
    {
        tidyBufCheckAlloc(&data, size, chunksize);
    }

    void buffer::free() throw()
    {
        tidyBufFree(&data);
    }

    void buffer::clear() throw()
    {
        tidyBufClear(&data);
    }

    void buffer::attach(byte *ptr, uint size) throw()
    {
        tidyBufAttach(&data, ptr, size);
    }

    void buffer::detach() throw()
    {
        tidyBufDetach(&data);
    }

    void buffer::append(void *ptr, uint size) throw()
    {
        tidyBufAppend(&data, ptr, size);
    }

    void buffer::putbyte(byte bval)
    {
        tidyBufPutByte(&data, bval);
    }

    int buffer::popbyte()
    {
        return tidyBufPopByte(&data);
    }

    int buffer::getbyte()
    {
        return tidyBufGetByte(&data);
    }

    void buffer::ungetbyte(byte bval)
    {
        tidyBufUngetByte(&data, bval);
    }

    bool buffer::eof()
    {
        return tidyBufEndOfInput(&data);
    }
}
