
#pragma once

class CComponent
{
public:
	CComponent(void);
	~CComponent(void);
	//T��ȡ��ֽ�ȡ����
	vector<float> &GetVtComponentRange(){return m_vtComponentRange;}
	const CString& GetComponentName(){return m_ComponentName;}

protected:
	CString m_ComponentName;//T�����
	vector<float> m_vtComponentRange;//T��ȡֵ
};

