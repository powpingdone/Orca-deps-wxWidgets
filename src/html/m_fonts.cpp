/////////////////////////////////////////////////////////////////////////////
// Name:        m_fonts.cpp
// Purpose:     wxHtml module for fonts & colors of fonts
// Author:      Vaclav Slavik
// RCS-ID:      $Id$
// Copyright:   (c) 1999 Vaclav Slavik
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation
#endif

#include "wx/wxprec.h"

#include "wx/defs.h"
#if wxUSE_HTML

#ifdef __BORDLANDC__
#pragma hdrstop
#endif

#ifndef WXPRECOMP
#include "wx/wx.h"
#endif

#include "wx/html/forcelnk.h"
#include "wx/html/m_templ.h"

FORCE_LINK_ME(m_fonts)


TAG_HANDLER_BEGIN(FONT, "FONT")

    TAG_HANDLER_PROC(tag)
    {
        wxColour oldclr = m_WParser -> GetActualColor();
        int oldsize = m_WParser -> GetFontSize();

        if (tag.HasParam(wxT("COLOR"))) {
	    unsigned long tmp = 0; 
            wxColour clr;
            if (tag.ScanParam(wxT("COLOR"), wxT("#%lX"), &tmp) == 1) {
                clr = wxColour((tmp & 0xFF0000) >> 16 , (tmp & 0x00FF00) >> 8, (tmp & 0x0000FF));
                m_WParser -> SetActualColor(clr);
                m_WParser -> GetContainer() -> InsertCell(new wxHtmlColourCell(clr));
	    }
        }

        if (tag.HasParam(wxT("SIZE"))) {
	    long tmp = 0;
            wxChar c = tag.GetParam(wxT("SIZE"))[0];
            if (tag.ScanParam(wxT("SIZE"), wxT("%li"), &tmp) == 1) {
                if (c == '+' || c == '-')
                    m_WParser -> SetFontSize(oldsize+tmp);
                else
                    m_WParser -> SetFontSize(tmp);
                m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
	    }
        }

        ParseInner(tag);

        if (oldclr != m_WParser -> GetActualColor()) {
            m_WParser -> SetActualColor(oldclr);
            m_WParser -> GetContainer() -> InsertCell(new wxHtmlColourCell(oldclr));
        }
        if (oldsize != m_WParser -> GetFontSize()) {
            m_WParser -> SetFontSize(oldsize);
            m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
        }
        return TRUE;
    }

TAG_HANDLER_END(FONT)


TAG_HANDLER_BEGIN(FACES_U, "U")

    TAG_HANDLER_PROC(tag)
    {
        int underlined = m_WParser -> GetFontUnderlined();

        m_WParser -> SetFontUnderlined(TRUE);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));

        ParseInner(tag);

        m_WParser -> SetFontUnderlined(underlined);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
        return TRUE;
    }

TAG_HANDLER_END(FACES_U)




TAG_HANDLER_BEGIN(FACES_B, "B,STRONG")

    TAG_HANDLER_PROC(tag)
    {
        int bold = m_WParser -> GetFontBold();

        m_WParser -> SetFontBold(TRUE);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));

        ParseInner(tag);

        m_WParser -> SetFontBold(bold);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
        return TRUE;
    }

TAG_HANDLER_END(FACES_B)




TAG_HANDLER_BEGIN(FACES_I, "I,EM,CITE")

    TAG_HANDLER_PROC(tag)
    {
        int italic = m_WParser -> GetFontItalic();

        m_WParser -> SetFontItalic(TRUE);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));

        ParseInner(tag);

        m_WParser -> SetFontItalic(italic);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
        return TRUE;
    }

TAG_HANDLER_END(FACES_I)




TAG_HANDLER_BEGIN(FACES_TT, "TT")

    TAG_HANDLER_PROC(tag)
    {
        int fixed = m_WParser -> GetFontFixed();

        m_WParser -> SetFontFixed(TRUE);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));

        ParseInner(tag);

        m_WParser -> SetFontFixed(fixed);
        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
        return TRUE;
    }

TAG_HANDLER_END(FACES_TT)





TAG_HANDLER_BEGIN(Hx, "H1,H2,H3,H4,H5,H6")

    TAG_HANDLER_PROC(tag)
    {
        int old_size, old_b, old_i, old_u, old_f, old_al;
        wxHtmlContainerCell *c;

        old_size = m_WParser -> GetFontSize();
        old_b = m_WParser -> GetFontBold();
        old_i = m_WParser -> GetFontItalic();
        old_u = m_WParser -> GetFontUnderlined();
        old_f = m_WParser -> GetFontFixed();
        old_al = m_WParser -> GetAlign();

        m_WParser -> SetFontBold(TRUE);
        m_WParser -> SetFontItalic(FALSE);
        m_WParser -> SetFontUnderlined(FALSE);
        m_WParser -> SetFontFixed(FALSE);

             if (tag.GetName() == "H1")
                m_WParser -> SetFontSize(7);
        else if (tag.GetName() == "H2")
                m_WParser -> SetFontSize(6);
        else if (tag.GetName() == "H3")
                m_WParser -> SetFontSize(5);
        else if (tag.GetName() == "H4") {
                m_WParser -> SetFontSize(5);
                m_WParser -> SetFontItalic(TRUE);
                m_WParser -> SetFontBold(FALSE);
        }
        else if (tag.GetName() == "H5")
                m_WParser -> SetFontSize(4);
        else if (tag.GetName() == "H6") {
                m_WParser -> SetFontSize(4);
                m_WParser -> SetFontItalic(TRUE);
                m_WParser -> SetFontBold(FALSE);
        }

        c = m_WParser -> GetContainer();
        if (c -> GetFirstCell()) {
            m_WParser -> CloseContainer();
            m_WParser -> OpenContainer();
            c = m_WParser -> GetContainer();
        }
        c = m_WParser -> GetContainer();

        c -> SetAlign(tag);
        c -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
        c -> SetIndent(m_WParser -> GetCharHeight(), wxHTML_INDENT_TOP);
        m_WParser -> SetAlign(c -> GetAlignHor());

        ParseInner(tag);

        m_WParser -> SetFontSize(old_size);
        m_WParser -> SetFontBold(old_b);
        m_WParser -> SetFontItalic(old_i);
        m_WParser -> SetFontUnderlined(old_u);
        m_WParser -> SetFontFixed(old_f);
        m_WParser -> SetAlign(old_al);

        m_WParser -> GetContainer() -> InsertCell(new wxHtmlFontCell(m_WParser -> CreateCurrentFont()));
        m_WParser -> CloseContainer();
        m_WParser -> OpenContainer();
        c = m_WParser -> GetContainer();
        c -> SetIndent(m_WParser -> GetCharHeight(), wxHTML_INDENT_TOP);

        return TRUE;
    }

TAG_HANDLER_END(Hx)




TAGS_MODULE_BEGIN(Fonts)

    TAGS_MODULE_ADD(FONT)
    TAGS_MODULE_ADD(FACES_U)
    TAGS_MODULE_ADD(FACES_I)
    TAGS_MODULE_ADD(FACES_B)
    TAGS_MODULE_ADD(FACES_TT)
    TAGS_MODULE_ADD(Hx)

TAGS_MODULE_END(Fonts)


#endif
