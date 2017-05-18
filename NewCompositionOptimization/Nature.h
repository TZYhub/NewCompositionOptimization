

#pragma once


class CNature
{
public:
	CNature(void);
	~CNature(void);
	//T��ȡ���ʽ�ȡ����
	vector<float> &GetVtNatureRange(){return m_natureRange;}
	const CString& GetNatureName(){return m_natureName;}
	const ChoiceValue GetChoiceValue(){return m_choiceValue;}

protected:
	CString m_natureName;			//T��������
	vector<float> m_natureRange;	//T��ȡֵ
	ChoiceValue m_choiceValue;		//Tѡ�����ֵ������Сֵ
};

