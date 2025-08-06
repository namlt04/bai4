#include "pch.h"
#include "CRightView.h"


IMPLEMENT_DYNCREATE(CRightView, CView)


BEGIN_MESSAGE_MAP(CRightView, CView)
END_MESSAGE_MAP()
CRightView::CRightView() noexcept {}; 
CRightView::~CRightView() {};


void CRightView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    CRect rClient;
    GetClientRect(&rClient);

    m_listCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | WS_BORDER,
        rClient, this, 1123);

    m_listCtrl.InsertColumn(0, _T("Tên"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(1, _T("Tuổi"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(2, _T("Địa chỉ"), LVCFMT_CENTER, 100);

  }


void CRightView::OnDraw(CDC* pDC)
{

}

void CRightView::OnUpdate(CView* sender, LPARAM lHint, CObject* pHint)
{
    //m_listCtrl.DeleteAllItems(); 
    if (pHint != nullptr) 
    {

        CData* data = (CData*)pHint;
        HKEY hRoot = data->hKey; 
        CStringW path = data->path; 
        HKEY hKey; 
        LONG result = RegOpenKeyEx(hRoot, path.GetBuffer(), 0, KEY_ALL_ACCESS, &hKey);
       
        if (result != ERROR_SUCCESS)
        {
            return; 
        }

        DWORD index = 0; 
        WCHAR name[256]; ;
        DWORD nameLen = 256; 
        while (true)
        {
            
            nameLen = 256; 
            result = RegEnumValue(hKey, index, name, &nameLen, nullptr, nullptr, nullptr, nullptr);
            if (result == ERROR_NO_MORE_ITEMS)
                break; 
            else if (result == ERROR_SUCCESS)
            {
                int row = m_listCtrl.InsertItem(0, CStringW(name));
                AfxMessageBox(CStringW(name));
                m_listCtrl.SetItemText(row, 1, CStringW(name));
                m_listCtrl.SetItemText(row, 2, CStringW(name));

            }
            index += 1; 
        }
    }
    // Truy van ra key
    // them vao m_listCtrl

}

