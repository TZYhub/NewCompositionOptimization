// WaitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NewCompositionOptimization.h"
#include "WaitDlg.h"
#include "afxdialogex.h"


// CWaitDlg 对话框

IMPLEMENT_DYNAMIC(CWaitDlg, CDialogEx)

CWaitDlg::CWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWaitDlg::IDD, pParent)
	,m_bIsDoModal(FALSE)
{

}

CWaitDlg::~CWaitDlg()
{
}

void CWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAIT, m_gifPicture);
}


BEGIN_MESSAGE_MAP(CWaitDlg, CDialogEx)
END_MESSAGE_MAP()


// CWaitDlg 消息处理程序


BOOL CWaitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(),0,(255*60)/100,2); //具有0%透明度
		FreeLibrary(hInst); 
	}

	if (m_gifPicture.Load(MAKEINTRESOURCE(IDR_WAIT_GIF),_T("Gif")))
			m_gifPicture.Draw();  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CWaitDlg::SetIsDoModel(BOOL bIsOpen)
{
	InterlockedExchange(LPLONG(&m_bIsDoModal),(LONG)bIsOpen);
}

void CWaitDlg::EndDlg()
{
	CDialog::OnCancel();
}