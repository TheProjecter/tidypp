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

#include "io.hpp"
#include "document.hpp"

namespace tidypp
{
    namespace io
    {
        /**
         * TidyInputSource wrapper - Delivers raw bytes of input.
         */
        class inputsource : public basic_wrapper<TidyInputSource>
        {
            friend void document::parsesource(inputsource &source) throw(const exception &);

        public:
            /**
             * Facilitates user defined source by providing an entry point to marshal
             * pointers-to-functions. Needed by .NET and possibly other language bindings.
             *
             * @param srcdata the source data.
             * @param gbfunc input callback: get next byte of input.
             * @param ugbfunc input callback: unget a byte of input.
             * @param endfunc input callback: are we at the end of the input?
             * @throw tidypp::exception an exception that describes the general cause of the error.
             */
            inputsource(void *srcdata, getbytefunc gbfunc, ungetbytefunc ugbfunc, eoffunc endfunc)
                throw(const exception &);

            /**
             * Initialize an input source from a buffer.
             * @param[in] buf the buffer that will be bound to the input source.
             */
            inputsource(buffer &buf) throw();

            /**
             * Default destructor.
             */
            virtual ~inputsource() throw();

            /**
             * Helper: get next byte from input source.
             * @return the obtained byte.
             */
            uint getbyte() throw();

            /**
             * Helper: unget byte back to input source.
             * @param byteval the byte to unget.
             */
            void ungetbyte(uint byteval) throw();

            /**
             * Helper: check if input source is at end.
             * @return true if the input source reached eof, otherwise false.
             */
            bool eof() throw();
        };
    }
}
