/////////////////////////////////////////////////////////////////////////////
// Name:        view_running.cpp
// Author:      Laurent Pugin
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "view.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "bboxdevicecontext.h"
#include "devicecontext.h"
#include "doc.h"
#include "pghead.h"
#include "text.h"
#include "vrv.h"

namespace vrv {
    
void View::DrawRunningElements(DeviceContext *dc, Page *page)
{
    assert(dc);
    assert(page);
    
    if (dc->Is(BBOX_DEVICE_CONTEXT)) {
        BBoxDeviceContext *bBoxDC = dynamic_cast<BBoxDeviceContext *>(dc);
        assert(bBoxDC);
        if (!bBoxDC->UpdateVerticalValues()) return;
    }
    
    PgHead *pgHead = m_doc->m_scoreDef.GetPgHead();
    if (pgHead) {
        DrawPgHead(dc, pgHead);
    }
}
    
void View::DrawPgHead(DeviceContext *dc, PgHead *pgHead)
{
    assert(dc);
    assert(pgHead);
    
    dc->StartGraphic(pgHead, "", pgHead->GetUuid());
    
    FontInfo pgHeadTxt;
    
    TextDrawingParams params;
    
    // If we have not timestamp
    params.m_x = pgHead->GetDrawingX();
    params.m_y = pgHead->GetDrawingY();
    params.m_width = pgHead->GetWidth();
    params.m_alignment = HORIZONTALALIGNMENT_left;
    params.m_laidOut = true;
    
    pgHeadTxt.SetPointSize(m_doc->GetDrawingLyricFont(100)->GetPointSize());
    
    dc->SetBrush(m_currentColour, AxSOLID);
    dc->SetFont(&pgHeadTxt);
    
    dc->StartText(ToDeviceContextX(params.m_x), ToDeviceContextY(params.m_y), HORIZONTALALIGNMENT_left);
    DrawTextChildren(dc, pgHead, params);
    dc->EndText();
    
    dc->ResetFont();
    dc->ResetBrush();

    dc->EndGraphic(pgHead, this);
}

} // namespace vrv
