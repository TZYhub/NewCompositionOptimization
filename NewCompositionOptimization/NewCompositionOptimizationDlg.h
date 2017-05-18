
// NewCompositionOptimizationDlg.h : 头文件
//
#include "Component.h"
#include "Nature.h"
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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	void Init();									//所有初始化
	void AutoSizeListColumn(CListCtrl &clist,int column);//T自动调整列表某列宽度
	void InitCompositionList();						//初始化组成列表
	void InitNatureList();							//初始化性质列表
	void InitResultList();							//初始化结果列表
	void LoadFixeCalcCoe();							//T加载固定性质系数
	void LoadVtStrFromIni(vector<CString> &vtStr,const CString& keyStr);	//从配置文件中获取字符串数据

protected:
	//T获取性质计算系数,包括固定值和不固定值的,每次计算前都来调用此函数，以获取对应系数
	float GetNatureCalcCoefficient(const CString& cName, const CString nName,const float cValue);
	//T从固定值中获取系数，若有，则返回大于0的值，若无则返回-1
	float GetFixedNatureCalcCoe(const CString& cName, const CString& nName, const float cValue);
	//T使用公式计算性质系数
	float GetNatureCalcCoeWithFormula(const CString& cName, const CString& nName, const float cValue);


	bool m_bIsSelectComponent;						//T是否进行组分选择
	bool m_bIsSelectNature;							//T是否进行性质选择



protected:
	//T此程序中，规定与组分有关的数组则顺序都与组分数组顺序相同 与性质有关的都与性质数组顺序相同
	vector<CComponent> m_vtComponent;	//T组分数组
	vector<CNature> m_vtNature;			//T性质数组
	vector<SNatureCalcCoefficient> m_vtFixedNatureCalcCoe;//T固定性质计算系数数组

	vector<vector<float>> m_vtSectionValue;//T组分数据截段构成数组  内部的vector<float>数组排序与m_vtComponent数组相同
	map<CNature, vector<float>> m_mapNatureResult;//T根据截段组分%和组分系数 计算性质结果
												//T如 ： 密度，at(1)=0.93 at(2)=1.2 at(3)=1.3

public:
	//T组分优选按钮
	afx_msg void OnBnClickedBtnStartOptimization();
	afx_msg void OnBnClickedBtnSelectComponent();

	//组成列表
	CListCtrl m_ComponentList;
	CListCtrl m_NatureList;
	CListCtrl m_ResultList;
	afx_msg void OnBnClickedBtnSelectNature();
};
