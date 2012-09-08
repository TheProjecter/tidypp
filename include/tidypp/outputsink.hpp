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
         * TidyOutputSink wrapper - accepts raw bytes of output.
         */
        class outputsink : public basic_wrapper<TidyOutputSink>
        {
            friend void document::seterrorsink(outputsink &sink) throw(const exception &);
            friend void document::savesink(io::outputsink &sink) throw(const exception &);
            friend void document::optsavesink(io::outputsink &sink) throw(const exception &);

        public:
            /**
             * Facilitates user defined sinks by providing an entry point to marshal pointers-to-functions.
             * Needed by .NET and possibly other language bindings.
             *
             * @param snkdata pointer to the sink data.
             * @param pbfunc output callback: send a byte to output.
             * @throw tidypp::exception an exception that describes the general cause of the error.
             */
            outputsink(void *snkdata, putbytefunc pbfunc) throw(const exception &);

            /**
             * Initialize an output sink from a buffer.
             * @param[in] buf the buffer that will be bound to the output sink.
             */
            outputsink(buffer &buf) throw();

            /**
             * Default destructor.
             */
            virtual ~outputsink() throw();

            /**
             * Helper: send a byte to output
             * @param byteval the byte to send.
             */
            void putbyte(uint byteval) throw();
        };
    }
}
