#include "pch.h"
#include "CRightView.h"


IMPLEMENT_DYNCREATE(CRightView, CView)



BEGIN_MESSAGE_MAP(CRightView, CView)
    ON_NOTIFY(NM_RCLICK, 1123, CRightView::OnRClick)
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

    m_listCtrl.InsertColumn(0, _T("Name"), LVCFMT_LEFT, rClient.Width() / 3);
    m_listCtrl.InsertColumn(1, _T("Type"), LVCFMT_LEFT, rClient.Width() / 3);
    m_listCtrl.InsertColumn(2, _T("Data"), LVCFMT_LEFT, rClient.Width() / 3 );

  }


void CRightView::OnDraw(CDC* pDC)
{

}

void CRightView::OnUpdate(CView* sender, LPARAM lHint, CObject* pHint)
{
    if (::IsWindow(m_listCtrl.GetSafeHwnd())) {
        m_listCtrl.DeleteAllItems();
    }
    if (pHint != nullptr) 
    {

        CData* data = (CData*)pHint;
        HKEY hRoot = data->hKey; 
        CStringW path = data->path; 
        HKEY hKey; 
        LONG result = RegOpenKeyExW(hRoot, path, 0, KEY_ALL_ACCESS, &hKey);
       
        if (result != ERROR_SUCCESS)
        {
        
            return; 
        }

        DWORD index = 0; 
        WCHAR name[256]; 
        BYTE b_data[1024]; 
        
        DWORD nameLen, dataLen, type; 
        while (true)
        {
            
            nameLen = 256; 
            dataLen = 1024; 
            result = RegEnumValue(hKey, index, name, &nameLen, nullptr,&type,  b_data, &dataLen);
            if (result == ERROR_NO_MORE_ITEMS)
                break; 
            else if (result == ERROR_SUCCESS)
            {
                
                int row = m_listCtrl.InsertItem(m_listCtrl.GetItemCount(), CStringW(name));
                m_listCtrl.SetItemText(row, 1, HelperConvert(type));
                m_listCtrl.SetItemText(row, 2, GetRegistryValueAsString(type, b_data, dataLen));

            }
            index += 1; 
        }
    }
    // Truy van ra key
    // them vao m_listCtrl

}
CStringW CRightView::HelperConvert(DWORD type)
{

    switch (type) {
    case REG_NONE: return L"REG_NONE";
    case REG_SZ: return L"REG_SZ";
    case REG_EXPAND_SZ: return L"REG_EXPAND_SZ";
    case REG_BINARY: return L"REG_BINARY";
    case REG_DWORD: return L"REG_DWORD";
    case REG_DWORD_BIG_ENDIAN: return L"REG_DWORD_BIG_ENDIAN";
    case REG_LINK: return L"REG_LINK";
    case REG_MULTI_SZ: return L"REG_MULTI_SZ";
    case REG_QWORD: return L"REG_QWORD";
    default: return L"UNKNOWN_TYPE";
    }
}

CStringW CRightView::GetRegistryValueAsString(DWORD type, BYTE* data, DWORD dataLen)
{
    // GPT
    CStringW result;

    switch (type)
    {
    case REG_SZ:
    case REG_EXPAND_SZ:
        result = CStringW((WCHAR*)data);
        break;

    case REG_MULTI_SZ:
    {
        // MULTI_SZ kết thúc bằng 2 ký tự null (L"\0\0")
        WCHAR* p = (WCHAR*)data;
        while (*p)
        {
            result += p;
            result += L"; ";
            p += wcslen(p) + 1;
        }
        break;
    }

    case REG_DWORD:
        if (dataLen >= sizeof(DWORD))
        {
            DWORD val = *(DWORD*)data;
            result.Format(L"%u (0x%08X)", val, val);
        }
        break;

    case REG_QWORD:
        if (dataLen >= sizeof(ULONGLONG))
        {
            ULONGLONG val = *(ULONGLONG*)data;
            result.Format(L"%llu (0x%016llX)", val, val);
        }
        break;

    case REG_BINARY:
    default:
    {
        for (DWORD i = 0; i < dataLen; ++i)
        {
            CStringW byteStr;
            byteStr.Format(L"%02X ", data[i]);
            result += byteStr;
        }
        break;
    }
    }

    return result;
}

void CRightView::OnRClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    CPoint point;
    GetCursorPos(&point); // Lấy tọa độ chuột toàn màn hình

    // Xác định item được click nếu cần
    CPoint ptClient = point;
    m_listCtrl.ScreenToClient(&ptClient);
    LVHITTESTINFO hitTest = {};
    hitTest.pt = ptClient;
    int index = m_listCtrl.HitTest(&hitTest);

    if (index != -1)
        m_listCtrl.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);

    // Hiện popup menu
    CMenu menu;
    menu.LoadMenu(IDR_MENU1);
    CMenu* pPopup = menu.GetSubMenu(0);
    if (pPopup)
        pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

    *pResult = 0;

}
