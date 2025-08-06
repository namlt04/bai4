#pragma once

class CLeftView :
    public CView{

public : 
    CLeftView() noexcept; 
    ~CLeftView();

protected:

    virtual void OnDraw(CDC* pDC);
    virtual void OnInitialUpdate(); 
    BOOL HasSubKey(HKEY hRoot, CStringW path);
    void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pLresult);
    void LoadSubKey(HKEY hRoot, CStringW& path, HTREEITEM pParent); 
    CTreeCtrl m_keyView;
    DECLARE_DYNCREATE(CLeftView);

    DECLARE_MESSAGE_MAP(); 



};

