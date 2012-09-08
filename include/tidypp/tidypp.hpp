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

#include <exception>
#include <string>
#include <tidy/tidy.h>

/**
 * tidypp - a c++ object-oriented wrapper around Tidy HTML (TidyLib).
 * @author Francesco "Franc[e]sco" Noferi (francesco1149@gmail.com)
 * TODO: Wrap tidy enums to match the lower-case naming convention
 */
namespace tidypp
{
    /** A generic HTML Tidy exception. */
    class exception : public std::exception
    {
    public:
        /**
         * Default constructor.
         * @param info information about the general cause of the error.
         */
        exception(std::string info) throw();

        /**
         * Default destructor
         */
        virtual ~exception() throw();

        /**
         * Returns a C-style character string describing the general cause of the current error.
         * @return a zero-terminated C-style string.
         */
        virtual const char *what() const throw();

    protected:
        std::string info; /**< Stores information about the error passed on the constructor.
                              @see exception(std::string info) */
    };

    typedef TidyNodeType nodetype; /**< Node types:
                                        @li TidyNode_Root: Root
                                        @li TidyNode_DocType: DOCTYPE
                                        @li TidyNode_Comment: Comment
                                        @li TidyNode_ProcIns: Processing Instruction
                                        @li TidyNode_Text: Text
                                        @li TidyNode_Start: Start Tag
                                        @li TidyNode_End: End Tag
                                        @li TidyNode_StartEnd: Start/End (empty) Tag
                                        @li TidyNode_CDATA: Unparsed Text
                                        @li TidyNode_Section: XML Section
                                        @li TidyNode_Asp: ASP Source
                                        @li TidyNode_Jste: JSTE Source
                                        @li TidyNode_Php: PHP Source
                                        @li TidyNode_XmlDecl: XML Declaration */

    typedef TidyOptionId optionid; /**< Option IDs Used to get/set option values. See <a href="http://www.sens.
                                        buffalo.edu/services/webhosting/advanced/tidydoc/api/tidyenum_8h.html#a395">
                                        TidyOptionId</a> for the available values. */

    typedef TidyOptionType optiontype; /**< Option data types (TidyString, TidyInteger, TidyBoolean) */

    typedef TidyIterator iterator; /**< Used to iterate options */

    typedef TidyConfigCategory configcategory; /**< Categories of Tidy configuration options:
                                                    @li TidyMarkup: Markup options (HTML/XHTML version, etc)
                                                    @li TidyDiagnostics: Diagnostics
                                                    @li TidyPrettyPring: Output layout
                                                    @li TidyEncoding: Character encodings
                                                    @li TidyMiscellaneous: File handling, message format, etc */

    typedef TidyTagId tagid; /**< Known HTML element types. See <a href="http://www.sens.buffalo.edu/services/webhosting/
                                  advanced/tidydoc/api/tidyenum_8h.html#a403">TidyTagId</a> for the available values. */

    typedef TidyAttrId attributeid; /**< Known HTML attributes. See <a href="http://www.sens.buffalo.edu/services/webhosting/
                                  advanced/tidydoc/api/tidyenum_8h.html#a404">TidyTagId</a> for the available values. */

    typedef TidyOptCallback optcallback; /**< bool ( *)(ctmbstr option, ctmbstr value)<br />
                                              Applications using TidyLib may want to augment command-line and configuration
                                              file options. Setting this callback allows an application developer to examine
                                              command-line and configuration file options after TidyLib has examined them and
                                              failed to recognize them.
                                              @see document::setoptioncallback() */

    /**
     * Get HTML Tidy Lib release date (version) for current library.
     * @return a zero-terminated string.
     */
    ctmbstr releasedate() throw();
}
