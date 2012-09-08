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
    class attribute;

    /**
     * TidyNode wrapper.
     */
    class node : public basic_wrapper<TidyNode>
    {
        friend node document::root() throw();
        friend node document::html() throw();
        friend node document::head() throw();
        friend node document::body() throw();
        friend bool document::nodeisprop(const node &node) throw();
        friend bool document::nodehastext(const node &node) throw();
        friend void document::nodegettext(const node &node, buffer &buf) throw(const exception &);
        friend void document::nodegetvalue(const node &node, buffer &buf) throw(const exception &);

    public:
        /**
         * Default constructor
         */
        node() throw();

        /**
         * Clone constructor
         * @param other the node to clone.
         */
        node(const node &other) throw();

        /**
         * Default destructor
         */
        virtual ~node() throw();

        /**
         * Get the parent of this node.
         * @return the parent node.
         */
        node parent() throw();

        /**
         * Get the child of this node.
         * @return the child node.
         */
        node child() throw();

        /**
         * Get the next node.
         * @return the next node.
         */
        node next() throw();

        /**
         * Get the prev node.
         * @return the prev node.
         */
        node prev() throw();

        /**
         * Get the first node attribute.
         * @return the first node attribute.
         */
        attribute attrfirst() throw();

        /**
         * Get the type of the node.
         * @return the node type.
         * @see nodetype
         */
        nodetype type() throw();

        /**
         * Get the name of the node.
         * @return a zero terminated string.
         */
        ctmbstr name() throw();

        /**
         * Lookup an attribute from the node.
         * @param id the attribute id to look for.
         * @return the attribute.
         * @see attribute
         */
        attribute attrgetbyid(attributeid id) throw();

        bool istext() throw();
        bool isheader() throw();
        tagid id() throw();
        uint line() throw();
        uint column() throw();

        bool ishtml() throw();
        bool ishead() throw();
        bool istitle() throw();
        bool isbase() throw();
        bool ismeta() throw();
        bool isbody() throw();
        bool isframeset() throw();
        bool isframe() throw();
        bool isiframe() throw();
        bool isnoframes() throw();
        bool ishr() throw();
        bool ish1() throw();
        bool ish2() throw();
        bool ispre() throw();
        bool islisting() throw();
        bool isp() throw();
        bool isul() throw();
        bool isol() throw();
        bool isdl() throw();
        bool isdir() throw();
        bool isli() throw();
        bool isdt() throw();
        bool isdd() throw();
        bool istable() throw();
        bool iscaption() throw();
        bool istd() throw();
        bool isth() throw();
        bool istr() throw();
        bool iscol() throw();
        bool iscolgroup() throw();
        bool isbr() throw();
        bool isa() throw();
        bool islink() throw();
        bool isb() throw();
        bool isi() throw();
        bool isstrong() throw();
        bool isem() throw();
        bool isbig() throw();
        bool issmall() throw();
        bool isparam() throw();
        bool isoption() throw();
        bool isoptgroup() throw();
        bool isimg() throw();
        bool ismap() throw();
        bool isarea() throw();
        bool isnobr() throw();
        bool iswbr() throw();
        bool isfont() throw();
        bool islayer() throw();
        bool isspacer() throw();
        bool iscenter() throw();
        bool isstyle() throw();
        bool isscript() throw();
        bool isnoscript() throw();
        bool isform() throw();
        bool istextarea() throw();
        bool isblockquote() throw();
        bool isapplet() throw();
        bool isobject() throw();
        bool isdiv() throw();
        bool isspan() throw();
        bool isinput() throw();
        bool isq() throw();
        bool islabel() throw();
        bool ish3() throw();
        bool ish4() throw();
        bool ish5() throw();
        bool ish6() throw();
        bool isaddress() throw();
        bool isxmp() throw();
        bool isselect() throw();
        bool isblink() throw();
        bool ismarquee() throw();
        bool isembed() throw();
        bool isbasefont() throw();
        bool isisindex() throw();
        bool iss() throw();
        bool isstrike() throw();
        bool isu() throw();
        bool ismenu() throw();

    protected:
        /**
         * Internal constructor from raw data.
         * @see basic_wrapper::basic_wrapper(const T &data)
         */
        node(const TidyNode &data) throw();
    };
}
