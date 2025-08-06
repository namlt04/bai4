#pragma once
#include <map>
#include "CData.h"
#include "MFCApplication1Doc.h"
class CLeftView :
    public CView{

public : 
    CLeftView() noexcept; 
    ~CLeftView();

protected:

    virtual void OnDraw(CDC* pDC);
    virtual void OnInitialUpdate(); 
    BOOL HasSubKey(HTREEITEM hItem, CStringW path);
    void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pLresult);
    void LoadSubKey(HKEY hRoot, CStringW path, HTREEITEM pParent); 
    void OnSelChange(NMHDR* pNMHDR, LRESULT* pLresult); 
    CTreeCtrl m_keyView;
    std::map<HTREEITEM, std::pair<HKEY, CStringW>> m_Data;
    DECLARE_DYNCREATE(CLeftView);


    DECLARE_MESSAGE_MAP(); 



};

