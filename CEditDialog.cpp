// CEditDialog.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CEditDialog.h"


// CEditDialog dialog

IMPLEMENT_DYNAMIC(CEditDialog, CDialogEx)

CEditDialog::CEditDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT_DIALOG, pParent)
{

}

CEditDialog::~CEditDialog()
{
}

void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_ceName);
	DDX_Control(pDX, IDC_EDIT_DATA, m_ceData);
}
BOOL CEditDialog::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Edit")); 
	HICON hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME); 
	SetIcon(hIcon, TRUE); 
	SetIcon(hIcon, FALSE); 
	m_ceName.SetWindowTextW(*m_cName); 
	if (*m_cName == L"(Default)")
		m_ceName.SetReadOnly(TRUE); 

	m_ceData.SetWindowTextW(*m_cData); 
	
	CRect rClient;
	GetClientRect(&rClient); 

	return TRUE;
}

void CEditDialog::SetData(CStringW& name, CStringW& data) 
{

	m_cName = &name; 
	m_cData = &data;
}
void CEditDialog::OnOK()
{
	m_ceName.GetWindowTextW(*m_cName); 
	m_ceName.SetReadOnly(FALSE); 
	m_ceData.GetWindowTextW(*m_cData); 

	CDialogEx::OnOK(); 
}


BEGIN_MESSAGE_MAP(CEditDialog, CDialogEx)
END_MESSAGE_MAP()


// CEditDialog message handlers
