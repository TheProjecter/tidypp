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

#include "../include/tidypp/option.hpp"

namespace tidypp
{
    // option methods
    option::option() throw()
    {
        memset(&data, 0, sizeof(TidyOption));
    }

    option::option(const option &other)
    {
        data = other.data;
    }

    option::~option() throw()
    {
        // empty
    }

    optionid option::id() throw()
    {
        return tidyOptGetId(data);
    }

    ctmbstr option::name() throw()
    {
        return tidyOptGetName(data);
    }

    optiontype option::type() throw()
    {
        return tidyOptGetType(data);
    }

    bool option::readonly() throw()
    {
        return tidyOptIsReadOnly(data);
    }

    configcategory option::category() throw()
    {
        return tidyOptGetCategory(data);
    }

    ctmbstr option::defaultval() throw()
    {
        return tidyOptGetDefault(data);
    }

    ulong option::defaultint() throw()
    {
        return tidyOptGetDefaultInt(data);
    }

    bool option::defaultbool() throw()
    {
        return tidyOptGetDefaultBool(data);
    }

    iterator option::picklist() throw()
    {
        return tidyOptGetPickList(data);
    }

    ctmbstr option::nextpick(iterator *it) throw()
    {
        return tidyOptGetNextPick(data, it);
    }

    optionid option::getidbyname(ctmbstr name) throw()
    {
        return tidyOptGetIdForName(name);
    }

    option::option(const TidyOption &data) throw()
        : basic_wrapper<TidyOption>(data)
    {
        // empry
    }
}
