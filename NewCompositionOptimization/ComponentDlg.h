#pragma once


// CComponentDlg dialog

class CComponentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CComponentDlg)

public:
	CComponentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComponentDlg();

// Dialog Data
	enum { IDD = IDD_COMPONENT_DIALOG };

	vector<CString>& GetComponentSelectString(){return m_selectString;}//T获取选择的组分字符串数组
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

protected:
	vector<CString> m_selectString;
};
