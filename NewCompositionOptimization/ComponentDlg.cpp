// ComponentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewCompositionOptimization.h"
#include "ComponentDlg.h"
#include "afxdialogex.h"


// CComponentDlg dialog

IMPLEMENT_DYNAMIC(CComponentDlg, CDialogEx)

CComponentDlg::CComponentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComponentDlg::IDD, pParent)
{

}

CComponentDlg::~CComponentDlg()
{
}

void CComponentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComponentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CComponentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CComponentDlg message handlers


void CComponentDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_selectString.clear();
	int iStartID = IDC_CHECK_AL2O3;
	int iEndID = IDC_CHECK_ZrO2;
	CString strValue("");
	for(int i = iStartID; i <= iEndID; i++)
	{
		if (((CButton*)GetDlgItem(i))->GetCheck())//判断复选框是否选中
		{
			GetDlgItemText(i, strValue);
			m_selectString.push_back(strValue);
		}
	}
	CDialogEx::OnOK();
}
