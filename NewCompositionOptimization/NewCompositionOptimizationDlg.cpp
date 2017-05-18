
// NewCompositionOptimizationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NewCompositionOptimization.h"
#include "NewCompositionOptimizationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CNewCompositionOptimizationDlg 对话框




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


// CNewCompositionOptimizationDlg 消息处理程序

BOOL CNewCompositionOptimizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Init();
	LoadFixeCalcCoe();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNewCompositionOptimizationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNewCompositionOptimizationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNewCompositionOptimizationDlg::Init()
{
	InitCompositionList();						//初始化组成列表
	InitNatureList();							//初始化性质列表
	InitResultList();							//初始化结果列表
}

void CNewCompositionOptimizationDlg::AutoSizeListColumn(CListCtrl &clist,int column)
{
	clist.SetColumnWidth(column, LVSCW_AUTOSIZE);  
	int nColumnWidth = clist.GetColumnWidth(column);  
	clist.SetColumnWidth(column, LVSCW_AUTOSIZE_USEHEADER);  
	int nHeaderWidth = clist.GetColumnWidth(column);  
	clist.SetColumnWidth(column, max(nColumnWidth, nHeaderWidth));
}

//初始化组成列表
void CNewCompositionOptimizationDlg::InitCompositionList()
{
	//先删除所有行和所有列，再加载
	m_ComponentList.DeleteAllItems();
	int nColumnCount = m_ComponentList.GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_ComponentList.DeleteColumn(0);
	}


	LONG lStyle;
	lStyle = GetWindowLong(m_ComponentList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle |= LVS_REPORT;										//设置style
	DWORD dwStyle = m_ComponentList.GetExtendedStyle();   
	dwStyle |= LVS_EX_FULLROWSELECT;							// 选中某行使整行高亮（只适用与report 风格的listctrl ）   
	dwStyle |= LVS_EX_GRIDLINES;								// 网格线（只适用与report 风格的listctrl ）      
	m_ComponentList.SetExtendedStyle(dwStyle);				// 设置扩展风格 

	m_ComponentList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 40); 
	m_ComponentList.InsertColumn(1, _T("组成"), LVCFMT_CENTER, 60); 
	m_ComponentList.InsertColumn(2, _T("组成范围"), LVCFMT_CENTER, 60); 
	//自动调整截取宽度
	AutoSizeListColumn(m_ComponentList, 2);

}

//初始化性质列表
void CNewCompositionOptimizationDlg::InitNatureList()
{
	//先删除所有行和所有列，再加载
	m_NatureList.DeleteAllItems();
	int nColumnCount = m_NatureList.GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	for (int i = 0;i < nColumnCount; i++)
	{
		m_NatureList.DeleteColumn(0);
	}

	LONG lStyle;
	lStyle = GetWindowLong(m_NatureList.m_hWnd, GWL_STYLE);	//获取当前窗口style
	lStyle |= LVS_REPORT;									//设置style
	DWORD dwStyle = m_NatureList.GetExtendedStyle();   
	dwStyle |= LVS_EX_FULLROWSELECT;						// 选中某行使整行高亮（只适用与report 风格的listctrl ）   
	dwStyle |= LVS_EX_GRIDLINES;							// 网格线（只适用与report 风格的listctrl ）      
	m_NatureList.SetExtendedStyle(dwStyle);					// 设置扩展风格 


	m_NatureList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 40); 
	m_NatureList.InsertColumn(1, _T("性    质"), LVCFMT_CENTER, 60); 
	m_NatureList.InsertColumn(2, _T("性质范围"), LVCFMT_CENTER, 80);
	//自动调整截取宽度
	AutoSizeListColumn(m_NatureList, 2);

}

//初始化结果列表
void CNewCompositionOptimizationDlg::InitResultList()
{
	m_ResultList.DeleteAllItems();
	int nColumnCount = m_ResultList.GetHeaderCtrl()->GetItemCount();
	for (int i = 0;i < nColumnCount; i++)
	{
		m_ResultList.DeleteColumn(0);
	}
	LONG lStyle;
	lStyle = GetWindowLong(m_ResultList.m_hWnd, GWL_STYLE);	//获取当前窗口style
	lStyle |= LVS_REPORT;									//设置style
	DWORD dwStyle = m_ResultList.GetExtendedStyle();   
	dwStyle |= LVS_EX_FULLROWSELECT;						// 选中某行使整行高亮（只适用与report 风格的listctrl ）   
	dwStyle |= LVS_EX_GRIDLINES;							// 网格线（只适用与report 风格的listctrl ）      
	m_ResultList.SetExtendedStyle(dwStyle);					// 设置扩展风格 
	m_ResultList.InsertColumn(0, _T("组分及性质"), LVCFMT_CENTER, 80); 

	m_ResultList.InsertItem(1, _T("优选结果"));
}

//T加载固定性质系数
void CNewCompositionOptimizationDlg::LoadFixeCalcCoe()
{
	//1.从配置文件中获取固定性质系数
	vector<CString> vtCString;
	LoadVtStrFromIni(vtCString, _T("固定性质系数"));
	//2.把组分名、性质名及其对应的固定性质计算系数添加到数组中
	UINT iSize = vtCString.size();
	int a = 0, b = 0;
	SNatureCalcCoefficient NCC;
	float CValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		b = vtCString.at(i).ReverseFind(',');
		CString strCompositionName = vtCString.at(i).Left(a);//1.取出逗号前的组分名
		CString strNatureName = vtCString.at(i).Mid(a + 1, b - a - 1); //2.取出逗号后的性质名
		CString strCoefficientValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - b - 1);//3.取出性质系数的值
		CValue = _ttof(strCoefficientValue);

		NCC.CompositionName = strCompositionName;
		NCC.NatureName = strNatureName;
		NCC.CoefficientValue = CValue;
		m_vtFixedNatureCalcCoe.push_back(NCC);//T推入数组中
	}

}

//从配置文件中获取字符串数据
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
		MessageBox(_T("读取配置文件中的组分失败,请检查配置文件！"));
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


//T获取性质计算系数,包括固定值和不固定值的,每次计算前都来调用此函数，以获取对应系数
float CNewCompositionOptimizationDlg::GetNatureCalcCoefficient(const CString& cName, const CString nName,const float cValue)
{
	//T1、从固定值中查是否有，有，则返回值
	float coeValue = GetFixedNatureCalcCoe(cName, nName, cValue);
	//T2、调用计算公式来计算系数
	if (coeValue < 0)//T如果固定值中没有，则使用公式计算
	{
		coeValue = GetNatureCalcCoeWithFormula(cName, nName, cValue);
	}
	return coeValue;
}

//T从固定值中获取系数，若有，则返回大于0的值，若无则返回-1
float CNewCompositionOptimizationDlg::GetFixedNatureCalcCoe(const CString& cName, const CString& nName, const float cValue)
{
	return -1;
}

//T使用公式计算性质系数
float CNewCompositionOptimizationDlg::GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue)
{
	return -1;
}

void CNewCompositionOptimizationDlg::OnBnClickedBtnStartOptimization()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bIsSelectComponent && m_bIsSelectNature)
	{

	
	//T从组分表格中获取组分名及其取值范围
	//T从性质表格中获取性质名及其取值范围
	//T对数据进行处理

	//T计算

	//T进行初选

	//T进行精选

	//T结果显示
	}
	else if (!m_bIsSelectComponent)
	{
		MessageBox(_T("请先选择组分！"));
	}
	else if (!m_bIsSelectNature)
	{
		MessageBox(_T("请先选择性质！"));
	}
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectComponent()
{
	// TODO: 在此添加控件通知处理程序代码
	//把打钩的复选框，写入组分表格中

	m_bIsSelectComponent = true;
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectNature()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSelectNature = true;
}
