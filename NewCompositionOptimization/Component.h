
#pragma once

class CComponent
{
public:
	CComponent(void);
	~CComponent(void);
	//T获取组分截取数组
	vector<float> &GetVtComponentRange(){return m_vtComponentRange;}
	const CString& GetComponentName(){return m_ComponentName;}

protected:
	CString m_ComponentName;//T组分名
	vector<float> m_vtComponentRange;//T截取值
};

