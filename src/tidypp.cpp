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

#include "../include/tidypp/tidypp.hpp"

namespace tidypp
{
    // functions
    ctmbstr releasedate() throw()
    {
        return tidyReleaseDate();
    }

    // exception methods
    exception::exception(std::string info) throw()
    {
        this->info = info;
    }

    exception::~exception() throw()
    {
        // empty
    }

    const char *exception::what() const throw()
    {
        return info.c_str();
    }
}
