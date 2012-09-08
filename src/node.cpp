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

#include "../include/tidypp/node.hpp"
#include "../include/tidypp/attribute.hpp"

namespace tidypp
{
    // node methods
    node::node() throw()
    {
        memset(&data, 0, sizeof(TidyNode));
    }

    node::node(const node &other) throw()
    {
        data = other.data;
    }

    node::~node() throw()
    {
        // empty
    }

    node node::parent() throw()
    {
        return node(tidyGetParent(data));
    }

    node node::child() throw()
    {
        return node(tidyGetChild(data));
    }

    node node::next() throw()
    {
        return node(tidyGetNext(data));
    }

    node node::prev() throw()
    {
        return node(tidyGetPrev(data));
    }

    attribute node::attrfirst() throw()
    {
        return attribute(tidyAttrFirst(data));
    }

    nodetype node::type() throw()
    {
        return tidyNodeGetType(data);
    }

    ctmbstr node::name() throw()
    {
        return tidyNodeGetName(data);
    }

    attribute node::attrgetbyid(attributeid id) throw()
    {
        return attribute(tidyAttrGetById(data, id));
    }

    bool node::istext() throw()
    {
        return tidyNodeIsText(data);
    }

    bool node::isheader() throw()
    {
       return tidyNodeIsHeader(data);
    }

    tagid node::id() throw()
    {
        return tidyNodeGetId(data);
    }

    uint node::line() throw()
    {
        return tidyNodeLine(data);
    }

    uint node::column() throw()
    {
        return tidyNodeColumn(data);
    }

    bool node::ishtml() throw()
    {
        return tidyNodeIsHTML(data);
    }

    bool node::ishead() throw()
    {
        return tidyNodeIsHEAD(data);
    }

    bool node::istitle() throw()
    {
        return tidyNodeIsTITLE(data);
    }

    bool node::isbase() throw()
    {
        return tidyNodeIsBASE(data);
    }

    bool node::ismeta() throw()
    {
        return tidyNodeIsMETA(data);
    }

    bool node::isbody() throw()
    {
        return tidyNodeIsBODY(data);
    }

    bool node::isframeset() throw()
    {
        return tidyNodeIsFRAMESET(data);
    }

    bool node::isframe() throw()
    {
        return tidyNodeIsFRAME(data);
    }

    bool node::isiframe() throw()
    {
        return tidyNodeIsIFRAME(data);
    }

    bool node::isnoframes() throw()
    {
        return tidyNodeIsNOFRAMES(data);
    }

    bool node::ishr() throw()
    {
        return tidyNodeIsHR(data);
    }

    bool node::ish1() throw()
    {
        return tidyNodeIsH1(data);
    }

    bool node::ish2() throw()
    {
        return tidyNodeIsH2(data);
    }

    bool node::ispre() throw()
    {
        return tidyNodeIsPRE(data);
    }

    bool node::islisting() throw()
    {
        return tidyNodeIsLISTING(data);
    }

    bool node::isp() throw()
    {
        return tidyNodeIsP(data);
    }

    bool node::isul() throw()
    {
        return tidyNodeIsUL(data);
    }

    bool node::isol() throw()
    {
        return tidyNodeIsOL(data);
    }

    bool node::isdl() throw()
    {
        return tidyNodeIsDL(data);
    }

    bool node::isdir() throw()
    {
        return tidyNodeIsDIR(data);
    }

    bool node::isli() throw()
    {
        return tidyNodeIsLI(data);
    }

    bool node::isdt() throw()
    {
        return tidyNodeIsDT(data);
    }

    bool node::isdd() throw()
    {
        return tidyNodeIsDD(data);
    }

    bool node::istable() throw()
    {
        return tidyNodeIsTABLE(data);
    }

    bool node::iscaption() throw()
    {
        return tidyNodeIsCAPTION(data);
    }

    bool node::istd() throw()
    {
        return tidyNodeIsTD(data);
    }

    bool node::isth() throw()
    {
        return tidyNodeIsTH(data);
    }

    bool node::istr() throw()
    {
        return tidyNodeIsTR(data);
    }

    bool node::iscol() throw()
    {
        return tidyNodeIsCOL(data);
    }

    bool node::iscolgroup() throw()
    {
        return tidyNodeIsCOLGROUP(data);
    }

    bool node::isbr() throw()
    {
        return tidyNodeIsBR(data);
    }

    bool node::isa() throw()
    {
        return tidyNodeIsA(data);
    }

    bool node::islink() throw()
    {
        return tidyNodeIsLINK(data);
    }

    bool node::isb() throw()
    {
        return tidyNodeIsB(data);
    }

    bool node::isi() throw()
    {
        return tidyNodeIsI(data);
    }

    bool node::isstrong() throw()
    {
        return tidyNodeIsSTRONG(data);
    }

    bool node::isem() throw()
    {
        return tidyNodeIsEM(data);
    }

    bool node::isbig() throw()
    {
        return tidyNodeIsBIG(data);
    }

    bool node::issmall() throw()
    {
        return tidyNodeIsSMALL(data);
    }

    bool node::isparam() throw()
    {
        return tidyNodeIsPARAM(data);
    }

    bool node::isoption() throw()
    {
        return tidyNodeIsOPTION(data);
    }

    bool node::isoptgroup() throw()
    {
        return tidyNodeIsOPTGROUP(data);
    }

    bool node::isimg() throw()
    {
        return tidyNodeIsIMG(data);
    }

    bool node::ismap() throw()
    {
        return tidyNodeIsMAP(data);
    }

    bool node::isarea() throw()
    {
        return tidyNodeIsAREA(data);
    }

    bool node::isnobr() throw()
    {
        return tidyNodeIsNOBR(data);
    }

    bool node::iswbr() throw()
    {
        return tidyNodeIsWBR(data);
    }

    bool node::isfont() throw()
    {
        return tidyNodeIsFONT(data);
    }

    bool node::islayer() throw()
    {
        return tidyNodeIsLAYER(data);
    }

    bool node::isspacer() throw()
    {
        return tidyNodeIsSPACER(data);
    }

    bool node::iscenter() throw()
    {
        return tidyNodeIsCENTER(data);
    }

    bool node::isstyle() throw()
    {
        return tidyNodeIsSTYLE(data);
    }

    bool node::isscript() throw()
    {
        return tidyNodeIsSCRIPT(data);
    }

    bool node::isnoscript() throw()
    {
        return tidyNodeIsNOSCRIPT(data);
    }

    bool node::isform() throw()
    {
        return tidyNodeIsFORM(data);
    }

    bool node::istextarea() throw()
    {
        return tidyNodeIsTEXTAREA(data);
    }

    bool node::isblockquote() throw()
    {
        return tidyNodeIsBLOCKQUOTE(data);
    }

    bool node::isapplet() throw()
    {
        return tidyNodeIsAPPLET(data);
    }

    bool node::isobject() throw()
    {
        return tidyNodeIsOBJECT(data);
    }

    bool node::isdiv() throw()
    {
        return tidyNodeIsDIV(data);
    }

    bool node::isspan() throw()
    {
        return tidyNodeIsSPAN(data);
    }

    bool node::isinput() throw()
    {
        return tidyNodeIsINPUT(data);
    }

    bool node::isq() throw()
    {
        return tidyNodeIsQ(data);
    }

    bool node::islabel() throw()
    {
        return tidyNodeIsLABEL(data);
    }

    bool node::ish3() throw()
    {
        return tidyNodeIsH3(data);
    }

    bool node::ish4() throw()
    {
        return tidyNodeIsH4(data);
    }

    bool node::ish5() throw()
    {
        return tidyNodeIsH5(data);
    }

    bool node::ish6() throw()
    {
        return tidyNodeIsH6(data);
    }

    bool node::isaddress() throw()
    {
        return tidyNodeIsADDRESS(data);
    }

    bool node::isxmp() throw()
    {
        return tidyNodeIsXMP(data);
    }

    bool node::isselect() throw()
    {
        return tidyNodeIsSELECT(data);
    }

    bool node::isblink() throw()
    {
        return tidyNodeIsBLINK(data);
    }

    bool node::ismarquee() throw()
    {
        return tidyNodeIsMARQUEE(data);
    }

    bool node::isembed() throw()
    {
        return tidyNodeIsEMBED(data);
    }

    bool node::isbasefont() throw()
    {
        return tidyNodeIsBASEFONT(data);
    }

    bool node::isisindex() throw()
    {
        return tidyNodeIsISINDEX(data);
    }

    bool node::iss() throw()
    {
        return tidyNodeIsS(data);
    }

    bool node::isstrike() throw()
    {
        return tidyNodeIsSTRIKE(data);
    }

    bool node::isu() throw()
    {
        return tidyNodeIsU(data);
    }

    bool node::ismenu() throw()
    {
        return tidyNodeIsMENU(data);
    }

    node::node(const TidyNode &data) throw()
        : basic_wrapper<TidyNode>(data)
    {
        // empty
    }
}
