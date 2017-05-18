
// NewCompositionOptimizationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NewCompositionOptimization.h"
#include "NewCompositionOptimizationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNewCompositionOptimizationDlg �Ի���




CNewCompositionOptimizationDlg::CNewCompositionOptimizationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewCompositionOptimizationDlg::IDD, pParent)
	,m_bIsSelectComponent(false)
	,m_bIsSelectNature(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewCompositionOptimizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COMPONENT, m_ComponentList);
	DDX_Control(pDX, IDC_LIST_NATURE, m_NatureList);
	DDX_Control(pDX, IDC_LIST_RESULT, m_ResultList);
}

BEGIN_MESSAGE_MAP(CNewCompositionOptimizationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START_OPTIMIZATION, &CNewCompositionOptimizationDlg::OnBnClickedBtnStartOptimization)
	ON_BN_CLICKED(IDC_BTN_SELECT_COMPONENT, &CNewCompositionOptimizationDlg::OnBnClickedBtnSelectComponent)
	ON_BN_CLICKED(IDC_BTN_SELECT_NATURE, &CNewCompositionOptimizationDlg::OnBnClickedBtnSelectNature)
END_MESSAGE_MAP()


// CNewCompositionOptimizationDlg ��Ϣ�������

BOOL CNewCompositionOptimizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Init();
	LoadFixeCalcCoe();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CNewCompositionOptimizationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNewCompositionOptimizationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNewCompositionOptimizationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNewCompositionOptimizationDlg::Init()
{
	InitCompositionList();						//��ʼ������б�
	InitNatureList();							//��ʼ�������б�
	InitResultList();							//��ʼ������б�
}

void CNewCompositionOptimizationDlg::AutoSizeListColumn(CListCtrl &clist,int column)
{
	clist.SetColumnWidth(column, LVSCW_AUTOSIZE);  
	int nColumnWidth = clist.GetColumnWidth(column);  
	clist.SetColumnWidth(column, LVSCW_AUTOSIZE_USEHEADER);  
	int nHeaderWidth = clist.GetColumnWidth(column);  
	clist.SetColumnWidth(column, max(nColumnWidth, nHeaderWidth));
}

//��ʼ������б�
void CNewCompositionOptimizationDlg::InitCompositionList()
{
	//��ɾ�������к������У��ټ���
	m_ComponentList.DeleteAllItems();
	int nColumnCount = m_ComponentList.GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_ComponentList.DeleteColumn(0);
	}


	LONG lStyle;
	lStyle = GetWindowLong(m_ComponentList.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle |= LVS_REPORT;										//����style
	DWORD dwStyle = m_ComponentList.GetExtendedStyle();   
	dwStyle |= LVS_EX_FULLROWSELECT;							// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl ��   
	dwStyle |= LVS_EX_GRIDLINES;								// �����ߣ�ֻ������report ����listctrl ��      
	m_ComponentList.SetExtendedStyle(dwStyle);				// ������չ��� 

	m_ComponentList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40); 
	m_ComponentList.InsertColumn(1, _T("���"), LVCFMT_CENTER, 60); 
	m_ComponentList.InsertColumn(2, _T("��ɷ�Χ"), LVCFMT_CENTER, 60); 
	//�Զ�������ȡ���
	AutoSizeListColumn(m_ComponentList, 2);

}

//��ʼ�������б�
void CNewCompositionOptimizationDlg::InitNatureList()
{
	//��ɾ�������к������У��ټ���
	m_NatureList.DeleteAllItems();
	int nColumnCount = m_NatureList.GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	for (int i = 0;i < nColumnCount; i++)
	{
		m_NatureList.DeleteColumn(0);
	}

	LONG lStyle;
	lStyle = GetWindowLong(m_NatureList.m_hWnd, GWL_STYLE);	//��ȡ��ǰ����style
	lStyle |= LVS_REPORT;									//����style
	DWORD dwStyle = m_NatureList.GetExtendedStyle();   
	dwStyle |= LVS_EX_FULLROWSELECT;						// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl ��   
	dwStyle |= LVS_EX_GRIDLINES;							// �����ߣ�ֻ������report ����listctrl ��      
	m_NatureList.SetExtendedStyle(dwStyle);					// ������չ��� 


	m_NatureList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40); 
	m_NatureList.InsertColumn(1, _T("��    ��"), LVCFMT_CENTER, 60); 
	m_NatureList.InsertColumn(2, _T("���ʷ�Χ"), LVCFMT_CENTER, 80);
	//�Զ�������ȡ���
	AutoSizeListColumn(m_NatureList, 2);

}

//��ʼ������б�
void CNewCompositionOptimizationDlg::InitResultList()
{
	m_ResultList.DeleteAllItems();
	int nColumnCount = m_ResultList.GetHeaderCtrl()->GetItemCount();
	for (int i = 0;i < nColumnCount; i++)
	{
		m_ResultList.DeleteColumn(0);
	}
	LONG lStyle;
	lStyle = GetWindowLong(m_ResultList.m_hWnd, GWL_STYLE);	//��ȡ��ǰ����style
	lStyle |= LVS_REPORT;									//����style
	DWORD dwStyle = m_ResultList.GetExtendedStyle();   
	dwStyle |= LVS_EX_FULLROWSELECT;						// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl ��   
	dwStyle |= LVS_EX_GRIDLINES;							// �����ߣ�ֻ������report ����listctrl ��      
	m_ResultList.SetExtendedStyle(dwStyle);					// ������չ��� 
	m_ResultList.InsertColumn(0, _T("��ּ�����"), LVCFMT_CENTER, 80); 

	m_ResultList.InsertItem(1, _T("��ѡ���"));
}

//T���ع̶�����ϵ��
void CNewCompositionOptimizationDlg::LoadFixeCalcCoe()
{
	//1.�������ļ��л�ȡ�̶�����ϵ��
	vector<CString> vtCString;
	LoadVtStrFromIni(vtCString, _T("�̶�����ϵ��"));
	//2.��������������������Ӧ�Ĺ̶����ʼ���ϵ����ӵ�������
	UINT iSize = vtCString.size();
	int a = 0, b = 0;
	SNatureCalcCoefficient NCC;
	float CValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		b = vtCString.at(i).ReverseFind(',');
		CString strCompositionName = vtCString.at(i).Left(a);//1.ȡ������ǰ�������
		CString strNatureName = vtCString.at(i).Mid(a + 1, b - a - 1); //2.ȡ�����ź��������
		CString strCoefficientValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - b - 1);//3.ȡ������ϵ����ֵ
		CValue = _ttof(strCoefficientValue);

		NCC.CompositionName = strCompositionName;
		NCC.NatureName = strNatureName;
		NCC.CoefficientValue = CValue;
		m_vtFixedNatureCalcCoe.push_back(NCC);//T����������
	}

}

//�������ļ��л�ȡ�ַ�������
void CNewCompositionOptimizationDlg::LoadVtStrFromIni(vector<CString> &vtStr,const CString& keyStr)
{
	CString strRead = _T("");
	CString des = _T("");
	::GetCurrentDirectory(MAX_PATH, des.GetBuffer(MAX_PATH));
	des.ReleaseBuffer();
	des += "\\config.ini";
	int nCount = GetPrivateProfileInt(keyStr, _T("nCount"), 0, des);
	if (0 == nCount)
	{
		MessageBox(_T("��ȡ�����ļ��е����ʧ��,���������ļ���"));
		return;
	}
	else
	{
		TCHAR ch[50];
		for (int i = 1; i <= nCount; i++)
		{
			_itot_s(i, ch, _countof(ch), 10);
			GetPrivateProfileString(keyStr, ch, _T(""), strRead.GetBufferSetLength(50), 50, des);
			strRead.ReleaseBuffer();
			vtStr.push_back(strRead);
		}
	}
}	


//T��ȡ���ʼ���ϵ��,�����̶�ֵ�Ͳ��̶�ֵ��,ÿ�μ���ǰ�������ô˺������Ի�ȡ��Ӧϵ��
float CNewCompositionOptimizationDlg::GetNatureCalcCoefficient(const CString& cName, const CString nName,const float cValue)
{
	//T1���ӹ̶�ֵ�в��Ƿ��У��У��򷵻�ֵ
	float coeValue = GetFixedNatureCalcCoe(cName, nName, cValue);
	//T2�����ü��㹫ʽ������ϵ��
	if (coeValue < 0)//T����̶�ֵ��û�У���ʹ�ù�ʽ����
	{
		coeValue = GetNatureCalcCoeWithFormula(cName, nName, cValue);
	}
	return coeValue;
}

//T�ӹ̶�ֵ�л�ȡϵ�������У��򷵻ش���0��ֵ�������򷵻�-1
float CNewCompositionOptimizationDlg::GetFixedNatureCalcCoe(const CString& cName, const CString& nName, const float cValue)
{
	return -1;
}

//Tʹ�ù�ʽ��������ϵ��
float CNewCompositionOptimizationDlg::GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue)
{
	return -1;
}

void CNewCompositionOptimizationDlg::OnBnClickedBtnStartOptimization()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bIsSelectComponent && m_bIsSelectNature)
	{

	
	//T����ֱ���л�ȡ���������ȡֵ��Χ
	//T�����ʱ���л�ȡ����������ȡֵ��Χ
	//T�����ݽ��д���

	//T����

	//T���г�ѡ

	//T���о�ѡ

	//T�����ʾ
	}
	else if (!m_bIsSelectComponent)
	{
		MessageBox(_T("����ѡ����֣�"));
	}
	else if (!m_bIsSelectNature)
	{
		MessageBox(_T("����ѡ�����ʣ�"));
	}
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectComponent()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�Ѵ򹳵ĸ�ѡ��д����ֱ����

	m_bIsSelectComponent = true;
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectNature()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bIsSelectNature = true;
}
