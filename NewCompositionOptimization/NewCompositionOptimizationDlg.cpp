
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
	LoadNatureChoiceValue();
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
	m_NatureList.InsertColumn(1, _T("��    ��"), LVCFMT_CENTER, 120); 
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
	CString strCompositionName;
	CString strNatureName;
	CString strCoefficientValue;
	float CValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		b = vtCString.at(i).ReverseFind(',');
		strCompositionName = vtCString.at(i).Left(a);//1.ȡ������ǰ�������
		strNatureName = vtCString.at(i).Mid(a + 1, b - a - 1); //2.ȡ�����ź��������
		strCoefficientValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - b - 1);//3.ȡ������ϵ����ֵ
		CValue = _ttof(strCoefficientValue);

		NCC.CompositionName = strCompositionName;
		NCC.NatureName = strNatureName;
		NCC.CoefficientValue = CValue;
		m_vtFixedNatureCalcCoe.push_back(NCC);//T����������
	}

}

//T�������ʼ���ֵ�ͼ�Сֵ
void CNewCompositionOptimizationDlg::LoadNatureChoiceValue()
{
	//1.�������ļ��л�ȡ�̶�����ϵ��
	vector<CString> vtCString;
	LoadVtStrFromIni(vtCString, _T("����ȡ��ֵ"));
	UINT iSize = vtCString.size();
	int a = 0;
	CString strNatureName;
	CString strChoiceValue;
	ChoiceValue cv;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		strNatureName = vtCString.at(i).Left(a);//1.ȡ������ǰ�������
		strChoiceValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - a - 1);//3.ȡ������ϵ����ֵ
		if ("max" == strChoiceValue)
		{
			cv = LargeValue;
		}
		else if ("min" == strChoiceValue)
		{
			cv = SmallVaule;
		}
		m_mapNatureChoiceValue.insert(make_pair(strNatureName, cv));//T����ӳ����
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

//����������иĶ�ʱ�����øú���������ʾ
void CNewCompositionOptimizationDlg::UpDateComponetList()
{
	m_ComponentList.DeleteAllItems();
	//��һ�������ﵼ����Ҫ������������
	if (!m_vtComponent.empty())//������
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

//�����������иĶ�ʱ�����øú���������ʾ
void CNewCompositionOptimizationDlg::UpDateNatureList()
{
	m_NatureList.DeleteAllItems();
	//��һ�������ﵼ����Ҫ������������
	if (!m_vtNature.empty())//������
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

//���������������иĶ�ʱ�����øú���������ʾ����б�
void CNewCompositionOptimizationDlg::UpDateResultList()
{
	m_ResultList.DeleteAllItems();
	int pos = 1;
	if (!m_vtComponent.empty())//������
	{
		vector<CComponent>::iterator it = m_vtComponent.begin();
		vector<CComponent>::iterator itEnd = m_vtComponent.end();

		for (; it != itEnd; ++it, ++pos)
		{
			m_ResultList.InsertColumn(pos, it->GetComponentName(), LVCFMT_CENTER, 80);
		}
	}

	if (!m_vtNature.empty())//������
	{
		vector<CNature>::iterator it = m_vtNature.begin();
		vector<CNature>::iterator itEnd = m_vtNature.end();
		for (; it != itEnd; ++it, ++pos)
		{
			m_ResultList.InsertColumn(pos, it->GetNatureName(), LVCFMT_CENTER, 80); 
		}
	}
	m_ResultList.InsertItem(1, _T("��ѡ���"));
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

//T��ȡѡ��ĸ�ѡ�򣬴���ΪComponent��ȡ��֣�����ΪNature��ȡ����
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
		if (((CButton*)GetDlgItem(i))->GetCheck())//�жϸ�ѡ���Ƿ�ѡ��
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
				//�������ļ��л�ȡ�ļ���ֵ��Сֵ
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
	//T1���Ȱ���ֽض�����������
	CombinationTruncationData();

	//T2�����������ÿ����ֵĺ�������ȡ��ͬ���ʵļ���ϵ��


	//T3���������ȥ��ϵ������ֺ�������������





	
	//�������


	//����������ÿһ���Ӧ������ϵ��ֵ�������ʡ��������������˳������
	//	vector<CNature>::iterator vtCString = m_vtNature.begin();
	//	vector<CNature>::iterator vtCStringEnd = m_vtNature.end();
	//	for (; vtCString!=vtCStringEnd; ++vtCString)
	//	{
	//		//����������ÿһ���Ӧ������ϵ��ֵ�������ʡ��������������˳������
	//		map<int,map<CString,float>>::iterator itMap2;
	//		//����ϵ��
	//		vector<float> vtNature;//��ȡ�����ʶ�Ӧ������ϵ��
	//		//size��СΪm_vtComposition.size();
	//		for (int i=0; i<typeNumber; i++)
	//		{
	//			itMap2 = m_mapAllNature.find(i);//�Ҹ��������� SiO2 Al2O3..
	//			if (itMap2 != m_mapAllNature.end())//����ҵ���
	//			{
	//				map<CString,float>::iterator map3 = itMap2->second.find(*vtCString);
	//				if (map3 != itMap2->second.end())//����ҵ���
	//				{
	//					vtNature.push_back(map3->second);
	//				}
	//			}	
	//		}
	//		int times = m_subResult.size();//�ж��ٷ��飬ѭ�����ٴ�
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


//index Ϊ��Ҫ����������еĵڼ���ֵ 
void CNewCompositionOptimizationDlg::Calculate(const int index, vector<float> &vtSub)
{
	if (index < m_vtComponent.size())//�����ⲻ�����һ��
	{
		//it--;//��ȥ�ж�ʱ�ӵ�1
		vector<float> vt = m_vtComponent.at(index).GetVtComponentRange();
		int subSize = vt.size();
		for (int i = 0; i < subSize; i++)
		{
			vtSub.at(index) = vt.at(i);
			Calculate(index+1, vtSub);
		}
	}
	else//�����һ��
	{
		m_vtComponentGrouping.push_back(vtSub);
	}

}

//T��Ͻض��������
void CNewCompositionOptimizationDlg::CombinationTruncationData()
{
	vector<float> vtSub;
	int typeNumber = m_vtComponent.size();//�ж���������
	for (int i=0; i<typeNumber; i++)
	{
		vtSub.push_back(-1);
	}
	//���õݹ麯��ʵ��ѭ����ʵ�ַ���
	//�������ݴ�ŵ���vector<vector<float>> m_subResult��
	//0�� 1 3 5 7
	//1�� 1 3 5 8
	//2�� 1 3 6 7
	//   ...
	vector<float> vt = m_vtComponent.at(0).GetVtComponentRange();
	int subSize = vt.size();
	for (int i = 0; i < subSize; i++)
	{
		vtSub.at(0) = vt.at(i);
		Calculate(1, vtSub);
	}
	

	for (int i = 0; i < typeNumber; i++)//������ѭ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bIsSelectComponent && m_bIsSelectNature)
	{
		//�������б�û�����ݣ����˳�
		if (m_vtComponent.empty())
		{
			MessageBox(_T("û��������֣�"));
			return;
		}
		if (m_vtNature.empty())
		{
			MessageBox(_T("û���������ʣ�"));
			return;
		}
		//�����������б�
		UpDateResultList();
		//������ʼ����
		CalculateNature();
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
	m_vtComponent.clear();
	m_bIsSelectComponent = GetSelectCheckBox(_T("Component"));
	UpDateComponetList();
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectNature()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_vtNature.clear();
	m_bIsSelectNature = GetSelectCheckBox(_T("Nature"));
	UpDateNatureList();
}


void CNewCompositionOptimizationDlg::OnNMDblclkListComponent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem != -1 && 2 == pNMListView->iSubItem)
	{
		m_row = pNMListView->iItem;							//m_rowΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_column = pNMListView->iSubItem;						//m_columnΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_ComponentList.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem, LVIR_LABEL, rc);//ȡ������ľ���

		rc.bottom += 3;

		m_inputComEdit.SetParent(&m_ComponentList);
		PTSTR ch=new TCHAR[20];
		m_ComponentList.GetItemText(pNMListView->iItem, pNMListView->iSubItem, ch, 20);//ȡ�����������
		m_inputComEdit.SetWindowText(ch);					//�������������ʾ���༭����
		m_inputComEdit.ShowWindow(SW_SHOW);					//��ʾ�༭��
		m_inputComEdit.MoveWindow(&rc);						//���༭���ƶ����������棬������������
		m_inputComEdit.SetFocus();							//ʹ�༭��ȡ�ý���
		m_inputComEdit.CreateSolidCaret(1, rc.Height() - 5);//����һ�����
		m_inputComEdit.ShowCaret();							//��ʾ���
		m_inputComEdit.SetSel(-1);							//ʹ����Ƶ������
		delete ch;
	}
	*pResult = 0;
}


void CNewCompositionOptimizationDlg::OnEnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_inputComEdit.GetWindowText(str);//ȡ�ñ༭�������
	m_ComponentList.SetItemText(m_row, m_column, str);//�������ݸ��µ�CListCtrl��
	//T���ַ������õ����������,�����ڲ������ַ��������洢����Χ������
	m_vtComponent.at(m_row).SetStrComponentRange(str);
	m_inputComEdit.ShowWindow(SW_HIDE);//���ر༭��
}


void CNewCompositionOptimizationDlg::OnNMDblclkListNature(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem != -1 && pNMListView->iSubItem == 2)
	{
		m_row = pNMListView->iItem;								//m_rowΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_column = pNMListView->iSubItem;							//m_columnΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_NatureList.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem, LVIR_LABEL, rc);//ȡ������ľ���

		rc.bottom += 3;

		m_inputNatureEdit.SetParent(&m_NatureList);
		PTSTR ch = new TCHAR[20];
		m_NatureList.GetItemText(pNMListView->iItem, pNMListView->iSubItem, ch, 20);//ȡ�����������
		m_inputNatureEdit.SetWindowText(ch);					//�������������ʾ���༭����
		m_inputNatureEdit.ShowWindow(SW_SHOW);					//��ʾ�༭��
		m_inputNatureEdit.MoveWindow(&rc);						//���༭���ƶ����������棬������������
		m_inputNatureEdit.SetFocus();							//ʹ�༭��ȡ�ý���
		m_inputNatureEdit.CreateSolidCaret(1, rc.Height() - 5);	//����һ�����
		m_inputNatureEdit.ShowCaret();							//��ʾ���
		m_inputNatureEdit.SetSel(-1);							//ʹ����Ƶ������
	}
	*pResult = 0;
}


void CNewCompositionOptimizationDlg::OnEnKillfocusEdit2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ж������Ƿ����Ҫ�󣨺�������
	CString str;
	m_inputNatureEdit.GetWindowText(str);//ȡ�ñ༭�������
	m_NatureList.SetItemText(m_row, m_column, str);//�������ݸ��µ�CListCtrl��
	//T���ַ������õ�����������,�����ڲ������ַ��������洢����Χ������
	m_vtNature.at(m_row).SetStrNatureRange(str);
	m_inputNatureEdit.ShowWindow(SW_HIDE);//���ر༭��
}
