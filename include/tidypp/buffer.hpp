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

#pragma once

#include "basic_wrapper.hpp"
#include "mem.hpp"
#include "inputsource.hpp"
#include "outputsink.hpp"
#include "document.hpp"
#include <tidy/buffio.h>

namespace tidypp
{
    /**
     * TidyBuffer wrapper - A chunk of memory.
     */
    class buffer : public basic_wrapper<TidyBuffer>
    {
        friend io::inputsource::inputsource(buffer &buf) throw();
        friend io::outputsink::outputsink(buffer &buf) throw();
        friend void document::seterrorbuffer(buffer &buf) throw(const exception &);
        friend void document::parsebuffer(buffer &buf) throw(const exception &);
        friend void document::savebuffer(buffer &buf) throw(const exception &);
        friend void document::nodegettext(const node &node, buffer &buf) throw(const exception &);
        friend void document::nodegetvalue(const node &node, buffer &buf) throw(const exception &);

    public:
        /**
         * Default constructor.
         */
        buffer() throw();

        /**
         * Initialize buffer using the given custom allocator.
         * @param[in] allocator the custom allocator.
         */
        buffer(mem::allocator &allocator) throw();

        /**
         * Returns a pointer to the buffer's data.
         * @return a pointer to a byte array.
         */
        byte *ptr() throw();

        /**
         * Returns the size of the buffer's data in bytes.
         * @return an unsigned integer.
         */
        uint size() throw();

        /**
         * Free current buffer, allocate given amount, reset input pointer, use the default allocator.
         * @param size amount of memory to allocate in bytes.
         */
        void alloc(uint size) throw();

        /**
         * Free current buffer, allocate given amount, reset input pointer, use the given custom allocator.
         *
         * @param[in] allocator the custom allocator.
         * @param size amount of memory to allocate in bytes.
         */
        void alloc(mem::allocator &allocator, uint size) throw();

        /**
         * Expand buffer to given size. Chunk size is minimum growth. Pass 0 for default of 256 bytes.
         *
         * @param size desired size.
         * @param chunksize minimum growth of the buffer.
         */
        void checkalloc(uint size, uint chunksize) throw();

        /**
         * Free current contents and zero out memory.
         */
        void free() throw();

        /**
         * Set buffer memory to 0.
         */
        void clear() throw();

        /**
         * Attach to existing buffer.
         * @param[in] ptr pointer to the existing buffer's data.
         * @param size size of the existing buffer.
         */
        void attach(byte *ptr, uint size) throw();

        /**
         * Detach from buffer. Caller must free.
         */
        void detach() throw();

        /**
         * Append bytes to buffer. Expand if necessary.
         * @param[in] ptr pointer to the data to append.
         * @param size size of the data.
         */
        void append(void *ptr, uint size) throw();

        /**
         * Append one byte to buffer. Expand if necessary.
         * @param bval the byte to append.
         */
        void putbyte(byte bval);

        /**
         * Get byte from end of buffer.
         * @return the popped byte.
         */
        int popbyte();

        /**
         * Get byte from front of buffer. Increment input offset.
         * @return the obtained byte.
         */
        int getbyte();

        /**
         * Put a byte back in front of the buffer. Decrement input offset.
         * @param bval the byte to insert.
         */
        void ungetbyte(byte bval);

        /**
         * At end of buffer?
         * @return true if we're at the end of the buffer, otherwise false.
         */
        bool eof();
    };
}
