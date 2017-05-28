
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
	LoadComponentFixedValue();
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
	CString strComponentName;
	CString strNatureName;
	CString strCoefficientValue;
	float CValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		b = vtCString.at(i).ReverseFind(',');
		strComponentName = vtCString.at(i).Left(a);//1.ȡ������ǰ�������
		strNatureName = vtCString.at(i).Mid(a + 1, b - a - 1); //2.ȡ�����ź��������
		strCoefficientValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - b - 1);//3.ȡ������ϵ����ֵ
		CValue = _ttof(strCoefficientValue);

		NCC.ComponentName = strComponentName;
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

//T�������ļ��л�ȡ��ֽ�ȡֵ���Ĺ̶�ϵ��
void CNewCompositionOptimizationDlg::LoadComponentFixedValue()
{
	//1.�������ļ��л�ȡ�̶�����ϵ��
	map<CString, float> mapFixedValue;
	vector<CString> vtCString;
	LoadVtStrFromIni(vtCString, _T("��̶ֹ�ϵ��"));
	UINT iSize = vtCString.size();
	int a = 0;
	CString strNatureName;
	CString strFixedValue;
	float fixedValue;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtCString.at(i).Find(',');
		strNatureName = vtCString.at(i).Left(a);//1.ȡ������ǰ�������
		strFixedValue = vtCString.at(i).Right(vtCString.at(i).GetLength() - a - 1);//2.ȡ���̶�ϵ����ֵ
		fixedValue = _ttof(strFixedValue);
		mapFixedValue.insert(make_pair(strNatureName, fixedValue));//T����ӳ����
	}
	CComponent::SetComponentFixedValue(mapFixedValue);//T��ֵ�������
}

//�������ļ��л�ȡ�ַ�������
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
		MessageBox(_T("��ȡ�����ļ��е�")+keyStr+_T("ʧ��,���������ļ���"),DlgTitle);
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


//д���ݵ������ļ���WritePrivateProfileString
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


//����������иĶ�ʱ�����øú���������ʾ
void CNewCompositionOptimizationDlg::UpdateComponetList()
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
	UpdateResultList();
}

//�����������иĶ�ʱ�����øú���������ʾ
void CNewCompositionOptimizationDlg::UpdateNatureList()
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
	UpdateResultList();
}

//���������������иĶ�ʱ�����øú���������ʾ����б�
void CNewCompositionOptimizationDlg::UpdateResultList()
{
	m_ResultList.DeleteAllItems();
	int nColumnCount = m_ResultList.GetHeaderCtrl()->GetItemCount();
	for (int i = 0;i < nColumnCount; i++)
	{
		m_ResultList.DeleteColumn(0);
	}
	m_ResultList.InsertColumn(0, _T("��ּ�����"), LVCFMT_CENTER, 80); 
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
	float coeValue ;
	bool rt = GetFixedNatureCalcCoe(cName, nName, cValue, coeValue);
	//T2�����ü��㹫ʽ������ϵ��
	if (!rt)//T����̶�ֵ��û�У���ʹ�ù�ʽ����
	{
		coeValue = GetNatureCalcCoeWithFormula(cName, nName, cValue);
		coeValue = 1;
	}
	return coeValue;
}

//T�ӹ̶�ֵ�л�ȡϵ�������У��򷵻�true,ֵ����rtValue�У������򷵻�false
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

//Tʹ�ù�ʽ��������ϵ��
float CNewCompositionOptimizationDlg::GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue)
{
	//�˴�ֻд��SiO2�������ʼ���
	if ("SiO2" == cName && "������" == nName)
	{
		return 1.475-0.0005*(cValue-67);//	SiO2��������ϵ��=1.475-0.0005*��SiO2����ֺ���-67��
	}
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

	for(int i = iStartID; i <= iEndID; i++)
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

//�ж������Ƿ������ѡҪ��
bool CNewCompositionOptimizationDlg::JudgmentInput()
{
	//�������б�û�����ݣ����˳�///T���뷶Χֵʱ�Ƿ�����ж�����Ϸ�
	CString str;
	if (m_vtComponent.empty())
	{
		MessageBox(_T("û��������֣�"),DlgTitle);
		return false;
	}
	else//�жϷ����뷶Χֵ
	{
		int iSize = m_vtComponent.size();
		for (int i = 0; i < iSize; i++)
		{
			if ("" == m_vtComponent.at(i).GetStrComponentRange())
			{
				
				MessageBox(_T("���������\"")+m_vtComponent.at(i).GetComponentName()+_T("\"�ķ�Χ!"),DlgTitle);
				return false;
			}
		}
	}
	if (m_vtNature.empty())
	{
		MessageBox(_T("û���������ʣ�"),DlgTitle);
		return false;
	}
	else//�жϷ����뷶Χֵ
	{
		int iSize = m_vtNature.size();
		for (int i = 0; i < iSize; i++)
		{
			if ("" == m_vtNature.at(i).GetStrNatureRange())
			{

				MessageBox(_T("����������\"")+m_vtNature.at(i).GetNatureName()+_T("\"�ķ�Χ!"),DlgTitle);
				return false;
			}
		}
	}
}


void CNewCompositionOptimizationDlg::CalculateNature()
{
	//T1���Ȱ���ֽض�����������
	CombinationTruncationData();

	//T2���ڶ�������Ͳ������Ҫʹ�õİٷֱ�
	CalculateComponentPercentage();

	//T3�����������ÿ����ֵĺ�������ȡ��ͬ���ʵļ���ϵ��,�����������������m_mapNatureResult��
	CalculateEachGroupNature();
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
		m_vtComponentGroupingBefore.push_back(vtSub);
	}
	
}

//T��Ͻض��������
void CNewCompositionOptimizationDlg::CombinationTruncationData()
{
	m_vtComponentGroupingBefore.clear();//������һ������
	m_vtComponentGrouping.clear();
	int typeNumber = m_vtComponent.size();//�ж���������
	vector<float> vtSub(typeNumber);
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
	m_vtComponentGrouping = m_vtComponentGroupingBefore;
}

//T��Ͳ��������ְٷֱ�
void CNewCompositionOptimizationDlg::CalculateComponentPercentage()
{
	int iSize = m_vtComponentGrouping.size();
	int subSize = -1;
	float sumValue = 0;
	vector<float> vtGroup;//Tÿһ�����
	for (int i = 0; i < iSize; i++)
	{
		sumValue = 0;
		subSize = m_vtComponentGrouping.at(i).size();
		//T��i��ĺ�
		for (int j = 0; j < subSize; j++)
		{
			sumValue += m_vtComponentGrouping.at(i).at(j);
		}
		//T��i��İٷֱ�
		for (int j = 0; j < subSize; j++)
		{
			//m_vtComponentGrouping.at(i).at(j) /= (sumValue * 100);
			m_vtComponentGrouping.at(i).at(j) = (m_vtComponentGrouping.at(i).at(j)/sumValue) * 100;
		}
	}
}


//T����ÿһ���Ӧ������
void CNewCompositionOptimizationDlg::CalculateEachGroupNature()
{
	int groupSize = m_vtComponentGrouping.size();//T������
	vector<float> vtResult(groupSize);//��СΪm_vtComponentGrouping�Ĵ�С
	int NSize = m_vtNature.size();
	vector<float> vtTemp;
	int tempSize;
	float resultValue = 0;
	for (int i = 0; i < NSize; i++)
	{
		
		for (int j = 0; j < groupSize; j++)
		{
			//��ýضϷ����ֵ������ֵĺ���
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


//�ɹ���û���ҵ�����false ��һ���������Ϸ���true
bool CNewCompositionOptimizationDlg::PreSelect(vector<int> &vtResultIndex)
{
	int size = m_vtComponentGrouping.size();
	vtResultIndex.clear();
	for (int i=0; i<size; i++)
	{
		vtResultIndex.push_back(i);//��¼������ţ��������������£�������������ɾ��
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
				fValue = vtTempResult.at(vtResultIndex.at(i));//ȡ����Ӧ��ֵ
				if(!(fValue >= m_vtNature.at(nIndex).GetVtNatureRange().front() && fValue <= m_vtNature.at(nIndex).GetVtNatureRange().back()))//������Ҫ��
				{
					//vtResultIndex�еĲ�����Ҫ���������ֵΪ-1
					vtResultIndex.at(i) = -1;
				}
			}
		}

		//T���Ϊ-1������ֵ
		itVt = vtResultIndex.begin();
		for (int i = vtResultIndex.size()-1; i >= 0; i--)
		{
			if (-1 == vtResultIndex.at(i))
			{
				vtResultIndex.erase(itVt + i);
			}
		}

	}

	//�������Ҫ������Ϊ0�����ؼ٣����������ݶ���ɾ����
	if (0 == vtResultIndex.size())
	{
		return false;
	}
	return true;
}


//��ȡ��ѡ���
void CNewCompositionOptimizationDlg::ExtractPreResult(vector<int> vtResultIndex)
{
	//�Ȱ���Ҫ���о�ѡ������ȡ��������m_afterPreResult��m_mapAfterPreResult��
	//��ȡ����ϵ�����

	vector<int>::iterator it = vtResultIndex.begin();
	vector<int>::iterator itEnd = vtResultIndex.end();
	vector<float> vtFloat;
	for (; it!=itEnd; ++it)
	{
		vtFloat.clear();

		vtFloat = m_vtComponentGrouping.at(*it);
		m_afterPreResult.push_back(vtFloat);
	}
	//��ȡ�����ݼ�����Ľ��
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

//��ѡ
bool CNewCompositionOptimizationDlg::AccuSelect(vector<int> &vtResultIndex)
{

	//��ѡ����洢��m_afterPreResult��m_mapAfterPreResult��

	//���ֻ��һ����Ҫ�Ƚϵ����ʣ���ѡ����ӽ����ʵ�һ�鲢����
	if (1 == m_vtNature.size())
	{
		int index = 0;//��¼�ǵڼ���Ϊ��ֵ����
		vector<float> vt = m_mapAfterPreResult.begin()->second;//��Ϊֻ��һ�����ʣ�����ֱ��ȡ��һ��
		//ChoiceValue cv;
		//cv = m_vtNature.at(0).GetChoiceValue();
		if(LargeValue == m_vtNature.at(0).GetChoiceValue())//���������ȡ��ֵ
		{
			//���������������ʽ�������������ҳ����ֵ����
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
		else if (SmallVaule == m_vtNature.at(0).GetChoiceValue())//���������ȡСֵ
		{
			//���������������ʽ�������������ҳ���Сֵ����
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
		return true;//�����ҵ���ĳһ�����ݵ���������
	}
	//��������������ϵıȽ����ʣ���ʹ��������
	else if (m_vtNature.size() > 1)
	{
		//һ������Diֵ
		vector<CNature>::iterator it = m_vtNature.begin();
		vector<CNature>::iterator itEnd = m_vtNature.end();
		int index = 0;//vector�е�����
		CNature temp;
		for (; it!=itEnd; ++it, ++index)
		{
			temp = m_vtNature.at(index);
			float diff = temp.GetVtNatureRange().back() - temp.GetVtNatureRange().front();//��ֵ��Сֵ
			if(LargeValue == temp.GetChoiceValue())//����Ǵ�ֵ
			{
				map<CString,vector<float>>::iterator itMap = m_mapAfterPreResult.find(it->GetNatureName());
				if (itMap != m_mapAfterPreResult.end())
				{
					vector<float> vtFloat = itMap->second;
					vector<float> vtResult;//��ż�����
					UINT vectorNumber = vtFloat.size();
					for (UINT i=0; i<vectorNumber; i++)
					{
						vtResult.push_back((temp.GetVtNatureRange().back() - vtFloat.at(i))/diff);//��ȥ��ֵ  Di=( Ymax- Yi)/(Ymax-Ymin)
					}
					m_mapAfterPreResultDi.insert(make_pair(it->GetNatureName(), vtResult));
				}
			}
			else if (SmallVaule == temp.GetChoiceValue())//�����Сֵ
			{
				map<CString,vector<float>>::iterator itMap = m_mapAfterPreResult.find(it->GetNatureName());
				if (itMap != m_mapAfterPreResult.end())
				{
					vector<float> vtFloat = itMap->second;
					vector<float> vtResult;//��ż�����
					UINT vectorNumber = vtFloat.size();
					for (UINT i=0; i<vectorNumber; i++)
					{
						vtResult.push_back((vtFloat.at(i) - temp.GetVtNatureRange().front())/diff);//��ȥСֵ Di=(Yi-Ymin)/(Ymax-Ymin)
				}
					m_mapAfterPreResultDi.insert(make_pair(it->GetNatureName(), vtResult));
				}
			}
		}//Di�������


		//���������ۺϵ÷�
		UINT groupNumber = m_afterPreResult.size();//��ѡ�������
		UINT k = groupNumber;//kֵ��Ϊ����
		vector<float> comprehensiveScore(groupNumber, 1);//�ۺϵ÷�����
		//���㷽��Ϊ�ѵõ���Di�����ͷ��β����һ�飬Ȼ��ʹ���ۺϵ÷�������ÿһ�����ʵ�������ˣ�����ٿ�k�η�
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
		//��k�η�
		float squareValue = 1.0/k;
		for (UINT i=0; i<groupNumber; i++)
		{
			comprehensiveScore.at(i) = pow(comprehensiveScore.at(i), squareValue);
		}
		//��������Tֵ
		//Ϊ�˷�����㣬��������ۺϵ÷ַ��룬ɸѡ�������������һ��  �� ��һ��Ϊ 7 1 3 6 1.3604312
		//															�ڶ���Ϊ 7 1 4 5 1.3456212
		//																		...
		for (UINT i=0; i<groupNumber; i++)
		{
			m_afterPreResult.at(i).push_back(comprehensiveScore.at(i));
		}

		vector<float> finalResult;
		CalculateFinallyGroup(m_afterPreResult, finalResult);//�������յ�����ֵ����������Tֵ��ɸѡ����
		//�������������ٰ��ۺϵ÷�ȡ��
		groupNumber = m_afterPreResult.size();//��ѡ�������
		for (UINT i=0; i<groupNumber; i++)
		{
			m_afterPreResult.at(i).erase(m_afterPreResult.at(i).begin() + m_vtComponent.size());//ȥ���ۺϵ÷�
		}

		//�ġ����ʷ���
		//�жϳ�ѡ�������Ƿ����������������飬���򷵻�����ֵ��true��û���򷵻�false
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
				if ((*itVt2).at(i) != finalResult.at(i))//ֻҪ�в���ȵ����˳�ѭ�����Ƚ���һ��
				{
					break;
				}
				else
				{
					count++;
					if (count == compositionNumber)//����Ƚ������е����ݶ���ȣ��򷵻�true������
					{
						flag = true;
						vtResultIndex.clear();
						vtResultIndex.push_back(pos);
						return true;
					}
				}
			}
		}

		//�塢���ؽ��
	}
	return false;

}


//�������յ�����ֵ����������Tֵ��ɸѡ����
void CNewCompositionOptimizationDlg::CalculateFinallyGroup(const vector<vector<float>> &m_preResult, vector<float> &ReturnResult)
{
	int compositionNumber = m_vtComponent.size();//��ָ���
	vector<vector<float>> copyResult;
	for (int i = 0; i < compositionNumber; i++)
	{
		//�����i�����ʣ����1��ΪSiO2
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
			float comprehensiveScore = (*itVt2).back();//�ۺϵ÷�
			++itCompare;
			while (itCompare != copyResult.end())
			{
				if (compareValue == (*itCompare).at(i))
				{
					count++;
					comprehensiveScore += (*itCompare).back();
					itCompare = copyResult.erase(itCompare);//���Ѿ�����������������
				}
				else
				{
					++itCompare;
				}
			}
			comprehensiveScore = comprehensiveScore/count;//������ۺϵ÷�
			mapFloat2.insert(make_pair(compareValue, comprehensiveScore));
		}
		//ȡ�����ֵ��Ӧ������
		map<float, float>::iterator itMap = mapFloat2.begin();
		map<float, float>::iterator itMapEnd = mapFloat2.end();
		//�ȼ����һ��ֵΪ���ֵ
		float maxKey = itMap->first;
		float maxValue = itMap->second;
		//Ȼ��������ֵ�Ƚϣ�ȡ��
		++itMap;
		for (; itMap != itMapEnd; ++itMap)
		{
			if (itMap->second > maxValue)
			{
				maxKey = itMap->first;
				maxValue = itMap->second;
			}
		}
		//���뷵��������
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
	//T����Ӧ�û�ȡ ÿ������δ����Ľ�ȡֵ
	for (int i = 0; i < iSize; i++)
	{
		vtResult.at(i) = m_vtComponent.at(i).GetBeforeRangeValue(vtResult.at(i));
	}
	
	for (int i = 0; i < iSize; i++)
	{
		str.Format(_T("%g"), vtResult.at(i));
		m_ResultList.SetItemText(0, pos++, str);
	}
	//��ʾ������ֵõ��Ľ��
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


//������������Ϊ��һ����ѡ��׼��
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

//��ʼ������ѡ
void CNewCompositionOptimizationDlg::OnBnClickedBtnStartOptimization()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//T�ж������Ƿ����Ҫ��
	if (!JudgmentInput())
	{
		return;
	}
	//������ʼ����
	CalculateNature();

	//���н������������ˣ����������m_mapNatureResult��
	//����ɸѡ���
	//3.1����ɸѡ
	vector<int> vt;//�洢�˷���Ҫ������
	if (PreSelect(vt))//�������ɸѡ�ɹ�������ʾ������˳�
	{
		if (1 == vt.size())
		{
			Display(m_vtComponentGrouping, m_mapNatureResult, vt.front());
			ClearData();
			MessageBox(_T("��ѡ��ɹ��ҵ���"),DlgTitle);
		}
		else if (vt.size()>1)//������о�ѡ
		{
			//3.2��ѡ���
			//���ú���ʹ��ѡ����洢��m_afterPreResult��m_mapAfterPreResult��
			//ֻ����Ҫ��ѡʱ����Ҫ���ô˺���
			ExtractPreResult(vt);

			if (AccuSelect(vt))
			{

				//��ʾ���ŵ����
				Display(m_afterPreResult, m_mapAfterPreResult, vt.front());
				ClearData();
				MessageBox(_T("��ѡ��ɹ��ҵ���"),DlgTitle);
			}
			else
			{
				ClearData();
				MessageBox(_T("��ѡ���޽����"),DlgTitle);	
			}
		}
	}
	else
	{
		ClearData();
		MessageBox(_T("��ѡ���޽����"),DlgTitle);
	}

	
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnSelectComponent()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�Ѵ򹳵ĸ�ѡ��д����ֱ����
	m_vtComponent.clear();
	bool rt = GetSelectCheckBox(_T("Component"));
	UpdateComponetList();
	if (rt)
	{
		/*�ѶԻ������õ���һ��*/
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_vtNature.clear();
	bool rt = GetSelectCheckBox(_T("Nature"));
	UpdateNatureList();
	if (rt)
	{
		/*�ѶԻ������õ���һ��*/
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem != -1 && 2 == pNMListView->iSubItem)
	{
		m_row = pNMListView->iItem;							//m_rowΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_column = pNMListView->iSubItem;						//m_columnΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_ComponentList.GetSubItemRect(m_row, m_column, LVIR_LABEL, rc);//ȡ������ľ���

		rc.bottom += 3;

		m_inputComEdit.SetParent(&m_ComponentList);
		PTSTR ch=new TCHAR[20];
		m_ComponentList.GetItemText(m_row, m_column, ch, 20);//ȡ�����������
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
				if (IDC_EDIT1 == nID)//�������ֱ�
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
				else if (IDC_EDIT2 == nID)//���ʱ�
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
	//��������
	ClearData(true);
	//Tѡ���ļ���
	CString strFilter, fileName;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files|*.ini|*.ini||"), AfxGetMainWnd());//�����ļ����Ϊ�Ի���
	CString strPath;//��������
	if (dlg.DoModal() == IDOK)//�ж��Ƿ���"����"��ť
	{
		strPath = dlg.GetPathName();//����ļ�����·��
		if (strPath == _T(""))
		{
			MessageBox(_T("��ѡ��·��"),DlgTitle);
			return;
		}
	}
	//T��ȡ����
	vector<CString> vtRead;
	LoadVtStrFromIni(vtRead,_T("���"),strPath);
	//T��������ӵ�����������У���ѡ����Ҫ��ѡ
	//1.�������ļ��л�ȡ�̶�����ϵ��
	UINT iSize = vtRead.size();
	int a = 0;
	CString strName;
	CString strRange;
	CString strCompare;
	CComponent componet;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtRead.at(i).Find(',');
		strName = vtRead.at(i).Left(a);//1.ȡ������ǰ�������
		strRange = vtRead.at(i).Right(vtRead.at(i).GetLength() - a - 1);//3.ȡ������ϵ����ֵ
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
	LoadVtStrFromIni(vtRead,_T("����"),strPath);
	iSize = vtRead.size();
	CNature nature;
	map<CString, ChoiceValue>::iterator itMap;
	for (UINT i = 0; i < iSize; i++)
	{
		a = vtRead.at(i).Find(',');
		strName = vtRead.at(i).Left(a);//1.ȡ������ǰ�������
		strRange = vtRead.at(i).Right(vtRead.at(i).GetLength() - a - 1);//3.ȡ������ϵ����ֵ
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
	//T������ʾΪĳĳ�����ļ�
	SetWindowText(_T("�����ѡ�����ļ�   ")+strPath);
}


void CNewCompositionOptimizationDlg::OnBnClickedBtnExport()
{
	// TODO: Add your control notification handler code here
	//T1�ж��������ݣ�û��,����û������
	if (!JudgmentInput())
		return;
	//T2��ȡ����·�����ļ������û�ȡ
	CString strFilter, fileName;
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files|*.ini|*.ini||"), AfxGetMainWnd());//�����ļ����Ϊ�Ի���
	CString strPath;//��������
	if (dlg.DoModal() == IDOK)//�ж��Ƿ���"����"��ť
	{
		strPath = dlg.GetPathName();//����ļ�����·��
		if (strPath.Right(4) != ".ini")//�ж��ļ���չ��
		{
			strPath += ".ini";//�����ļ���չ��
		}
	}
	//T3��������
	//�����ļ���ʽΪ .ini  [���]
	//						nCount=1
	//						1=Al2O3,1-2
	//						[����]
	//						nCount=1
	//						1=������ϵ����20-30
	
	//Tд�����
	vector<CString> vtStrWrite;
	int CSize = m_vtComponent.size();
	for (int i = 0; i < CSize; i++)
	{
		vtStrWrite.push_back(m_vtComponent.at(i).GetComponentName()+_T(",")+m_vtComponent.at(i).GetStrComponentRange());
	}
	WriteStrToIni(vtStrWrite,_T("���"),strPath);
	//Tд������
	vtStrWrite.clear();
	int NSize = m_vtNature.size();
	for (int i = 0; i < NSize; i++)
	{
		vtStrWrite.push_back(m_vtNature.at(i).GetNatureName()+_T(",")+m_vtNature.at(i).GetStrNatureRange());
	}
	WriteStrToIni(vtStrWrite,_T("����"),strPath);
	MessageBox(_T("�����ɹ���"),DlgTitle);
}
