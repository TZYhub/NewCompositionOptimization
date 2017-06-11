#pragma once
#include "Nature.h"

// CNatureDlg dialog

class CNatureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNatureDlg)

public:
	CNatureDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNatureDlg();

// Dialog Data
	enum { IDD = IDD_NATURE_DIALOG };


	vector<CString>& GetSelectVtNature(){return m_selectNatureString;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

protected:
	vector<CString> m_selectNatureString;
};
