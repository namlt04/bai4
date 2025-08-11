#pragma once
#include "afxdialogex.h"


// CEditDialog dialog

class CEditDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDialog)

public:
	CEditDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEditDialog();
	void SetData(CStringW& name, CStringW& data); 

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK(); 
	virtual BOOL OnInitDialog(); 

	DECLARE_MESSAGE_MAP()
	CEdit m_ceName;
	CEdit m_ceData;

	CString* m_cName; 
	CString* m_cData;
};
