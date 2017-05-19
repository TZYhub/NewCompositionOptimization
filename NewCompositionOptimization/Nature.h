

#pragma once


class CNature
{
public:
	CNature(void);
	~CNature(void);
	//T获取性质截取数组
	vector<float> &GetVtNatureRange(){return m_vtNatureRange;}
	const CString& GetStrNatureRange(){return m_strNRange;}
	const CString& GetNatureName(){return m_natureName;}
	const ChoiceValue GetChoiceValue(){return m_choiceValue;}
	void SetNatureName(const CString& nName);
	void SetStrNatureRange(const CString& sRange);
	void SetNatureChoiceValue(ChoiceValue cv){m_choiceValue = cv;}//设置选择极大值还是极小值

protected:
	void CStringToFloat(CString str,float &a,float &b,bool bNeedSort=true);//字符串解析为浮点 如“1-2”，a=1.0,b=2.0;

protected:
	CString m_natureName;			//T性质名称
	CString m_strNRange;			//T取值范围的字符串
	vector<float> m_vtNatureRange;	//T截取值
	ChoiceValue m_choiceValue;		//T选择最大值还是最小值
};

