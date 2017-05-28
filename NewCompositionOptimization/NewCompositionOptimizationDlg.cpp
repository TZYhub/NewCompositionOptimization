
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
	,m_row(-1)
	,m_column(-1)
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
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CNewCompositionOptimizationDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BIN_IMPORT, &CNewCompositionOptimizationDlg::OnBnClickedBinImport)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CNewCompositionOptimizationDlg::OnBnClickedBtnExport)
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
	LoadComponentFixedValue();
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
	CString strComponentName;
	CString strNatureName;
	CString strCoefficientValue;
	float CValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		b = vtCString.at(i).ReverseFind(',');
		strComponentName = vtCString.at(i).Left(a);//1.取出逗号前的组分名
		strNatureName = vtCString.at(i).Mid(a + 1, b - a - 1); //2.取出逗号后的性质名
		strCoefficientValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - b - 1);//3.取出性质系数的值
		CValue = _ttof(strCoefficientValue);

		NCC.ComponentName = strComponentName;
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

//T从配置文件中获取组分截取值除的固定系数
void CNewCompositionOptimizationDlg::LoadComponentFixedValue()
{
	//1.从配置文件中获取固定性质系数
	map<CString, float> mapFixedValue;
	vector<CString> vtCString;
	LoadVtStrFromIni(vtCString, _T("组分固定系数"));
	UINT iSize = vtCString.size();
	int a = 0;
	CString strNatureName;
	CString strFixedValue;
	float fixedValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		strNatureName = vtCString.at(i).Left(a);//1.取出逗号前的组分名
		strFixedValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - a - 1);//2.取出固定系数的值
		fixedValue = _ttof(strFixedValue);
		mapFixedValue.insert(make_pair(strNatureName, fixedValue));//T推入映射中
	}
	CComponent::SetComponentFixedValue(mapFixedValue);//T赋值给组分类
}

//从配置文件中获取字符串数据
void CNewCompositionOptimizationDlg::LoadVtStrFromIni(vector<CString> &vtStr,const CString& keyStr, const CString& strPath /*= ""*/)
{
	CString strRead = _T("");
	CString des = _T("");
	
	if ("" == strPath)
	{
		::GetCurrentDirectory(MAX_PATH, des.GetBuffer(MAX_PATH));
		des.ReleaseBuffer();
		des += "\\config.ini";
	}
	else
	{
		des = strPath;
	}
	
	int nCount = GetPrivateProfileInt(keyStr, _T("nCount"), 0, des);
	if (0 == nCount)
	{
		MessageBox(_T("读取配置文件中的")+keyStr+_T("失败,请检查配置文件！"),DlgTitle);
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


//写数据到配置文件中WritePrivateProfileString
void CNewCompositionOptimizationDlg::WriteStrToIni(const vector<CString>& vtStr, const CString& keyStr, const CString& strPath)
{
	CString strWrite = _T("");
	int nCount = vtStr.size();
	strWrite.Format(_T("%d"),nCount);
	WritePrivateProfileString(keyStr,_T("nCount"),strWrite,strPath);
 	TCHAR ch[50];
 	for (int i = 1; i <= nCount; i++)
 	{
 		_itot_s(i, ch, _countof(ch), 10);
		WritePrivateProfileString(keyStr,ch,vtStr.at(i-1),strPath);
 		strWrite.ReleaseBuffer();
 	}
}


//当组分数组有改动时，调用该函数重新显示
void CNewCompositionOptimizationDlg::UpdateComponetList()
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
	UpdateResultList();
}

//当性质数组有改动时，调用该函数重新显示
void CNewCompositionOptimizationDlg::UpdateNatureList()
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
	UpdateResultList();
}

//当组分数组或性质有改动时，调用该函数重新显示结果列表
void CNewCompositionOptimizationDlg::UpdateResultList()
{
	m_ResultList.DeleteAllItems();
	int nColumnCount = m_ResultList.GetHeaderCtrl()->GetItemCount();
	for (int i = 0;i < nColumnCount; i++)
	{
		m_ResultList.DeleteColumn(0);
	}
	m_ResultList.InsertColumn(0, _T("组分及性质"), LVCFMT_CENTER, 80); 
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
	float coeValue ;
	bool rt = GetFixedNatureCalcCoe(cName, nName, cValue, coeValue);
	//T2、调用计算公式来计算系数
	if (!rt)//T如果固定值中没有，则使用公式计算
	{
		coeValue = GetNatureCalcCoeWithFormula(cName, nName, cValue);
		coeValue = 1;
	}
	return coeValue;
}

//T从固定值中获取系数，若有，则返回true,值存入rtValue中，若无则返回false
bool CNewCompositionOptimizationDlg::GetFixedNatureCalcCoe(const CString& cName, const CString& nName, const float cValue, float& rtValue)
{
	int iSize = m_vtFixedNatureCalcCoe.size();
	SNatureCalcCoefficient NCTemp;
	for (int i = 0; i < iSize; i++)
	{
		NCTemp = m_vtFixedNatureCalcCoe.at(i);
		if (NCTemp.ComponentName == cName && NCTemp.NatureName == nName)
		{
			rtValue = NCTemp.CoefficientValue;
			return true;
		}
	}
	return false;
}

//T使用公式计算性质系数
float CNewCompositionOptimizationDlg::GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue)
{
	//此处只写了SiO2的折射率计算
	if ("SiO2" == cName && "折射率" == nName)
	{
		return 1.475-0.0005*(cValue-67);//	SiO2的折射率系数=1.475-0.0005*（SiO2的组分含量-67）
	}
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

	for(int i = iStartID; i <= iEndID; i++)
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

//判断输入是否符合优选要求
bool CNewCompositionOptimizationDlg::JudgmentInput()
{
	//有任意列表没有数据，则退出///T输入范围值时是否添加判断输入合法
	CString str;
	if (m_vtComponent.empty())
	{
		MessageBox(_T("没有输入组分！"),DlgTitle);
		return false;
	}
	else//判断否输入范围值
	{
		int iSize = m_vtComponent.size();
		for (int i = 0; i < iSize; i++)
		{
			if ("" == m_vtComponent.at(i).GetStrComponentRange())
			{
				
				MessageBox(_T("请输入组分\"")+m_vtComponent.at(i).GetComponentName()+_T("\"的范围!"),DlgTitle);
				return false;
			}
		}
	}
	if (m_vtNature.empty())
	{
		MessageBox(_T("没有输入性质！"),DlgTitle);
		return false;
	}
	else//判断否输入范围值
	{
		int iSize = m_vtNature.size();
		for (int i = 0; i < iSize; i++)
		{
			if ("" == m_vtNature.at(i).GetStrNatureRange())
			{

				MessageBox(_T("请输入性质\"")+m_vtNature.at(i).GetNatureName()+_T("\"的范围!"),DlgTitle);
				return false;
			}
		}
	}
}


void CNewCompositionOptimizationDlg::CalculateNature()
{
	//T1、先把组分截断数组进行组合
	CombinationTruncationData();

	//T2、第二步：求和并计算出要使用的百分比
	CalculateComponentPercentage();

	//T3、根据组合中每种组分的含量来获取不同性质的计算系数,并计算出结果，存放在m_mapNatureResult中
	CalculateEachGroupNature();
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
		m_vtComponentGroupingBefore.push_back(vtSub);
	}
	
}

//T组合截断组分数据
void CNewCompositionOptimizationDlg::CombinationTruncationData()
{
	m_vtComponentGroupingBefore.clear();//清理上一次数据
	m_vtComponentGrouping.clear();
	int typeNumber = m_vtComponent.size();//有多少种物质
	vector<float> vtSub(typeNumber);
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
	m_vtComponentGrouping = m_vtComponentGroupingBefore;
}

//T求和并计算出组分百分比
void CNewCompositionOptimizationDlg::CalculateComponentPercentage()
{
	int iSize = m_vtComponentGrouping.size();
	int subSize = -1;
	float sumValue = 0;
	vector<float> vtGroup;//T每一组组合
	for (int i = 0; i < iSize; i++)
	{
		sumValue = 0;
		subSize = m_vtComponentGrouping.at(i).size();
		//T求i组的和
		for (int j = 0; j < subSize; j++)
		{
			sumValue += m_vtComponentGrouping.at(i).at(j);
		}
		//T求i组的百分比
		for (int j = 0; j < subSize; j++)
		{
			//m_vtComponentGrouping.at(i).at(j) /= (sumValue * 100);
			m_vtComponentGrouping.at(i).at(j) = (m_vtComponentGrouping.at(i).at(j)/sumValue) * 100;
		}
	}
}


//T计算每一组对应的性质
void CNewCompositionOptimizationDlg::CalculateEachGroupNature()
{
	int groupSize = m_vtComponentGrouping.size();//T分组数
	vector<float> vtResult(groupSize);//大小为m_vtComponentGrouping的大小
	int NSize = m_vtNature.size();
	vector<float> vtTemp;
	int tempSize;
	float resultValue = 0;
	for (int i = 0; i < NSize; i++)
	{
		
		for (int j = 0; j < groupSize; j++)
		{
			//获得截断分组的值，及组分的含量
			resultValue = 0;
			vtTemp = m_vtComponentGrouping.at(j);
			tempSize = vtTemp.size();
			for (int k = 0; k < tempSize; k++)
			{
				resultValue += vtTemp.at(k)*GetNatureCalcCoefficient(m_vtComponent.at(k).GetComponentName()
					,m_vtNature.at(i).GetNatureName(),vtTemp.at(k));
			}

			vtResult.at(j) = resultValue/100;
		}
		m_mapNatureResult.insert(make_pair(m_vtNature.at(i).GetNatureName(), vtResult));
	}
}


//成功：没有找到返回false 有一个或多个符合返回true
bool CNewCompositionOptimizationDlg::PreSelect(vector<int> &vtResultIndex)
{
	int size = m_vtComponentGrouping.size();
	vtResultIndex.clear();
	for (int i=0; i<size; i++)
	{
		vtResultIndex.push_back(i);//记录分组序号，符合条件的留下，不符合条件的删除
	}

	int NSize = m_vtNature.size();
	float fValue;
	vector<float> vtTempResult;

	vector<int>::iterator itVt;
	vector<int>::iterator itVtEnd;

	for (int nIndex = 0; nIndex < NSize; nIndex++)
	{
		map<CString,vector<float>>::iterator itMap = m_mapNatureResult.find(m_vtNature.at(nIndex).GetNatureName());
		if (itMap != m_mapNatureResult.end())
		{
			vtTempResult = itMap->second;
			int sizeIndex = vtResultIndex.size();
			for (int i=0; i<sizeIndex; i++)
			{
				fValue = vtTempResult.at(vtResultIndex.at(i));//取出对应的值
				if(!(fValue >= m_vtNature.at(nIndex).GetVtNatureRange().front() && fValue <= m_vtNature.at(nIndex).GetVtNatureRange().back()))//不符合要求
				{
					//vtResultIndex中的不符合要求的索引赋值为-1
					vtResultIndex.at(i) = -1;
				}
			}
		}

		//T清除为-1的索引值
		itVt = vtResultIndex.begin();
		for (int i = vtResultIndex.size()-1; i >= 0; i--)
		{
			if (-1 == vtResultIndex.at(i))
			{
				vtResultIndex.erase(itVt + i);
			}
		}

	}

	//如果符合要求的序号为0个返回假，即所有数据都被删除了
	if (0 == vtResultIndex.size())
	{
		return false;
	}
	return true;
}


//提取初选结果
void CNewCompositionOptimizationDlg::ExtractPreResult(vector<int> vtResultIndex)
{
	//先把需要进行精选的数据取出，放入m_afterPreResult和m_mapAfterPreResult中
	//先取出组合的数据

	vector<int>::iterator it = vtResultIndex.begin();
	vector<int>::iterator itEnd = vtResultIndex.end();
	vector<float> vtFloat;
	for (; it!=itEnd; ++it)
	{
		vtFloat.clear();

		vtFloat = m_vtComponentGrouping.at(*it);
		m_afterPreResult.push_back(vtFloat);
	}
	//再取出数据计算出的结果
	int NSize = m_vtNature.size();
	map<CString,vector<float>>::iterator itMap;
	for (int i = 0; i < NSize; i++)
	{
		itMap = m_mapNatureResult.find(m_vtNature.at(i).GetNatureName());
		if (itMap != m_mapNatureResult.end())
		{
			vector<float> vt = itMap->second;

			vector<int>::iterator it = vtResultIndex.begin();
			vector<int>::iterator itEnd = vtResultIndex.end();
			vtFloat.clear();
			for (; it!=itEnd; ++it)
			{
				vtFloat.push_back(vt.at(*it));
			}
			m_mapAfterPreResult.insert(make_pair(m_vtNature.at(i).GetNatureName(), vtFloat));
		}
	}
}

//精选
bool CNewCompositionOptimizationDlg::AccuSelect(vector<int> &vtResultIndex)
{

	//初选结果存储在m_afterPreResult和m_mapAfterPreResult中

	//如果只有一个需要比较的性质，则选出最接近性质的一组并返回
	if (1 == m_vtNature.size())
	{
		int index = 0;//记录是第几组为最值数据
		vector<float> vt = m_mapAfterPreResult.begin()->second;//因为只有一个性质，所以直接取第一个
		//ChoiceValue cv;
		//cv = m_vtNature.at(0).GetChoiceValue();
		if(LargeValue == m_vtNature.at(0).GetChoiceValue())//如果性质是取大值
		{
			//从这个计算出的性质结果的数组里面找出最大值即可
			vector<float>::iterator itVt = vt.begin();
			vector<float>::iterator itVtEnd = vt.end();
			int pos = 0;
			for (; itVt!=itVtEnd; ++itVt,++pos)
			{
				if (vt.at(index) < *itVt)
				{
					index = pos;
				}
			}
		}
		else if (SmallVaule == m_vtNature.at(0).GetChoiceValue())//如果性质是取小值
		{
			//从这个计算出的性质结果的数组里面找出最小值即可
			vector<float>::iterator itVt = vt.begin();
			vector<float>::iterator itVtEnd = vt.end();
			int pos = 0;
			for (; itVt!=itVtEnd; ++itVt, ++pos)
			{
				if (vt.at(index) > *itVt)
				{
					index = pos;
				}
			}
		}
		vtResultIndex.clear();
		vtResultIndex.push_back(index);
		return true;//返回找到的某一组数据的索引，在
	}
	//如果有两个或以上的比较性质，则使用正交法
	else if (m_vtNature.size() > 1)
	{
		//一、计算Di值
		vector<CNature>::iterator it = m_vtNature.begin();
		vector<CNature>::iterator itEnd = m_vtNature.end();
		int index = 0;//vector中的索引
		CNature temp;
		for (; it!=itEnd; ++it, ++index)
		{
			temp = m_vtNature.at(index);
			float diff = temp.GetVtNatureRange().back() - temp.GetVtNatureRange().front();//大值减小值
			if(LargeValue == temp.GetChoiceValue())//如果是大值
			{
				map<CString,vector<float>>::iterator itMap = m_mapAfterPreResult.find(it->GetNatureName());
				if (itMap != m_mapAfterPreResult.end())
				{
					vector<float> vtFloat = itMap->second;
					vector<float> vtResult;//存放计算结果
					UINT vectorNumber = vtFloat.size();
					for (UINT i=0; i<vectorNumber; i++)
					{
						vtResult.push_back((temp.GetVtNatureRange().back() - vtFloat.at(i))/diff);//减去大值  Di=( Ymax- Yi)/(Ymax-Ymin)
					}
					m_mapAfterPreResultDi.insert(make_pair(it->GetNatureName(), vtResult));
				}
			}
			else if (SmallVaule == temp.GetChoiceValue())//如果是小值
			{
				map<CString,vector<float>>::iterator itMap = m_mapAfterPreResult.find(it->GetNatureName());
				if (itMap != m_mapAfterPreResult.end())
				{
					vector<float> vtFloat = itMap->second;
					vector<float> vtResult;//存放计算结果
					UINT vectorNumber = vtFloat.size();
					for (UINT i=0; i<vectorNumber; i++)
					{
						vtResult.push_back((vtFloat.at(i) - temp.GetVtNatureRange().front())/diff);//减去小值 Di=(Yi-Ymin)/(Ymax-Ymin)
				}
					m_mapAfterPreResultDi.insert(make_pair(it->GetNatureName(), vtResult));
				}
			}
		}//Di计算完毕


		//二、计算综合得分
		UINT groupNumber = m_afterPreResult.size();//初选后的组数
		UINT k = groupNumber;//k值即为组数
		vector<float> comprehensiveScore(groupNumber, 1);//综合得分数组
		//计算方法为把得到的Di结果从头到尾遍历一遍，然后使用综合得分数组与每一个性质的数据相乘，最后再开k次方
		vector<CNature>::iterator itVt = m_vtNature.begin();
		vector<CNature>::iterator itVtEnd = m_vtNature.end();


		map<CString,vector<float>>::iterator itDiMapEnd = m_mapAfterPreResultDi.end();
		for (; itVt!=itVtEnd; ++itVt)
		{
			map<CString, vector<float>>::iterator itDiMap = m_mapAfterPreResult.find(itVt->GetNatureName());
			if (itDiMap != m_mapAfterPreResult.end())
			{
				vector<float> vtFloat = itDiMap->second;
				UINT size = vtFloat.size();
				for (UINT i=0; i<size; i++)
				{
					comprehensiveScore.at(i) = comprehensiveScore.at(i)*vtFloat.at(i);
				}
			}
		}
		//开k次放
		float squareValue = 1.0/k;
		for (UINT i=0; i<groupNumber; i++)
		{
			comprehensiveScore.at(i) = pow(comprehensiveScore.at(i), squareValue);
		}
		//三、计算T值
		//为了方便计算，把算出的综合得分放入，筛选过后的数组的最后一个  如 第一组为 7 1 3 6 1.3604312
		//															第二组为 7 1 4 5 1.3456212
		//																		...
		for (UINT i=0; i<groupNumber; i++)
		{
			m_afterPreResult.at(i).push_back(comprehensiveScore.at(i));
		}

		vector<float> finalResult;
		CalculateFinallyGroup(m_afterPreResult, finalResult);//计算最终的数组值，包括计算T值，筛选分组
		//算出最终数组后，再把综合得分取出
		groupNumber = m_afterPreResult.size();//初选后的组数
		for (UINT i=0; i<groupNumber; i++)
		{
			m_afterPreResult.at(i).erase(m_afterPreResult.at(i).begin() + m_vtComponent.size());//去掉综合得分
		}

		//四、性质反算
		//判断初选数组里是否存在最终算出的数组，有则返回索引值和true，没有则返回false
		vector<vector<float>>::iterator itVt2 = m_afterPreResult.begin();
		vector<vector<float>>::iterator itVt2End = m_afterPreResult.end();
		bool flag = false;
		int pos = 0;
		for (; itVt2!=itVt2End; ++itVt2, ++pos)
		{
			int count = 1;
			int compositionNumber = (*itVt2).size();
			for (int i=0; i<compositionNumber; i++)
			{
				if ((*itVt2).at(i) != finalResult.at(i))//只要有不相等的则退出循环，比较下一组
				{
					break;
				}
				else
				{
					count++;
					if (count == compositionNumber)//如果比较完所有的数据都相等，则返回true和索引
					{
						flag = true;
						vtResultIndex.clear();
						vtResultIndex.push_back(pos);
						return true;
					}
				}
			}
		}

		//五、返回结果
	}
	return false;

}


//计算最终的数组值，包括计算T值，筛选分组
void CNewCompositionOptimizationDlg::CalculateFinallyGroup(const vector<vector<float>> &m_preResult, vector<float> &ReturnResult)
{
	int compositionNumber = m_vtComponent.size();//组分个数
	vector<vector<float>> copyResult;
	for (int i = 0; i < compositionNumber; i++)
	{
		//计算第i个物质，如第1个为SiO2
		copyResult=m_preResult;
		vector<vector<float>>::iterator itVt2 = copyResult.begin();
		vector<vector<float>>::iterator itCompare;
		map<float,float> mapFloat2;
		mapFloat2.clear();
		for(; itVt2 != copyResult.end(); ++itVt2)
		{
			float compareValue = (*itVt2).at(i);
			itCompare = itVt2;
			int count = 1;
			float comprehensiveScore = (*itVt2).back();//综合得分
			++itCompare;
			while (itCompare != copyResult.end())
			{
				if (compareValue == (*itCompare).at(i))
				{
					count++;
					comprehensiveScore += (*itCompare).back();
					itCompare = copyResult.erase(itCompare);//把已经计算过的数据清理掉
				}
				else
				{
					++itCompare;
				}
			}
			comprehensiveScore = comprehensiveScore/count;//计算出综合得分
			mapFloat2.insert(make_pair(compareValue, comprehensiveScore));
		}
		//取出最大值对应的数据
		map<float, float>::iterator itMap = mapFloat2.begin();
		map<float, float>::iterator itMapEnd = mapFloat2.end();
		//先假设第一个值为最大值
		float maxKey = itMap->first;
		float maxValue = itMap->second;
		//然后与后面的值比较，取出
		++itMap;
		for (; itMap != itMapEnd; ++itMap)
		{
			if (itMap->second > maxValue)
			{
				maxKey = itMap->first;
				maxValue = itMap->second;
			}
		}
		//推入返回数组中
		ReturnResult.push_back(maxKey);
	}
}


void CNewCompositionOptimizationDlg::Display(vector<vector<float>> &result, map<CString, vector<float>> &mapResult, int resultIndex)
{
	int pos = 1;
	CString str;
	//vector<float> vtResult = result.at(resultIndex);
	vector<float> vtResult = m_vtComponentGroupingBefore.at(resultIndex);
	int iSize = vtResult.size();
	//T这里应该获取 每个性质未计算的截取值
	for (int i = 0; i < iSize; i++)
	{
		vtResult.at(i) = m_vtComponent.at(i).GetBeforeRangeValue(vtResult.at(i));
	}
	
	for (int i = 0; i < iSize; i++)
	{
		str.Format(_T("%g"), vtResult.at(i));
		m_ResultList.SetItemText(0, pos++, str);
	}
	//显示最优组分得到的结果
	int NSize = m_vtNature.size();
	for (int i = 0; i < NSize; i++)
	{
		map<CString, vector<float>>::iterator itMap = mapResult.find(m_vtNature.at(i).GetNatureName());
		if (itMap != mapResult.end())
		{
			vector<float> vtf = itMap->second;
			str.Format(_T("%g"), vtf.at(resultIndex));
			m_ResultList.SetItemText(0, pos++, str);
		}
	}
}


//计算数据清理，为下一次优选做准备
void CNewCompositionOptimizationDlg::ClearData(bool bClearAll/* =false */)
{
	m_vtComponentGrouping.clear();
	m_mapNatureResult.clear();
	m_afterPreResult.clear();
	m_mapAfterPreResult.clear();
	m_mapAfterPreResultDi.clear();
	if (bClearAll)
	{
		for (UINT i = IDC_CHECK_AL2O3; i < IDC_CHECK_ZrO2; i++)
		{
			if(((CButton*)GetDlgItem(i))->GetCheck())
			{
				((CButton*)GetDlgItem(i))->SetCheck(0);
			}
		}
		for (UINT i = IDC_CHECK_1_RPZXS; i < IDC_CHECK_31_RHWD; i++)
		{
			if(((CButton*)GetDlgItem(i))->GetCheck())
			{
				((CButton*)GetDlgItem(i))->SetCheck(0);
			}
		}
		m_vtComponent.clear();
		m_vtNature.clear();
		UpdateComponetList();
		UpdateNatureList();
	}
}

//开始进行优选
void CNewCompositionOptimizationDlg::OnBnClickedBtnStartOptimization()
{
	// TODO: 在此添加控件通知处理程序代码
	//T判断输入是否符合要求
	if (!JudgmentInput())
	{
		return;
	}
	//二、开始计算
	CalculateNature();

	//所有结果都计算出来了，并存放在了m_mapNatureResult中
	//三、筛选组成
	//3.1初步筛选
	vector<int> vt;//存储了符合要求的序号
	if (PreSelect(vt))//如果初步筛选成功，则显示结果并退出
	{
		if (1 == vt.size())
		{
			Display(m_vtComponentGrouping, m_mapNatureResult, vt.front());
			ClearData();
			MessageBox(_T("初选后成功找到！"),DlgTitle);
		}
		else if (vt.size()>1)//否则进行精选
		{
			//3.2精选结果
			//调用函数使初选结果存储在m_afterPreResult和m_mapAfterPreResult中
			//只有需要精选时才需要调用此函数
			ExtractPreResult(vt);

			if (AccuSelect(vt))
			{

				//显示最优的组分
				Display(m_afterPreResult, m_mapAfterPreResult, vt.front());
				ClearData();
				MessageBox(_T("精选后成功找到！"),DlgTitle);
			}
			else
			{
				ClearData();
				MessageBox(_T("精选后无结果！"),DlgTitle);	
			}
		}
	}
	else
	{
		ClearData();
		MessageBox(_T("初选后无结果！"),DlgTitle);
	}

	
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectComponent()
{
	// TODO: 在此添加控件通知处理程序代码
	//把打钩的复选框，写入组分表格中
	m_vtComponent.clear();
	bool rt = GetSelectCheckBox(_T("Component"));
	UpdateComponetList();
	if (rt)
	{
		/*把对话框设置到第一个*/
		NM_LISTVIEW* pNMListView = new NM_LISTVIEW;
		pNMListView->iItem = 0;
		pNMListView->iSubItem = 2;

		NMHDR *pNMHDR = reinterpret_cast<NMHDR*>(pNMListView);
		LRESULT pResult = 0;
		OnNMDblclkListComponent(pNMHDR,&pResult);
		delete pNMListView;
	}
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectNature()
{
	// TODO: 在此添加控件通知处理程序代码
	m_vtNature.clear();
	bool rt = GetSelectCheckBox(_T("Nature"));
	UpdateNatureList();
	if (rt)
	{
		/*把对话框设置到第一个*/
		NM_LISTVIEW* pNMListView = new NM_LISTVIEW;
		pNMListView->iItem = 0;
		pNMListView->iSubItem = 2;

		NMHDR *pNMHDR = reinterpret_cast<NMHDR*>(pNMListView);
		LRESULT pResult = 0;
		OnNMDblclkListNature(pNMHDR,&pResult);
		delete pNMListView;
	}
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
		m_ComponentList.GetSubItemRect(m_row, m_column, LVIR_LABEL, rc);//取得子项的矩形

		rc.bottom += 3;

		m_inputComEdit.SetParent(&m_ComponentList);
		PTSTR ch=new TCHAR[20];
		m_ComponentList.GetItemText(m_row, m_column, ch, 20);//取得子项的内容
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


void CNewCompositionOptimizationDlg::OnBnClickedBtnClear()
{
	// TODO: Add your control notification handler code here
	ClearData(true);
}


BOOL CNewCompositionOptimizationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch (pMsg->wParam)  
		{  
		case VK_TAB:  
	 
			CWnd *pWnd = GetFocus(); 
			if(pWnd == NULL)
				;//no focus
			else
			{
				UINT nID = pWnd->GetDlgCtrlID();
				SetFocus();
				if (IDC_EDIT1 == nID)//如果是组分表
				{
					NM_LISTVIEW* pNMListView = new NM_LISTVIEW;
					if (m_row+1 < m_vtComponent.size())
					{
						pNMListView->iItem = m_row+1;
					}
					pNMListView->iSubItem = 2;

					NMHDR *pNMHDR = reinterpret_cast<NMHDR*>(pNMListView);
					LRESULT pResult = 0;
					OnNMDblclkListComponent(pNMHDR,&pResult);
					delete pNMListView;
				}
				else if (IDC_EDIT2 == nID)//性质表
				{
					NM_LISTVIEW* pNMListView = new NM_LISTVIEW;
					if (m_row+1 < m_vtNature.size())
					{
						pNMListView->iItem = m_row+1;
					}
					pNMListView->iSubItem = 2;

					NMHDR *pNMHDR = reinterpret_cast<NMHDR*>(pNMListView);
					LRESULT pResult = 0;
					OnNMDblclkListNature(pNMHDR,&pResult);
					delete pNMListView;
				}
			}
			
			return TRUE;  
		}  
	}  
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CNewCompositionOptimizationDlg::OnBnClickedBinImport()
{
	// TODO: Add your control notification handler code here
	//清理数据
	ClearData(true);
	//T选择文件夹
	CString strFilter, fileName;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files|*.ini|*.ini||"), AfxGetMainWnd());//构造文件另存为对话框
	CString strPath;//声明变量
	if (dlg.DoModal() == IDOK)//判断是否按下"保存"按钮
	{
		strPath = dlg.GetPathName();//获得文件保存路径
		if (strPath == _T(""))
		{
			MessageBox(_T("请选择路径"),DlgTitle);
			return;
		}
	}
	//T读取数据
	vector<CString> vtRead;
	LoadVtStrFromIni(vtRead,_T("组分"),strPath);
	//T把数据添加到变量及表格中，复选框需要勾选
	//1.从配置文件中获取固定性质系数
	UINT iSize = vtRead.size();
	int a = 0;
	CString strName;
	CString strRange;
	CString strCompare;
	CComponent componet;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtRead.at(i).Find(',');
		strName = vtRead.at(i).Left(a);//1.取出逗号前的组分名
		strRange = vtRead.at(i).Right(vtRead.at(i).GetLength() - a - 1);//3.取出性质系数的值
		for (UINT i = IDC_CHECK_AL2O3; i < IDC_CHECK_ZrO2; i++)
		{
			GetDlgItem(i)->GetWindowText(strCompare);
			if(strName == strCompare)
			{
				((CButton*)GetDlgItem(i))->SetCheck(1);
			}
		}
		componet.SetComponentName(strName);
		componet.SetStrComponentRange(strRange);
		m_vtComponent.push_back(componet);
	}

	vtRead.clear();
	LoadVtStrFromIni(vtRead,_T("性质"),strPath);
	iSize = vtRead.size();
	CNature nature;
	map<CString, ChoiceValue>::iterator itMap;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtRead.at(i).Find(',');
		strName = vtRead.at(i).Left(a);//1.取出逗号前的组分名
		strRange = vtRead.at(i).Right(vtRead.at(i).GetLength() - a - 1);//3.取出性质系数的值
		for (UINT i = IDC_CHECK_1_RPZXS; i < IDC_CHECK_31_RHWD; i++)
		{
			GetDlgItem(i)->GetWindowText(strCompare);
			if(strName == strCompare)
			{
				((CButton*)GetDlgItem(i))->SetCheck(1);
			}
		}

		nature.SetNatureName(strName);
		nature.SetStrNatureRange(strRange);
		itMap = m_mapNatureChoiceValue.find(strName);
		if (itMap != m_mapNatureChoiceValue.end())
		{
			nature.SetNatureChoiceValue(itMap->second);
		}
		m_vtNature.push_back(nature);
	}
	UpdateComponetList();
	UpdateNatureList();
	//T标题显示为某某导入文件
	SetWindowText(_T("组分优选导入文件   ")+strPath);
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnExport()
{
	// TODO: Add your control notification handler code here
	//T1判断有无数据，没有,导出没有意义
	if (!JudgmentInput())
		return;
	//T2获取导出路径，文件名由用户取
	CString strFilter, fileName;
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files|*.ini|*.ini||"), AfxGetMainWnd());//构造文件另存为对话框
	CString strPath;//声明变量
	if (dlg.DoModal() == IDOK)//判断是否按下"保存"按钮
	{
		strPath = dlg.GetPathName();//获得文件保存路径
		if (strPath.Right(4) != ".ini")//判断文件扩展名
		{
			strPath += ".ini";//设置文件扩展名
		}
	}
	//T3导出数据
	//导出文件格式为 .ini  [组分]
	//						nCount=1
	//						1=Al2O3,1-2
	//						[性质]
	//						nCount=1
	//						1=热膨胀系数，20-30
	
	//T写入组分
	vector<CString> vtStrWrite;
	int CSize = m_vtComponent.size();
	for (int i = 0; i < CSize; i++)
	{
		vtStrWrite.push_back(m_vtComponent.at(i).GetComponentName()+_T(",")+m_vtComponent.at(i).GetStrComponentRange());
	}
	WriteStrToIni(vtStrWrite,_T("组分"),strPath);
	//T写入性质
	vtStrWrite.clear();
	int NSize = m_vtNature.size();
	for (int i = 0; i < NSize; i++)
	{
		vtStrWrite.push_back(m_vtNature.at(i).GetNatureName()+_T(",")+m_vtNature.at(i).GetStrNatureRange());
	}
	WriteStrToIni(vtStrWrite,_T("性质"),strPath);
	MessageBox(_T("导出成功！"),DlgTitle);
}
