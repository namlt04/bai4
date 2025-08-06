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

    // === Thêm item 1 ===
    int nItem = m_listCtrl.InsertItem(0, _T("Nguyễn Văn A"));
    m_listCtrl.SetItemText(nItem, 1, _T("25"));
    m_listCtrl.SetItemText(nItem, 2, _T("Hà Nội"));

    // === Thêm item 2 ===
    nItem = m_listCtrl.InsertItem(1, _T("Trần Thị B"));
    m_listCtrl.SetItemText(nItem, 1, _T("30"));
    m_listCtrl.SetItemText(nItem, 2, _T("Đà Nẵng"));

    // === Thêm item 3 ===
    nItem = m_listCtrl.InsertItem(2, _T("Lê Văn C"));
    m_listCtrl.SetItemText(nItem, 1, _T("22"));
    m_listCtrl.SetItemText(nItem, 2, _T("TP.HCM"));
}


void CRightView::OnDraw(CDC* pDC)
{

}


