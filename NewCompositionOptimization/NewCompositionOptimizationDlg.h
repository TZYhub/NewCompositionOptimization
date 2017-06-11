
// NewCompositionOptimizationDlg.h : ͷ�ļ�
//
#include "Component.h"
#include "Nature.h"
#include "NatureDlg.h"
#include "ComponentDlg.h"
#pragma once


// CNewCompositionOptimizationDlg �Ի���
class CNewCompositionOptimizationDlg : public CDialogEx
{
// ����
public:
	CNewCompositionOptimizationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NEWCOMPOSITIONOPTIMIZATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//T�����ѡ��ť
	afx_msg void OnBnClickedBtnStartOptimization();
	afx_msg void OnBnClickedBtnSelectComponent();
	afx_msg void OnBnClickedBtnSelectNature();
	afx_msg void OnNMDblclkListComponent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnNMDblclkListNature(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBinImport();
	afx_msg void OnBnClickedBtnExport();
	DECLARE_MESSAGE_MAP()


	void Init();										//���г�ʼ��
	void AutoSizeListColumn(CListCtrl &clist,int column);//T�Զ������б�ĳ�п��
	void InitCompositionList();							//��ʼ������б�
	void InitNatureList();								//��ʼ�������б�
	void InitResultList();								//��ʼ������б�
	void LoadFixeCalcCoe();								//T���ع̶�����ϵ��
	void LoadNatureChoiceValue();						//T�������ʼ���ֵ�ͼ�Сֵ
	void LoadComponentFixedValue();						//T�������ļ��л�ȡ��ֽ�ȡֵ���Ĺ̶�ϵ��
	void LoadVtStrFromIni(vector<CString> &vtStr,const CString& keyStr, const CString& strPath = _T(""));	//�������ļ��л�ȡ�ַ�������
	void WriteStrToIni(const vector<CString>& vtStr, const CString& keyStr, const CString& strPath);//д���ݵ������ļ���

	void UpdateComponetList();							//����������иĶ�ʱ�����øú���������ʾ
	void UpdateNatureList();							//�����������иĶ�ʱ�����øú���������ʾ
	void UpdateResultList();							//���������������иĶ�ʱ�����øú���������ʾ����б�


	//T��ȡ���ʼ���ϵ��,�����̶�ֵ�Ͳ��̶�ֵ��,ÿ�μ���ǰ�������ô˺������Ի�ȡ��Ӧϵ��
	float GetNatureCalcCoefficient(const CString& cName, const CString nName,const float cValue);
	//T�ӹ̶�ֵ�л�ȡϵ�������У��򷵻�true,ֵ����rtValue�У������򷵻�false
	bool GetFixedNatureCalcCoe(const CString& cName, const CString& nName, const float cValue, float& rtValue);
	//Tʹ�ù�ʽ��������ϵ��
	float GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue);

	BOOL GetSelectCheckBox(const CString& str, const vector<CString>& vtStr);			//T��ȡѡ��ĸ�ѡ�򣬴���Ϊ"Component"��ȡ��֣�����Ϊ"Nature"��ȡ����

	bool JudgmentInput();								//�ж������Ƿ������ѡҪ��

	void CalculateNature();
	void CombinationTruncationData();					//T��Ͻض��������
	void CalculateComponentPercentage();				//T��Ͳ��������ְٷֱ�
	void CalculateEachGroupNature();					//T����ÿһ���Ӧ������
	void Calculate(map<int,vector<float>>::iterator itMap);
	void Calculate(const int index, vector<float> &vt);

	bool PreSelect(vector<int> &vtResultIndex);			//��ѡ  
	void ExtractPreResult(vector<int> vtResultIndex);	//��ȡ��ѡ�������m_afterPreResult��m_mapAfterPreResult��
	bool AccuSelect(vector<int> &vtResultIndex);		//��ѡ  ����true��ѡ�ɹ�������false ���޽��
	void CalculateFinallyGroup(const vector<vector<float>> &m_preResult,vector<float> &ReturnResult);//�������յ�����ֵ����������Tֵ��ɸѡ����
	void Display(vector<vector<float>> &vtResult,map<CString,vector<float>> &mapResult,int resultIndex);				//��ʾ���
	void ClearData(bool bClearAll = false);						//�����м䴫false ���������д�ture
	
public:
	CListCtrl m_ComponentList;							//����б�
	CListCtrl m_NatureList;								//�����б�
	CListCtrl m_ResultList;								//����б�
	CEdit m_inputComEdit;								//�������༭��
	CEdit m_inputNatureEdit;							//��������༭��

	//����Ϊ�Զ������
	vector<SNatureCalcCoefficient> m_vtFixedNatureCalcCoe;//T�������ļ��л�ȡ�ģ��̶����ʼ���ϵ������
	map<CString, ChoiceValue> m_mapNatureChoiceValue;	//T�������ļ��л�ȡ�ģ�����ѡ�񼫴�ֵ���Ǽ�Сֵ

	//T�˳����У��涨������йص�������˳�����������˳����ͬ �������йصĶ�����������˳����ͬ
	vector<CComponent> m_vtComponent;					//T�������
	vector<CNature> m_vtNature;							//T��������
	map<CString, vector<float>> m_mapNatureResult;		//T���ݽض����%�����ϵ�� �������ʽ��
														//T�� �� �ܶȣ�at(1)=0.93 at(2)=1.2 at(3)=1.3

	vector<vector<float>> m_vtComponentGroupingBefore;	//T���ʷ������������ݽض����ݽ�����ϵ�����,��������ʾ������
	vector<vector<float>> m_vtComponentGrouping;		//T���ʷ������������ݽض����ݽ�����ϵ�����
	vector<vector<float>> m_afterPreResult;				//��ѡ֮���m_vtComponentGrouping��ѡ�������������Ľض������ϣ���Ҫ���о�ѡ��
	map<CString,vector<float>> m_mapAfterPreResult;		//��ѡ֮��Ľ������ͨ������������ϼ�������Ľ��
	map<CString,vector<float>> m_mapAfterPreResultDi;	//��ѡ֮������Diֵ

	int m_row;											//���˫���б�ѡ�е���
	int m_column;										//���˫���б�ѡ�е���
	
};
