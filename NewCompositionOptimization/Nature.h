

#pragma once


class CNature
{
public:
	CNature(void);
	~CNature(void);
	//T��ȡ���ʽ�ȡ����
	vector<float> &GetVtNatureRange(){return m_vtNatureRange;}
	const CString& GetStrNatureRange(){return m_strNRange;}
	const CString& GetNatureName(){return m_natureName;}
	const ChoiceValue GetChoiceValue(){return m_choiceValue;}
	void SetNatureName(const CString& nName);
	void SetStrNatureRange(const CString& sRange);
	void SetNatureChoiceValue(ChoiceValue cv){m_choiceValue = cv;}//����ѡ�񼫴�ֵ���Ǽ�Сֵ

protected:
	void CStringToFloat(CString str,float &a,float &b,bool bNeedSort=true);//�ַ�������Ϊ���� �硰1-2����a=1.0,b=2.0;

protected:
	CString m_natureName;			//T��������
	CString m_strNRange;			//Tȡֵ��Χ���ַ���
	vector<float> m_vtNatureRange;	//T��ȡֵ
	ChoiceValue m_choiceValue;		//Tѡ�����ֵ������Сֵ
};

