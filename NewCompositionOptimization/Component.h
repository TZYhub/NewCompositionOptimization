
#pragma once

class CComponent
{
public:
	CComponent(void);
	~CComponent(void);
	//T获取组分截取数组
	vector<float> &GetVtComponentRange(){return m_vtComponentRange;}
	const CString& GetComponentName(){return m_ComponentName;}
	const CString& GetStrComponentRange(){return m_strRange;}
	void SetComponentName(const CString& cName);
	void SetStrComponentRange(const CString& sRange);

protected:
	void CStringToFloat(CString str,float &a,float &b,bool bNeedSort=true);//字符串解析为浮点 如“1-2”，a=1.0,b=2.0;

protected:
	CString m_ComponentName;//T组分名
	CString m_strRange;//T取值范围的字符串
	vector<float> m_vtComponentRange;//T截取值
};

