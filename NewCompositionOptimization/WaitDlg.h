#pragma once
#include "afxwin.h"
#include "PictureEx.h"


// CWaitDlg �Ի���

class CWaitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWaitDlg)

public:
	CWaitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWaitDlg();

// �Ի�������
	enum { IDD = IDD_WAIT_DIALOG };

	void EndDlg();

protected:
	BOOL m_bIsDoModal;

public:
	BOOL GetIsDoModel()
	{
		BOOL b2 = TRUE,b3 = TRUE;
		PVOID pb1 = &m_bIsDoModal;
		return (BOOL)InterlockedCompareExchange((LPLONG)pb1,(LONG)b2,(LONG)b3);
	}
	void SetIsDoModel(BOOL bIsOpen);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CPictureEx m_gifPicture;
	virtual BOOL OnInitDialog();
};
