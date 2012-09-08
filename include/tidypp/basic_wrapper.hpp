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

#include "tidypp.hpp"

namespace tidypp
{
    /**
     * A generic wrapper class to inherit for quick wrapping of tidy html structs and classes.
     */
    template <class T>
    class basic_wrapper
    {
    public:
        /**
         * Default constructor.
         */
        basic_wrapper() throw()
        {
            // empty
        }

        /**
         * Default destructor.
         */
        virtual ~basic_wrapper() throw()
        {
            // empty
        }

        /**
         * Checks if the internal data is not NULL.
         * @return true if the object is valid, otherwise false.
         */
        bool valid() throw()
        {
            return data;
        }

    protected:
        T data; /**< Internal instance of the wrapped struct/class */

        /**
         * If the passed tidy error code represents an error, throws an exception with the provided
         * description, otherwise does nothing.
         *
         * @param res the error code returned by a Tidy HTML function.
         * @param errortext the error description that will be thrown in case of errors.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        static void attempt(int res, std::string errortext) throw(const exception &)
        {
            if (res < 0 || res == 2) // ignore warnings
                throw exception(errortext);
        }

        /**
         * Internal constructor from raw data. Will be used in friend methods that must return the wrapped
         * datatype.<br />
         * NOTE: this assumes the data type can be copied with simple assignment, if not do not use this.
         * @param data the raw wrapped data.
         */
        basic_wrapper(const T &data) throw()
        {
            this->data = data;
        }
    };
}
