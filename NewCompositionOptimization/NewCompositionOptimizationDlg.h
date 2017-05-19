
// NewCompositionOptimizationDlg.h : ͷ�ļ�
//
#include "Component.h"
#include "Nature.h"
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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	void Init();									//���г�ʼ��
	void AutoSizeListColumn(CListCtrl &clist,int column);//T�Զ������б�ĳ�п��
	void InitCompositionList();						//��ʼ������б�
	void InitNatureList();							//��ʼ�������б�
	void InitResultList();							//��ʼ������б�
	void LoadFixeCalcCoe();							//T���ع̶�����ϵ��
	void LoadNatureChoiceValue();					//T�������ʼ���ֵ�ͼ�Сֵ
	void LoadVtStrFromIni(vector<CString> &vtStr,const CString& keyStr);	//�������ļ��л�ȡ�ַ�������

	void UpDateComponetList();						//����������иĶ�ʱ�����øú���������ʾ
	void UpDateNatureList();						//�����������иĶ�ʱ�����øú���������ʾ
	void UpDateResultList();						//���������������иĶ�ʱ�����øú���������ʾ����б�

protected:
	//T��ȡ���ʼ���ϵ��,�����̶�ֵ�Ͳ��̶�ֵ��,ÿ�μ���ǰ�������ô˺������Ի�ȡ��Ӧϵ��
	float GetNatureCalcCoefficient(const CString& cName, const CString nName,const float cValue);
	//T�ӹ̶�ֵ�л�ȡϵ�������У��򷵻ش���0��ֵ�������򷵻�-1
	float GetFixedNatureCalcCoe(const CString& cName, const CString& nName, const float cValue);
	//Tʹ�ù�ʽ��������ϵ��
	float GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue);


	BOOL GetSelectCheckBox(const CString& str);//T��ȡѡ��ĸ�ѡ�򣬴���ΪComponent��ȡ��֣�����ΪNature��ȡ����
	void CalculateNature();
	void Calculate(map<int,vector<float>>::iterator itMap);
	void Calculate(const int index, vector<float> &vt);

	void CombinationTruncationData();				//T��Ͻض��������

	bool m_bIsSelectComponent;						//T�Ƿ�������ѡ��
	bool m_bIsSelectNature;							//T�Ƿ��������ѡ��

	int m_row;
	int m_column;

protected:
	//T�˳����У��涨������йص�������˳�����������˳����ͬ �������йصĶ�����������˳����ͬ
	vector<CComponent> m_vtComponent;	//T�������
	vector<CNature> m_vtNature;			//T��������
	vector<SNatureCalcCoefficient> m_vtFixedNatureCalcCoe;//T�̶����ʼ���ϵ������
	map<CString, ChoiceValue> m_mapNatureChoiceValue;//T����ѡ�񼫴�ֵ���Ǽ�Сֵ

	vector<vector<float>> m_vtSectionValue;//T������ݽضι�������  �ڲ���vector<float>����������m_vtComponent������ͬ
	map<CNature, vector<float>> m_mapNatureResult;//T���ݽض����%�����ϵ�� �������ʽ��
												//T�� �� �ܶȣ�at(1)=0.93 at(2)=1.2 at(3)=1.3

	vector<vector<float>> m_vtComponentGrouping;//T���ʷ������������ݽض����ݽ�����ϵ�����
public:
	//T�����ѡ��ť
	afx_msg void OnBnClickedBtnStartOptimization();
	afx_msg void OnBnClickedBtnSelectComponent();

	//����б�
	CListCtrl m_ComponentList;
	CListCtrl m_NatureList;
	CListCtrl m_ResultList;
	afx_msg void OnBnClickedBtnSelectNature();
	CEdit m_inputComEdit;
	CEdit m_inputNatureEdit;
	afx_msg void OnNMDblclkListComponent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnNMDblclkListNature(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit2();
};
