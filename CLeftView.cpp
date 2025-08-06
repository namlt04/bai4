#include "pch.h"
#include "CLeftView.h"


IMPLEMENT_DYNCREATE(CLeftView, CView)
BEGIN_MESSAGE_MAP(CLeftView, CView)
    ON_NOTIFY(TVN_ITEMEXPANDING, 1234, CLeftView::OnItemExpanding)
END_MESSAGE_MAP()
CLeftView::CLeftView() noexcept{}

CLeftView::~CLeftView(){}

void CLeftView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    CRect rect;
    GetClientRect(&rect);

    m_keyView.Create(
        WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS,
        rect,
        this,
        1234  // ID control, chọn số tùy ý
    );

    /*m_keyView.InsertItem(_T("Nút cha"));
    HTREEITEM root =  m_keyView.InsertItem(_T("Nút con 1"), TVI_ROOT);
    m_keyView.InsertItem(_T("Test"), root); 
    m_keyView.InsertItem(_T("Test"), root); 
    m_keyView.InsertItem(_T("Test"), root); 
    m_keyView.InsertItem(_T("Test"), root); 
    m_keyView.InsertItem(_T("Test"), root); 

    HTREEITEM root1 = m_keyView.InsertItem(_T("Nút con 2"), TVI_ROOT);
    m_keyView.InsertItem(_T("Test"), root1);
    m_keyView.InsertItem(_T("Test"), root1);
    m_keyView.InsertItem(_T("Test"), root1);
    m_keyView.InsertItem(_T("Test"), root1);
    m_keyView.InsertItem(_T("Test"), root1);*/


    struct {
        HKEY hKey;
        LPCTSTR name;
    } rootKeys[] = {
        { HKEY_CLASSES_ROOT,     _T("HKEY_CLASSES_ROOT") },
        { HKEY_CURRENT_USER,     _T("HKEY_CURRENT_USER") },
        { HKEY_LOCAL_MACHINE,    _T("HKEY_LOCAL_MACHINE") },
        { HKEY_USERS,            _T("HKEY_USERS") },
        { HKEY_CURRENT_CONFIG,   _T("HKEY_CURRENT_CONFIG") },
        { HKEY_PERFORMANCE_DATA, _T("HKEY_PERFORMANCE_DATA") },
    };

    for (int i = 0; i < _countof(rootKeys); ++i)
    {
        HTREEITEM hRootItem = m_keyView.InsertItem(rootKeys[i].name);
        m_keyView.SetItemData(hRootItem, (DWORD_PTR)rootKeys[i].hKey); // lưu roottem co 1root key
        // Kiểm tra, nếu như có subkey thì tạo dump subkey
        if (HasSubKey(rootKeys[i].hKey, L""))
        {
            m_keyView.InsertItem(_T(""), hRootItem);
        }
    }
}
BOOL CLeftView::HasSubKey(HKEY hRoot, CStringW path)
{
    HKEY hKey; 
    LONG res = RegOpenKeyEx(hRoot, path.GetBuffer(), 0, KEY_ALL_ACCESS, &hKey);

    if (res != ERROR_SUCCESS)
    {
        AfxMessageBox(_T("Lỗi không thể mở Key con ")); 
        return FALSE; 
    }

    DWORD nSubKey;
    res = RegQueryInfoKey(hKey, NULL, NULL, NULL, &nSubKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    RegCloseKey(hKey);

    return (res == ERROR_SUCCESS && nSubKey > 0 ) ;
    
}

void CLeftView::OnDraw(CDC* pDC)
{
    // COMMENT
}
void CLeftView::LoadSubKey(HKEY hRoot, CStringW& path, HTREEITEM pParent)
{
    HKEY hKey; 
    LONG res = RegOpenKeyEx(hRoot, path, 0, KEY_ALL_ACCESS, &hKey);

    if (res != ERROR_SUCCESS)
    {
        AfxMessageBox(_T("Lỗi không thể load key")); 
        return; 
    }
    DWORD index = 0; 
    WCHAR subKeyName[256]; 
    DWORD subKeyLen = 256; 
    while (true)
    {
        subKeyLen = 256;


        LONG result = RegEnumKeyEx(hKey, index, subKeyName, &subKeyLen,  NULL, NULL, NULL, NULL);
        if (result == ERROR_NO_MORE_ITEMS)
            break; 
        else if (result == ERROR_SUCCESS)
        {
            m_keyView.InsertItem(CString(subKeyName),pParent);
            path += L"\\" + CStringW(subKeyName);
            if (HasSubKey(hRoot, path))
            {
                m_keyView.InsertItem(_T(""), pParent);
            }

        }
        index += 1; 
    }

}

void CLeftView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pLresult)
{

    NM_TREEVIEW* pNMTreeview = (NM_TREEVIEW*)pNMHDR; 
    HTREEITEM hItem = pNMTreeview->itemNew.hItem;

    if (pNMTreeview->action == TVE_EXPAND)
    {
        HTREEITEM hChild = m_keyView.GetChildItem(hItem);
        // Xoa dummy subkey
        m_keyView.DeleteItem(hChild);

        HKEY hKey = (HKEY)m_keyView.GetItemData(hItem);
        CStringW path = L""; 
        LoadSubKey(hKey, path , hItem);
    }
    else if (pNMTreeview->action == TVE_COLLAPSE)
    {
        HTREEITEM hChild = m_keyView.GetChildItem(hItem);
        while (hChild != NULL)
        {
            HTREEITEM hNext = m_keyView.GetNextSiblingItem(hChild); 
            m_keyView.DeleteItem(hChild); 
            hChild = hNext;
        }
        // Them lai dummy subkey de co dau cong 

        m_keyView.InsertItem(_T(""), hItem); 

    }




    //AfxMessageBox(_T("Da click vao tang giam")); 
}
