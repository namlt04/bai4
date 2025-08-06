#pragma once
#include <afxwin.h>
class CRightView :
    public CView
{


public : 
    CRightView() noexcept;
    ~CRightView();

protected: 
    virtual void OnDraw(CDC* pDC); 
    virtual void OnInitialUpdate();
    DECLARE_DYNCREATE(CRightView);
    DECLARE_MESSAGE_MAP(); 



    CListCtrl m_listCtrl; 
};

