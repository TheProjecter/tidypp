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
#include "document.hpp"

namespace tidypp
{
    /**
     * TidyOption wrapper
     * @see document::optionlist()
     */
    class option : public basic_wrapper<TidyOption>
    {
        friend option document::nextoption(iterator *pos) throw();
        friend option document::getoption(optionid optid) throw();
        friend option document::getoption(ctmbstr optnam) throw();
        friend ctmbstr document::optgetdoc(const option &opt) throw();
        friend iterator document::optgetdoclinkslist(const option &opt) throw();
        friend option document::optgetnextdoclinks(iterator *it) throw();

    public:
        /**
         * Default constructor.
         */
        option() throw();

        /**
         * Clone constructor.
         * @param other the option to clone.
         */
        option(const option &other);

        /**
         * Default destructor
         */
        ~option() throw();

        /**
         * Get ID of the option.
         *
         * @return the option id.
         * @see optionid
         */
        optionid id() throw();

        /**
         * Get name of the option.
         * @return the option name.
         */
        ctmbstr name() throw();

        /**
         * Get datatype of the option.
         *
         * @return the option datatype.
         * @see optiontype
         */
        optiontype type() throw();

        /**
         * Is option read-only?
         * @return true if the option is read-only, otherwise false.
         */
        bool readonly() throw();

        /**
         * Get category of the option.
         *
         * @return the category.
         * @see configcategory
         */
        configcategory category() throw();

        /**
         * Get default value of the option as a string.
         * @return a zero-terminated string.
         */
        ctmbstr defaultval() throw();

        /**
         * Get default value of the option as an unsigned integer.
         * @return an unsigned long integer.
         */
        ulong defaultint() throw();

        /**
         * Get default value of the option as a boolean value.
         * @return true or false.
         */
        bool defaultbool() throw();

        /**
         * Iterate over the option's "pick list"
         * @return an iterator to the list.
         */
        iterator picklist() throw();

        /**
         * Get next string value of option "pick list"
         *
         * @param[in,out] it the pick list iterator. Automatically incremented.
         * @return a zero-terminated string.
         * @see picklist()
         */
        ctmbstr nextpick(iterator *it) throw();

        /**
         * Get option ID by name.
         *
         * @param name the option name.
         * @return the matching option id.
         */
        static optionid getidbyname(ctmbstr name) throw();

    protected:
        /**
         * Internal constructor from raw data.
         * @see basic_wrapper::basic_wrapper(const T &data)
         */
        option(const TidyOption &data) throw();
    };
}
