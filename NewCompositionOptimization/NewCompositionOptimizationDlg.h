
// NewCompositionOptimizationDlg.h : 头文件
//
#include "Component.h"
#include "Nature.h"
#include "NatureDlg.h"
#include "ComponentDlg.h"
#pragma once


// CNewCompositionOptimizationDlg 对话框
class CNewCompositionOptimizationDlg : public CDialogEx
{
// 构造
public:
	CNewCompositionOptimizationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NEWCOMPOSITIONOPTIMIZATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//T组分优选按钮
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


	void Init();										//所有初始化
	void AutoSizeListColumn(CListCtrl &clist,int column);//T自动调整列表某列宽度
	void InitCompositionList();							//初始化组成列表
	void InitNatureList();								//初始化性质列表
	void InitResultList();								//初始化结果列表
	void LoadFixeCalcCoe();								//T加载固定性质系数
	void LoadNatureChoiceValue();						//T加载性质极大值和极小值
	void LoadComponentFixedValue();						//T从配置文件中获取组分截取值除的固定系数
	void LoadVtStrFromIni(vector<CString> &vtStr,const CString& keyStr, const CString& strPath = _T(""));	//从配置文件中获取字符串数据
	void WriteStrToIni(const vector<CString>& vtStr, const CString& keyStr, const CString& strPath);//写数据到配置文件中

	void UpdateComponetList();							//当组分数组有改动时，调用该函数重新显示
	void UpdateNatureList();							//当性质数组有改动时，调用该函数重新显示
	void UpdateResultList();							//当组分数组或性质有改动时，调用该函数重新显示结果列表


	//T获取性质计算系数,包括固定值和不固定值的,每次计算前都来调用此函数，以获取对应系数
	float GetNatureCalcCoefficient(const CString& cName, const CString nName,const float cValue);
	//T从固定值中获取系数，若有，则返回true,值存入rtValue中，若无则返回false
	bool GetFixedNatureCalcCoe(const CString& cName, const CString& nName, const float cValue, float& rtValue);
	//T使用公式计算性质系数
	float GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue);

	BOOL GetSelectCheckBox(const CString& str, const vector<CString>& vtStr);			//T获取选择的复选框，传入为"Component"获取组分，传入为"Nature"获取性质

	bool JudgmentInput();								//判断输入是否符合优选要求

	void CalculateNature();
	void CombinationTruncationData();					//T组合截断组分数据
	void CalculateComponentPercentage();				//T求和并计算出组分百分比
	void CalculateEachGroupNature();					//T计算每一组对应的性质
	void Calculate(map<int,vector<float>>::iterator itMap);
	void Calculate(const int index, vector<float> &vt);

	bool PreSelect(vector<int> &vtResultIndex);			//初选  
	void ExtractPreResult(vector<int> vtResultIndex);	//提取初选结果，到m_afterPreResult和m_mapAfterPreResult中
	bool AccuSelect(vector<int> &vtResultIndex);		//精选  返回true则精选成功，返回false 则无结果
	void CalculateFinallyGroup(const vector<vector<float>> &m_preResult,vector<float> &ReturnResult);//计算最终的数组值，包括计算T值，筛选分组
	void Display(vector<vector<float>> &vtResult,map<CString,vector<float>> &mapResult,int resultIndex);				//显示结果
	void ClearData(bool bClearAll = false);						//清理中间传false ，清理所有传ture
	
public:
	CListCtrl m_ComponentList;							//组分列表
	CListCtrl m_NatureList;								//性质列表
	CListCtrl m_ResultList;								//结果列表
	CEdit m_inputComEdit;								//组分输入编辑框
	CEdit m_inputNatureEdit;							//性质输入编辑框

	//下面为自定义变量
	vector<SNatureCalcCoefficient> m_vtFixedNatureCalcCoe;//T从配置文件中获取的，固定性质计算系数数组
	map<CString, ChoiceValue> m_mapNatureChoiceValue;	//T从配置文件中获取的，性质选择极大值还是极小值

	//T此程序中，规定与组分有关的数组则顺序都与组分数组顺序相同 与性质有关的都与性质数组顺序相同
	vector<CComponent> m_vtComponent;					//T组分数组
	vector<CNature> m_vtNature;							//T性质数组
	map<CString, vector<float>> m_mapNatureResult;		//T根据截段组分%和组分系数 计算性质结果
														//T如 ： 密度，at(1)=0.93 at(2)=1.2 at(3)=1.3

	vector<vector<float>> m_vtComponentGroupingBefore;	//T性质分组结果，即根据截段数据进行组合的数组,仅用于显示处理部分
	vector<vector<float>> m_vtComponentGrouping;		//T性质分组结果，即根据截段数据进行组合的数组
	vector<vector<float>> m_afterPreResult;				//初选之后从m_vtComponentGrouping中选出的满足条件的截断组分组合，需要进行精选，
	map<CString,vector<float>> m_mapAfterPreResult;		//初选之后的结果，即通过满足条件组合计算出来的结果
	map<CString,vector<float>> m_mapAfterPreResultDi;	//初选之后结果的Di值

	int m_row;											//鼠标双击列表选中的行
	int m_column;										//鼠标双击列表选中的列
	
};
