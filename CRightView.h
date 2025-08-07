#pragma once
#include <afxwin.h>
#include "CData.h"
class CRightView :
    public CView
{


public : 
    CRightView() noexcept;
    ~CRightView();

protected: 

    void OnUpdate(CView* sender, LPARAM lHint, CObject* pHint);
    virtual void OnDraw(CDC* pDC); 
    virtual void OnInitialUpdate();
    DECLARE_DYNCREATE(CRightView);
    DECLARE_MESSAGE_MAP(); 
    CStringW HelperConvert(DWORD type);
    
    CStringW GetRegistryValueAsString(DWORD type, BYTE* data, DWORD dataLen);

    CListCtrl m_listCtrl; 
};

