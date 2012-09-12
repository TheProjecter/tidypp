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
#include "node.hpp"

namespace tidypp
{
    /**
     * TidyAttr wrapper.
     */
    class attribute : public basic_wrapper<TidyAttr>
    {
        friend attribute node::attrfirst() throw();
        friend attribute node::attrgetbyid(attributeid id) throw();

    public:
        /**
         * Default constructor.
         */
        attribute() throw();

        /**
         * Default destructor.
         */
        virtual ~attribute() throw();

        /**
         * Gets the next attribute.
         * @return the next attribute.
         */
        attribute next() throw();

        /**
         * Gets the attribute name.
         * @return a zero-terminated string.
         */
        ctmbstr name() throw();

        /**
         * Gets the attribute value.
         * @return a zero-terminated string.
         */
        ctmbstr value() throw();

        /**
         * Gets the attribute id.
         * @return an attribute id.
         * @see attributeid
         */
         attributeid id() throw();

    protected:
        /**
         * Internal constructor from raw data.
         * @see basic_wrapper::basic_wrapper(const T &data)
         */
        attribute(const TidyAttr &data) throw();
    };
}
