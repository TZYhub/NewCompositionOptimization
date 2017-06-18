
#pragma once

class CComponent
{
public:
	CComponent(void);
	~CComponent(void);
	static void SetComponentFixedValue(const map<CString, float>& mapFixedValue);//设置组分计算的固定系数
	//T获取组分截取数组
	vector<float> &GetVtComponentRange(){return m_vtComponentRange;}
	vector<float>& GetVtComponentBeforeRange(){return m_vtBeforeCalcRange;}
	const CString& GetComponentName(){return m_ComponentName;}
	const CString& GetStrComponentRange(){return m_strRange;}
	void SetComponentName(const CString& cName);
	void SetStrComponentRange(const CString& sRange);
	float GetBeforeRangeValue(const float afterCalcValue);//T使用计算后的值来查找计算前的截断值，用于显示

protected:
	void CStringToFloat(CString str,float &a,float &b,bool bNeedSort=true);//字符串解析为浮点 如“1-2”，a=1.0,b=2.0;
	float FindFixedValue();//从m_ComponentFixedValue找到组分对应的固定系数值
protected:
	CString m_ComponentName;//T组分名
	CString m_strRange;//T取值范围的字符串
	vector<float> m_vtBeforeCalcRange;//T计算前的截取值
	vector<float> m_vtComponentRange;//T计算后的截取值
	static map<CString, float> m_ComponentFixedValue;//T截取值计算时分母使用的固定系数，从配置文件中获取
};

