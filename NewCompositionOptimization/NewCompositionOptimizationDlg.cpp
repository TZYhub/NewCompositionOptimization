
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
	DDX_Control(pDX, IDC_EDIT1, m_inputComEdit);
	DDX_Control(pDX, IDC_EDIT2, m_inputNatureEdit);
}

BEGIN_MESSAGE_MAP(CNewCompositionOptimizationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START_OPTIMIZATION, &CNewCompositionOptimizationDlg::OnBnClickedBtnStartOptimization)
	ON_BN_CLICKED(IDC_BTN_SELECT_COMPONENT, &CNewCompositionOptimizationDlg::OnBnClickedBtnSelectComponent)
	ON_BN_CLICKED(IDC_BTN_SELECT_NATURE, &CNewCompositionOptimizationDlg::OnBnClickedBtnSelectNature)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMPONENT, &CNewCompositionOptimizationDlg::OnNMDblclkListComponent)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CNewCompositionOptimizationDlg::OnEnKillfocusEdit1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NATURE, &CNewCompositionOptimizationDlg::OnNMDblclkListNature)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CNewCompositionOptimizationDlg::OnEnKillfocusEdit2)
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
	LoadNatureChoiceValue();
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
	m_NatureList.InsertColumn(1, _T("性    质"), LVCFMT_CENTER, 120); 
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
	CString strCompositionName;
	CString strNatureName;
	CString strCoefficientValue;
	float CValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		b = vtCString.at(i).ReverseFind(',');
		strCompositionName = vtCString.at(i).Left(a);//1.取出逗号前的组分名
		strNatureName = vtCString.at(i).Mid(a + 1, b - a - 1); //2.取出逗号后的性质名
		strCoefficientValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - b - 1);//3.取出性质系数的值
		CValue = _ttof(strCoefficientValue);

		NCC.CompositionName = strCompositionName;
		NCC.NatureName = strNatureName;
		NCC.CoefficientValue = CValue;
		m_vtFixedNatureCalcCoe.push_back(NCC);//T推入数组中
	}

}

//T加载性质极大值和极小值
void CNewCompositionOptimizationDlg::LoadNatureChoiceValue()
{
	//1.从配置文件中获取固定性质系数
	vector<CString> vtCString;
	LoadVtStrFromIni(vtCString, _T("性质取极值"));
	UINT iSize = vtCString.size();
	int a = 0;
	CString strNatureName;
	CString strChoiceValue;
	ChoiceValue cv;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		strNatureName = vtCString.at(i).Left(a);//1.取出逗号前的组分名
		strChoiceValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - a - 1);//3.取出性质系数的值
		if ("max" == strChoiceValue)
		{
			cv = LargeValue;
		}
		else if ("min" == strChoiceValue)
		{
			cv = SmallVaule;
		}
		m_mapNatureChoiceValue.insert(make_pair(strNatureName, cv));//T推入映射中
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

//当组分数组有改动时，调用该函数重新显示
void CNewCompositionOptimizationDlg::UpDateComponetList()
{
	m_ComponentList.DeleteAllItems();
	//从一个数组里导入需要计算的组成物质
	if (!m_vtComponent.empty())//有数据
	{
		vector<CComponent>::iterator it = m_vtComponent.begin();
		vector<CComponent>::iterator itEnd = m_vtComponent.end();
		int pos = 1;
		CString str;
		for (; it != itEnd; ++it, ++pos)
		{
			str.Format(_T("%d"), pos);
			m_ComponentList.InsertItem(pos, str);
			m_ComponentList.SetItemText(pos-1, 1, it->GetComponentName());
			m_ComponentList.SetItemText(pos-1, 2, it->GetStrComponentRange());
		}
	}
	UpDateResultList();
}

//当性质数组有改动时，调用该函数重新显示
void CNewCompositionOptimizationDlg::UpDateNatureList()
{
	m_NatureList.DeleteAllItems();
	//从一个数组里导入需要计算的组成物质
	if (!m_vtNature.empty())//有数据
	{
		vector<CNature>::iterator it = m_vtNature.begin();
		vector<CNature>::iterator itEnd = m_vtNature.end();
		int pos = 1;
		CString str;
		for (; it != itEnd; ++it, ++pos)
		{
			str.Format(_T("%d"), pos);
			m_NatureList.InsertItem(pos, str); 
			m_NatureList.SetItemText(pos-1, 1, it->GetNatureName());
			m_NatureList.SetItemText(pos-1, 2, it->GetStrNatureRange());
		}
	}
	UpDateResultList();
}

//当组分数组或性质有改动时，调用该函数重新显示结果列表
void CNewCompositionOptimizationDlg::UpDateResultList()
{
	m_ResultList.DeleteAllItems();
	int pos = 1;
	if (!m_vtComponent.empty())//有数据
	{
		vector<CComponent>::iterator it = m_vtComponent.begin();
		vector<CComponent>::iterator itEnd = m_vtComponent.end();

		for (; it != itEnd; ++it, ++pos)
		{
			m_ResultList.InsertColumn(pos, it->GetComponentName(), LVCFMT_CENTER, 80);
		}
	}

	if (!m_vtNature.empty())//有数据
	{
		vector<CNature>::iterator it = m_vtNature.begin();
		vector<CNature>::iterator itEnd = m_vtNature.end();
		for (; it != itEnd; ++it, ++pos)
		{
			m_ResultList.InsertColumn(pos, it->GetNatureName(), LVCFMT_CENTER, 80); 
		}
	}
	m_ResultList.InsertItem(1, _T("优选结果"));
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

//T获取选择的复选框，传入为Component获取组分，传入为Nature获取性质
BOOL CNewCompositionOptimizationDlg::GetSelectCheckBox(const CString& str)
{
	BOOL rt = FALSE;
	int iStartID = -1;
	int iEndID = -1;
	if ("Component" == str)
	{
		iStartID = IDC_CHECK_AL2O3;
		iEndID = IDC_CHECK_ZrO2;
	}
	else if ("Nature" == str)
	{
		iStartID = IDC_CHECK_1_RPZXS;
		iEndID = IDC_CHECK_31_RHWD;
	}
	map<CString, ChoiceValue>::iterator itMap;
	CComponent component;
	CNature nature;
	CString strValue;

	for(int i = iStartID; i < iEndID; i++)
	{
		if (((CButton*)GetDlgItem(i))->GetCheck())//判断复选框是否选中
		{
			GetDlgItemText(i, strValue);
			if ("Component" == str)
			{
				component.SetComponentName(strValue);
				m_vtComponent.push_back(component);
				rt = TRUE;
			}
			else if ("Nature" == str)
			{
				nature.SetNatureName(strValue);
				//从配置文件中获取的极大值或极小值
				itMap = m_mapNatureChoiceValue.find(strValue);
				if (itMap != m_mapNatureChoiceValue.end())
				{
					nature.SetNatureChoiceValue(itMap->second);
				}
				m_vtNature.push_back(nature);
				rt = TRUE;
			}
		}
	}
	return rt;
}


void CNewCompositionOptimizationDlg::CalculateNature()
{
	//T1、先把组分截断数组进行组合
	CombinationTruncationData();

	//T2、根据组合中每种组分的含量来获取不同性质的计算系数


	//T3、有上面或去的系数和组分含量来计算性质





	
	//分组完成


	//接下来计算每一组对应的膨胀系数值、折射率。。（按照输入的顺序来）
	//	vector<CNature>::iterator vtCString = m_vtNature.begin();
	//	vector<CNature>::iterator vtCStringEnd = m_vtNature.end();
	//	for (; vtCString!=vtCStringEnd; ++vtCString)
	//	{
	//		//接下来计算每一组对应的膨胀系数值、折射率。。（按照输入的顺序来）
	//		map<int,map<CString,float>>::iterator itMap2;
	//		//膨胀系数
	//		vector<float> vtNature;//获取各物质对应的膨胀系数
	//		//size大小为m_vtComposition.size();
	//		for (int i=0; i<typeNumber; i++)
	//		{
	//			itMap2 = m_mapAllNature.find(i);//找各个物质如 SiO2 Al2O3..
	//			if (itMap2 != m_mapAllNature.end())//如果找到了
	//			{
	//				map<CString,float>::iterator map3 = itMap2->second.find(*vtCString);
	//				if (map3 != itMap2->second.end())//如果找到了
	//				{
	//					vtNature.push_back(map3->second);
	//				}
	//			}	
	//		}
	//		int times = m_subResult.size();//有多少分组，循环多少次
	//		float resultValue = 0;
	//		vector<float> vtFloat;
	//		vtFloat.clear();
	//		for (int i=0; i<times; i++)
	//		{
	//			resultValue = 0;
	//			for (int j=0; j<typeNumber; j++)
	//			{
	//				resultValue += vtNature.at(j) * m_subResult.at(i).at(j);
	//			}
	//			vtFloat.push_back(resultValue/100);
	//		}
	//		m_mapResult.insert(make_pair(*vtCString, vtFloat));
	//	}
}


//index 为需要计算的数组中的第几个值 
void CNewCompositionOptimizationDlg::Calculate(const int index, vector<float> &vtSub)
{
	if (index < m_vtComponent.size())//表明这不是最后一个
	{
		//it--;//减去判断时加的1
		vector<float> vt = m_vtComponent.at(index).GetVtComponentRange();
		int subSize = vt.size();
		for (int i = 0; i < subSize; i++)
		{
			vtSub.at(index) = vt.at(i);
			Calculate(index+1, vtSub);
		}
	}
	else//是最后一个
	{
		m_vtComponentGrouping.push_back(vtSub);
	}

}

//T组合截断组分数据
void CNewCompositionOptimizationDlg::CombinationTruncationData()
{
	vector<float> vtSub;
	int typeNumber = m_vtComponent.size();//有多少种物质
	for (int i=0; i<typeNumber; i++)
	{
		vtSub.push_back(-1);
	}
	//调用递归函数实现循环，实现分组
	//分组数据存放到了vector<vector<float>> m_subResult中
	//0组 1 3 5 7
	//1组 1 3 5 8
	//2组 1 3 6 7
	//   ...
	vector<float> vt = m_vtComponent.at(0).GetVtComponentRange();
	int subSize = vt.size();
	for (int i = 0; i < subSize; i++)
	{
		vtSub.at(0) = vt.at(i);
		Calculate(1, vtSub);
	}
	

	for (int i = 0; i < typeNumber; i++)//最外层的循环
	{
		
		for (int j = 0; j < subSize; j++)
		{
			vtSub.at(0) = vt.at(j);
			Calculate(i+1, vtSub);
		}
	}
}

void CNewCompositionOptimizationDlg::OnBnClickedBtnStartOptimization()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bIsSelectComponent && m_bIsSelectNature)
	{
		//有任意列表没有数据，则退出
		if (m_vtComponent.empty())
		{
			MessageBox(_T("没有输入组分！"));
			return;
		}
		if (m_vtNature.empty())
		{
			MessageBox(_T("没有输入性质！"));
			return;
		}
		//清理输出结果列表
		UpDateResultList();
		//三、开始计算
		CalculateNature();
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
	m_vtComponent.clear();
	m_bIsSelectComponent = GetSelectCheckBox(_T("Component"));
	UpDateComponetList();
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectNature()
{
	// TODO: 在此添加控件通知处理程序代码
	m_vtNature.clear();
	m_bIsSelectNature = GetSelectCheckBox(_T("Nature"));
	UpDateNatureList();
}


void CNewCompositionOptimizationDlg::OnNMDblclkListComponent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem != -1 && 2 == pNMListView->iSubItem)
	{
		m_row = pNMListView->iItem;							//m_row为被选中行的行序号（int类型成员变量）
		m_column = pNMListView->iSubItem;						//m_column为被选中行的列序号（int类型成员变量）
		m_ComponentList.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem, LVIR_LABEL, rc);//取得子项的矩形

		rc.bottom += 3;

		m_inputComEdit.SetParent(&m_ComponentList);
		PTSTR ch=new TCHAR[20];
		m_ComponentList.GetItemText(pNMListView->iItem, pNMListView->iSubItem, ch, 20);//取得子项的内容
		m_inputComEdit.SetWindowText(ch);					//将子项的内容显示到编辑框中
		m_inputComEdit.ShowWindow(SW_SHOW);					//显示编辑框
		m_inputComEdit.MoveWindow(&rc);						//将编辑框移动到子项上面，覆盖在子项上
		m_inputComEdit.SetFocus();							//使编辑框取得焦点
		m_inputComEdit.CreateSolidCaret(1, rc.Height() - 5);//创建一个光标
		m_inputComEdit.ShowCaret();							//显示光标
		m_inputComEdit.SetSel(-1);							//使光标移到最后面
		delete ch;
	}
	*pResult = 0;
}


void CNewCompositionOptimizationDlg::OnEnKillfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_inputComEdit.GetWindowText(str);//取得编辑框的内容
	m_ComponentList.SetItemText(m_row, m_column, str);//将该内容更新到CListCtrl中
	//T把字符串设置到组分数组中,函数内部解析字符串，并存储到范围数组中
	m_vtComponent.at(m_row).SetStrComponentRange(str);
	m_inputComEdit.ShowWindow(SW_HIDE);//隐藏编辑框
}


void CNewCompositionOptimizationDlg::OnNMDblclkListNature(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem != -1 && pNMListView->iSubItem == 2)
	{
		m_row = pNMListView->iItem;								//m_row为被选中行的行序号（int类型成员变量）
		m_column = pNMListView->iSubItem;							//m_column为被选中行的列序号（int类型成员变量）
		m_NatureList.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem, LVIR_LABEL, rc);//取得子项的矩形

		rc.bottom += 3;

		m_inputNatureEdit.SetParent(&m_NatureList);
		PTSTR ch = new TCHAR[20];
		m_NatureList.GetItemText(pNMListView->iItem, pNMListView->iSubItem, ch, 20);//取得子项的内容
		m_inputNatureEdit.SetWindowText(ch);					//将子项的内容显示到编辑框中
		m_inputNatureEdit.ShowWindow(SW_SHOW);					//显示编辑框
		m_inputNatureEdit.MoveWindow(&rc);						//将编辑框移动到子项上面，覆盖在子项上
		m_inputNatureEdit.SetFocus();							//使编辑框取得焦点
		m_inputNatureEdit.CreateSolidCaret(1, rc.Height() - 5);	//创建一个光标
		m_inputNatureEdit.ShowCaret();							//显示光标
		m_inputNatureEdit.SetSel(-1);							//使光标移到最后面
	}
	*pResult = 0;
}


void CNewCompositionOptimizationDlg::OnEnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断输入是否符合要求（后续处理）
	CString str;
	m_inputNatureEdit.GetWindowText(str);//取得编辑框的内容
	m_NatureList.SetItemText(m_row, m_column, str);//将该内容更新到CListCtrl中
	//T把字符串设置到性质数组中,函数内部解析字符串，并存储到范围数组中
	m_vtNature.at(m_row).SetStrNatureRange(str);
	m_inputNatureEdit.ShowWindow(SW_HIDE);//隐藏编辑框
}
