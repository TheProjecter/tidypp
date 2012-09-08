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

#include "../include/tidypp/document.hpp"
#include "../include/tidypp/option.hpp"
#include "../include/tidypp/outputsink.hpp"
#include "../include/tidypp/buffer.hpp"
#include "../include/tidypp/node.hpp"

namespace tidypp
{
    // document methods
    document::document() throw()
    {
        data = tidyCreate();
    }

    document::document(mem::allocator &allocator) throw()
    {
        data = tidyCreateWithAllocator(&allocator);
    }

    document::~document() throw()
    {
        tidyRelease(data);
    }

    void document::setappdata(void *appdata) throw()
    {
        tidySetAppData(data, appdata);
    }

    void *document::getappdata() throw()
    {
        return tidyGetAppData(data);
    }

    int document::status() throw()
    {
        return tidyStatus(data);
    }

    int document::htmlversion() throw()
    {
        return tidyDetectedHtmlVersion(data);
    }

    bool document::isxhtml() throw()
    {
        return tidyDetectedXhtml(data);
    }

    bool document::isgenericxml() throw()
    {
        return tidyDetectedGenericXml(data);
    }

    uint document::errorcount() throw()
    {
        return tidyErrorCount(data);
    }

    uint document::warningcount() throw()
    {
        return tidyWarningCount(data);
    }

    uint document::accesswarningcount() throw()
    {
        return tidyAccessWarningCount(data);
    }

    uint document::configerrorcount() throw()
    {
        return tidyConfigErrorCount(data);
    }

    void document::loadconfig(ctmbstr configfile) throw(const exception &)
    {
        attempt(tidyLoadConfig(data, configfile), "document.loadconfig(configfile): failed to load config file.");
    }

    void document::loadconfig(ctmbstr configfile, ctmbstr charenc) throw(const exception &)
    {
        attempt(tidyLoadConfigEnc(data, configfile, charenc), "document.loadconfig(configfile, charenc): failed to load config file.");
    }

    bool document::file_exists(ctmbstr filename) throw()
    {
        return tidyFileExists(data, filename);
    }

    void document::setcharencoding(ctmbstr charenc) throw(const exception &)
    {
        attempt(tidySetCharEncoding(data, charenc), "document.setcharencoding: failed to set char encoding.");
    }

    void document::setincharencoding(ctmbstr charenc) throw(const exception &)
    {
        attempt(tidySetInCharEncoding(data, charenc), "document.setincharencoding: failed to set input char encoding.");
    }

    void document::setoutcharencoding(ctmbstr charenc) throw(const exception &)
    {
        attempt(tidySetOutCharEncoding(data, charenc), "document.setoutcharencoding: failed to set output char encoding.");
    }

    void document::setoptioncallback(optcallback optioncallback) throw(const exception &)
    {
        if (!tidySetOptionCallback(data, optioncallback))
            throw exception("document.setoptioncallback: failed to set option callback. Invalid/NULL callback pointer?");
    }

    iterator document::optionlist() throw()
    {
        return tidyGetOptionList(data);
    }


    option document::nextoption(iterator *pos) throw()
    {
        return option(tidyGetNextOption(data, pos));
    }

    option document::getoption(optionid optid) throw()
    {
        return option(tidyGetOption(data, optid));
    }

    option document::getoption(ctmbstr optnam) throw()
    {
        return option(tidyGetOptionByName(data, optnam));
    }

    ctmbstr document::optgetvalue(optionid optid) throw()
    {
        return tidyOptGetValue(data, optid);
    }

    void document::optsetvalue(optionid optid, ctmbstr val) throw(const exception &)
    {
        if (!tidyOptSetValue(data, optid, val))
            throw exception("document.optsetvalue: failed to set option value.");
    }

    void document::optparsevalue(ctmbstr optnam, ctmbstr val) throw(const exception &)
    {
        if (!tidyOptParseValue(data, optnam, val))
            throw exception("document.optparsevalue: failed to parse option value.");
    }

    ulong document::optgetint(optionid optid) throw()
    {
        return tidyOptGetInt(data, optid);
    }

    void document::optsetint(optionid optid, ulong val) throw(const exception &)
    {
        if (!tidyOptSetInt(data, optid, val))
            throw exception("document.optsetint: failed to set option value.");
    }

    bool document::optgetbool(optionid optid) throw()
    {
        return tidyOptGetBool(data, optid);
    }

    void document::optsetbool(optionid optid, bool val) throw(const exception &)
    {
        if (!tidyOptSetBool(data, optid, val ? yes : no))
            throw exception("document.optsetbool: failed to set option value.");
    }

    void document::optreset(optionid optid) throw(const exception &)
    {
        if (!tidyOptResetToDefault(data, optid))
            throw exception("document.optreset: failed to reset option value.");
    }

    void document::optresetall() throw(const exception &)
    {
        if (!tidyOptResetAllToDefault(data))
            throw exception("document.optresetall: failed to reset options.");
    }

    void document::optsnapshot() throw(const exception &)
    {
        if (!tidyOptSnapshot(data))
            throw exception("document.optsnapshot: failed to create options snapshot.");
    }

    void document::optrestoresnapshot() throw(const exception &)
    {
        if (!tidyOptResetToSnapshot(data))
            throw exception("document.optrestoresnapshot: failed to restore options snapshot.");
    }

    bool document::optdiffthandefault() throw()
    {
        return tidyOptDiffThanDefault(data);
    }

    bool document::optdiffthansnapshot() throw()
    {
        return tidyOptDiffThanSnapshot(data);
    }

    void document::optcopyconfig(const document &other) throw(const exception &)
    {
        if (!tidyOptCopyConfig(data, other.data))
            throw exception("document.optcopyconfig: failed to copy config.");
    }

    ctmbstr document::optgetencname(optionid optid) throw()
    {
        return tidyOptGetEncName(data, optid);
    }

    ctmbstr document::optgetcurrpick(optionid optid) throw()
    {
        return tidyOptGetCurrPick(data, optid);
    }

    iterator document::optgetdecltaglist() throw()
    {
        return tidyOptGetDeclTagList(data);
    }

    ctmbstr document::optgetnextdecltag(optionid optid, iterator *it) throw()
    {
        return tidyOptGetNextDeclTag(data, optid, it);
    }

    ctmbstr document::optgetdoc(const option &opt) throw()
    {
        return tidyOptGetDoc(data, opt.data);
    }

    iterator document::optgetdoclinkslist(const option &opt) throw()
    {
        return tidyOptGetDocLinksList(data, opt.data);
    }

    option document::optgetnextdoclinks(iterator *it) throw()
    {
        return option(tidyOptGetNextDocLinks(data, it));
    }

    void document::setreportfilter(io::reportfilter filtcallback) throw(const exception &)
    {
        if (!tidySetReportFilter(data, filtcallback))
            throw exception("document.setreportfilter: failed to set filter callback.");
    }

    FILE *document::seterrorfile(ctmbstr errfilnam) throw(const exception &)
    {
        FILE *res = NULL;

        res = tidySetErrorFile(data, errfilnam);

        if (!res)
            throw exception("document.seterrorfile: failed to set/create error file.");

        return res;
    }

    void document::seterrorbuffer(buffer &buf) throw(const exception &)
    {
        attempt(tidySetErrorBuffer(data, &buf.data), "document.seterrorbuffer: failed to set error buffer.");
    }

    void document::seterrorsink(io::outputsink &sink) throw(const exception &)
    {
        attempt(tidySetErrorSink(data, &sink.data), "document.seterrorsink: failed to set error sink.");
    }

    void document::parsebuffer(buffer &buf) throw(const exception &)
    {
        attempt(tidyParseBuffer(data, &buf.data), "document.parsebuffer: failed to parse buffer.");
    }

    void document::parsesource(io::inputsource &source) throw(const exception &)
    {
        attempt(tidyParseSource(data, &source.data), "document.parsesource: failed to parse generic input source.");
    }

    void document::cleanandrepair() throw(const exception &)
    {
        attempt(tidyCleanAndRepair(data), "document.cleanandrepair: failed to execute configured cleanup and repair operations.");
    }

    void document::rundiagnostics() throw(const exception &)
    {
        attempt(tidyRunDiagnostics(data), "document.rundiagnostics: failed to run configured diagnostics on parsed and repaired markup.");
    }

    void document::savefile(ctmbstr filename) throw(const exception &)
    {
        attempt(tidySaveFile(data, filename), "document.savefile: failed to save to named file.");
    }

    void document::savestdout() throw(const exception &)
    {
        attempt(tidySaveStdout(data), "document.savestdout: failed to save to stdout.");
    }

    void document::savebuffer(buffer &buf) throw(const exception &)
    {
        attempt(tidySaveBuffer(data, &buf.data), "document.savebuffer: failed to save to buffer.");
    }

    int document::savestring(tmbstr buffer, uint *buflen) throw()
    {
        return tidySaveString(data, buffer, buflen);
    }

    void document::savesink(io::outputsink &sink) throw(const exception &)
    {
        attempt(tidySaveSink(data, &sink.data), "document.savesink: failed to save to given output sink.");
    }

    void document::optsavefile(ctmbstr filename) throw(const exception &)
    {
        attempt(tidyOptSaveFile(data, filename), "document.optsavefile: failed to save config to file.");
    }

    void document::optsavesink(io::outputsink &sink) throw(const exception &)
    {
        attempt(tidyOptSaveSink(data, &sink.data), "document.optsavesink: failed to save settings to generic output sink.");
    }

    void document::errorsummary() throw()
    {
        tidyErrorSummary(data);
    }

    void document::generalinfo() throw()
    {
        tidyGeneralInfo(data);
    }

    node document::root() throw()
    {
        return node(tidyGetRoot(data));
    }

    node document::html() throw()
    {
        return node(tidyGetHtml(data));
    }

    node document::head() throw()
    {
        return node(tidyGetHead(data));
    }

    node document::body() throw()
    {
        return node(tidyGetBody(data));
    }

    bool document::nodeisprop(const node &node) throw()
    {
        return tidyNodeIsProp(data, node.data);
    }

    bool document::nodehastext(const node &node) throw()
    {
        return tidyNodeHasText(data, node.data);
    }

    void document::nodegettext(const node &node, buffer &buf) throw(const exception &)
    {
        if (!tidyNodeGetText(data, node.data, &buf.data))
            throw exception("document.nodegettext: failed to retrieve node text.");
    }

    void document::nodegetvalue(const node &node, buffer &buf) throw(const exception &)
    {
        if (!tidyNodeGetValue(data, node.data, &buf.data))
            throw exception("document.nodegetvalue: failed to retrieve node value.");
    }
}
