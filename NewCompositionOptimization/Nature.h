

#pragma once


class CNature
{
public:
	CNature(void);
	~CNature(void);
	//T获取性质截取数组
	vector<float> &GetVtNatureRange(){return m_natureRange;}
	const CString& GetNatureName(){return m_natureName;}
	const ChoiceValue GetChoiceValue(){return m_choiceValue;}

protected:
	CString m_natureName;			//T性质名称
	vector<float> m_natureRange;	//T截取值
	ChoiceValue m_choiceValue;		//T选择最大值还是最小值
};

