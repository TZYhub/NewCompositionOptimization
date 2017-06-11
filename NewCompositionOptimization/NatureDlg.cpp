// NatureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewCompositionOptimization.h"
#include "NatureDlg.h"
#include "afxdialogex.h"


// CNatureDlg dialog

IMPLEMENT_DYNAMIC(CNatureDlg, CDialogEx)

CNatureDlg::CNatureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNatureDlg::IDD, pParent)
{

}

CNatureDlg::~CNatureDlg()
{
}

void CNatureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNatureDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNatureDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNatureDlg message handlers


void CNatureDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_selectNatureString.clear();
	int iStartID = IDC_CHECK_1_RPZXS;
	int iEndID = IDC_CHECK_31_RHWD;
	CString strValue("");
	for(int i = iStartID; i <= iEndID; i++)
	{
		if (((CButton*)GetDlgItem(i))->GetCheck())//判断复选框是否选中
		{
			GetDlgItemText(i, strValue);
			m_selectNatureString.push_back(strValue);
		}
	}
	CDialogEx::OnOK();
}
