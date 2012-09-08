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
#include <tidy/buffio.h>

namespace tidypp
{
    /**
     * I/O and Messages
     */
    namespace io
    {
        typedef TidyPutByteFunc putbytefunc; /**< Output callback: send a byte to output */
        typedef TidyGetByteFunc getbytefunc; /**< Input Callback: get next byte of input. */
        typedef TidyUngetByteFunc ungetbytefunc; /**< Input Callback: unget a byte of input. */
        typedef TidyEOFFunc eoffunc; /**< Input Callback: are we at the end of input? */
        typedef TidyReportFilter reportfilter; /**< Callback to filter messages by diagnostic level:
                                                    info, warning, etc. Just set diagnostic output handler
                                                    to redirect all diagnostics output. Return true to
                                                    proceed with output, false to cancel. */

        const int eof EndOfStream; /**< End of input "character" */
    }

    class buffer; // forward declaration
}
