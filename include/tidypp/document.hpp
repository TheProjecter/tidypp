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
#include "io.hpp"
#include "mem.hpp"

namespace tidypp
{
    // forward declarations
    class option;
    class node;

    namespace io
    {
        class outputsink;
        class inputsource;
    }

    /**
     * TidyDoc wrapper.
     */
    class document : public basic_wrapper<TidyDoc>
    {
    public:
        /**
         * Default constructor.
         */
        document() throw();

        /**
         * Initialize document using the given custom allocator.
         * @param[in] allocator the custom allocator.
         */
        document(mem::allocator &allocator) throw();

        /**
         * Default destructor.
         */
        virtual ~document() throw();

        /**
         * Let application store a chunk of data w/ each Tidy instance. Useful for callbacks.
         * @param appdata pointer to the data.
         */
        void setappdata(void *appdata) throw();

        /**
         * Get application data set previously.
         * @return a pointer to the data.
         */
        void *getappdata() throw();

        /**
         * Get status of current document.
         * @return the status of the document, represented as an integer.
         */
        int status() throw();

        /**
         * Detected HTML version: 0, 2, 3 or 4.
         * @return an integer.
         */
        int htmlversion() throw();

        /**
         * Input is XHTML?
         * @return true if the document is xhtml, otherwise false.
         */
        bool isxhtml() throw();

        /**
         * Input is generic XML (not HTML or XHTML)?
         * @return true if the document is generic XML, otherwise false.
         */
        bool isgenericxml() throw();

        /**
         * Number of Tidy errors encountered. If > 0, output is suppressed unless
         * TidyForceOutput option is set to true.
         * @return an unsigned integer.
         */
        uint errorcount() throw();

        /**
         * Number of Tidy warnings encountered.
         * @return an unsigned integer.
         */
        uint warningcount() throw();

        /**
         * Number of Tidy accessibility warnings encountered.
         * @return an unsigned integer.
         */
        uint accesswarningcount() throw();

        /**
         * Number of Tidy configuration errors encountered.
         * @return an unsigned integer.
         */
        uint configerrorcount() throw();

        /**
         * Load an ASCII Tidy configuration file.
         *
         * @param[in] configfile a zero-terminated string that contains the filename of the config file.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void loadconfig(ctmbstr configfile) throw(const exception &);

        /**
         * Load a Tidy configuration file with the specified character encoding.
         *
         * @param[in] configfile a zero-terminated string that contains the filename of the config file.
         * @param[in] charenc a zero-terminated string that contains the desired character encoding.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         * @see setcharencoding()
         */
        void loadconfig(ctmbstr configfile, ctmbstr charenc) throw(const exception &);

        /**
         * Checks whether a file exists or not.
         *
         * @param[in] filename a zero-terminated string that contains the filename.
         * @return true if the file exists, otherwise false.
         */
        bool file_exists(ctmbstr filename) throw();

        /**
         * Set the input/output character encoding for parsing markup. Values include: ascii, latin1, raw, utf8, iso2022,
         * mac, win1252, utf16le, utf16be, utf16, big5 and shiftjis. Case in-sensitive.
         *
         * @param[in] charenc the desired character encoding.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void setcharencoding(ctmbstr charenc) throw(const exception &);

        /**
         * Set the input encoding for parsing markup. As for tidySetCharEncoding but only affects the input encoding.
         *
         * @param[in] charenc the desired character encoding.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         * @see setcharencoding()
         */
        void setincharencoding(ctmbstr charenc) throw(const exception &);

        /**
         * Set the output encoding.
         *
         * @param[in] charenc the desired character encoding.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         * @see setcharencoding()
         */
        void setoutcharencoding(ctmbstr charenc) throw(const exception &);

        /**
         * Applications using TidyLib may want to augment command-line and configuration file options.
         * Setting this callback allows an application developer to examine command-line and configuration file options after
         * TidyLib has examined them and failed to recognize them.
         *
         * @param[in] optioncallback pointer to the callback.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         * @see optcallback
         */
        void setoptioncallback(optcallback optioncallback) throw(const exception &);

        /**
         * Get iterator for option list.<br /><br />
         *
         * Example:
         * @verbatim
           tidypp::iterator it = mydoc.optionlist();

           while (it)
           {
               tidypp::option opt = mydoc.nextoption(&it);

               // <get/set option values>
           }
         * @endverbatim
         *
         * @return a tidypp iterator.
         * @see iterator
         */
        iterator optionlist() throw();

        /**
         * Get next Option.
         *
         * @param[in,out] pos pointer to the iterator of the current position into the option list. Incremented automatically.
         * @return the next option.
         * @see option
         * @see optionlist()
         */
        option nextoption(iterator *pos) throw();

        /**
         * Lookup option by ID.
         *
         * @param optid the option id to look up.
         * @return the option.
         * @see option
         * @see optionid
         */
        option getoption(optionid optid) throw();

        /**
         * Lookup option by name.
         *
         * @param optnam the option name to look up, zero terminated string.
         * @return the option.
         * @see option
         */
        option getoption(ctmbstr optnam) throw();

        /**
         * Get current Option value as a string.
         *
         * @param optid the option id.
         * @return a zero-terminated string.
         */
        ctmbstr optgetvalue(optionid optid) throw();

        /**
         * Set Option value as a string.
         *
         * @param optid the option id.
         * @param[in] val the option value.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optsetvalue(optionid optid, ctmbstr val) throw(const exception &);

        /**
         * Set named Option value as a string that will be automatically parsed to the opt type.
         * Good if not sure of type.
         *
         * @param[in] optnam the option name.
         * @param[in] val the option value.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optparsevalue(ctmbstr optnam, ctmbstr val) throw(const exception &);

        /**
         * Get current Option value as an integer.
         *
         * @param optid the option id.
         * @return an unsigned long integer.
         */
        ulong optgetint(optionid optid) throw();

        /**
         * Set Option value as an integer.
         *
         * @param optid the option id.
         * @param val the value.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optsetint(optionid optid, ulong val) throw(const exception &);

        /**
         * Get current Option value as a Boolean flag.
         *
         * @param optid the option id.
         * @return a bool.
         */
        bool optgetbool(optionid optid) throw();

        /**
         * Set Option value as a Boolean flag.
         *
         * @param optid the option id.
         * @param val the value.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optsetbool(optionid optid, bool val) throw(const exception &);

        /**
         * Reset option to default value by ID.
         *
         * @param optid the option id.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optreset(optionid optid) throw(const exception &);

        /**
         * Reset all options to their default values.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optresetall() throw(const exception &);

        /**
         * Take a snapshot of current config settings.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optsnapshot() throw(const exception &);

        /**
         * Reset config settings to snapshot (after document processing).
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optrestoresnapshot() throw(const exception &);

        /**
         * Any settings different than default?
         * @return true if any setting differs from default value, otherwise false.
         */
        bool optdiffthandefault() throw();

        /**
         * Any settings different than snapshot?
         * @return true if any setting differs from snapshot values, otherwise false.
         */
        bool optdiffthansnapshot() throw();

        /**
         * Copy configuration settings from another document.
         *
         * @param[in] other the other document.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optcopyconfig(const document &other) throw(const exception &);

        /**
         * Get character encoding name of given option.
         * Used with setcharencoding(), setoutcharencoding(), setincharencoding().
         *
         * @param optid the option id.
         * @return a zero-terminated string.
         */
        ctmbstr optgetencname(optionid optid) throw();

        /**
         * Get current pick list value for option by ID. Useful for enum types.
         *
         * @param optid the option id.
         * @return a zero-terminated string.
         */
        ctmbstr optgetcurrpick(optionid optid) throw();

        /**
         * Iterate over user declared tags.
         * @return an iterator of the first element of the list.
         */
        iterator optgetdecltaglist() throw();

        /**
         * Get next declared tag of specified type: TidyInlineTags, TidyBlockTags, TidyEmptyTags, TidyPreTags
         *
         * @param optid the option id.
         * @param[in,out] it pointer to an iterator that will be incremented automatically.
         * @return a zero-terminated string.
         * @see optgetdecltaglist()
         */
        ctmbstr optgetnextdecltag(optionid optid, iterator *it) throw();

        /**
         * Get option description.
         *
         * @param opt the option.
         * @return a zero-terminated string.
         */
        ctmbstr optgetdoc(const option &opt) throw();

        /**
         * Iterate over a list of related options.
         *
         * @param opt the option.
         * @return an iterator of the first element of the list.
         */
        iterator optgetdoclinkslist(const option &opt) throw();

        /**
         * Get next related option.
         *
         * @param[in,out] it pointer to an iterator that will be incremented automatically.
         * @return the next related option.
         */
        option optgetnextdoclinks(iterator *it) throw();

        /**
         * Give Tidy a filter callback to use.
         *
         * @param[in] filtcallback callback to filter messages by diagnostic level.
         * @see io::reportfilter
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void setreportfilter(io::reportfilter filtcallback) throw(const exception &);

        /**
         * Set error sink to named file.
         *
         * @param[in] errfilnam the filename.
         * @return a handle to the file.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        FILE *seterrorfile(ctmbstr errfilnam) throw(const exception &);

        /**
         * Set error sink to given buffer.
         *
         * @param[out] buf the error buffer.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void seterrorbuffer(buffer &buf) throw(const exception &);

        /**
         * Set error sink to given generic sink.
         *
         * @param[out] sink the desired error sink.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void seterrorsink(io::outputsink &sink) throw(const exception &);

        /**
         * Parse markup in given buffer.
         *
         * @param[in] buf the error buffer.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void parsebuffer(buffer &buf) throw(const exception &);

        /**
         * Parse markup in given generic input source.
         *
         * @param[in] source the input source.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void parsesource(io::inputsource &source) throw(const exception &);

        /**
         * Execute configured cleanup and repair operations on parsed markup.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void cleanandrepair() throw(const exception &);

        /**
         * Run configured diagnostics on parsed and repaired markup. Must call cleanandrepair() first.
         */
        void rundiagnostics() throw(const exception &);

        /**
         * Save currently parsed document to named file.
         *
         * @param[in] filename a zero-terminated string containing the filename.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void savefile(ctmbstr filename) throw(const exception &);

        /**
         * Save currently parsed document to standard output (FILE*).
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void savestdout() throw(const exception &);

        /**
         * Save currently parsed document to given buffer.
         *
         * @param[out] buf the buffer that will store the document.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void savebuffer(buffer &buf) throw(const exception &);

        /**
         * Save document to application buffer.
         *
         * @param[out] buffer the buffer that will store the document.
         * @param[in,out] buflen pointer to the length of the buffer.
         * @return If buffer is not big enough, ENOMEM will be returned
         * and the necessary buffer size will be placed in *buflen.
         */
        int savestring(tmbstr buffer, uint *buflen) throw();

        /**
         * Save to given generic output sink.
         *
         * @param[in] sink the generic output sink that will store the document.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void savesink(io::outputsink &sink) throw(const exception &);

        /**
         * Save current settings to named file. Only non-default values are written.
         *
         * @param[in] filename the name of the file that will store the settings.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optsavefile(ctmbstr filename) throw(const exception &);

        /**
         * Save current settings to given output sink. Only non-default values are written.
         *
         * @param[in] sink the output sink.
         * @throw tidypp::exception an exception that describes the general cause of the error.
         */
        void optsavesink(io::outputsink &sink) throw(const exception &);

        /**
         * Write more complete information about errors to current error sink.
         * @see seterrorsink()
         */
        void errorsummary() throw();

        /**
         * Write more general information about markup to current error sink.
         * @see seterrorsink()
         */
        void generalinfo() throw();

        node root() throw();
        node html() throw();
        node head() throw();
        node body() throw();
        bool nodeisprop(const node &node) throw();
        bool nodehastext(const node &node) throw();
        void nodegettext(const node &node, buffer &buf) throw(const exception &);
        void nodegetvalue(const node &node, buffer &buf) throw(const exception &);
    };
}
