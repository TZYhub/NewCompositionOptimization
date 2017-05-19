
#pragma once

class CComponent
{
public:
	CComponent(void);
	~CComponent(void);
	//T��ȡ��ֽ�ȡ����
	vector<float> &GetVtComponentRange(){return m_vtComponentRange;}
	const CString& GetComponentName(){return m_ComponentName;}
	const CString& GetStrComponentRange(){return m_strRange;}
	void SetComponentName(const CString& cName);
	void SetStrComponentRange(const CString& sRange);

protected:
	void CStringToFloat(CString str,float &a,float &b,bool bNeedSort=true);//�ַ�������Ϊ���� �硰1-2����a=1.0,b=2.0;

protected:
	CString m_ComponentName;//T�����
	CString m_strRange;//Tȡֵ��Χ���ַ���
	vector<float> m_vtComponentRange;//T��ȡֵ
};

