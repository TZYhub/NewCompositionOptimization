
#pragma once

class CComponent
{
public:
	CComponent(void);
	~CComponent(void);
	static void SetComponentFixedValue(const map<CString, float>& mapFixedValue);//������ּ���Ĺ̶�ϵ��
	//T��ȡ��ֽ�ȡ����
	vector<float> &GetVtComponentRange(){return m_vtComponentRange;}
	vector<float>& GetVtComponentBeforeRange(){return m_vtBeforeCalcRange;}
	const CString& GetComponentName(){return m_ComponentName;}
	const CString& GetStrComponentRange(){return m_strRange;}
	void SetComponentName(const CString& cName);
	void SetStrComponentRange(const CString& sRange);
	float GetBeforeRangeValue(const float afterCalcValue);//Tʹ�ü�����ֵ�����Ҽ���ǰ�Ľض�ֵ��������ʾ

protected:
	void CStringToFloat(CString str,float &a,float &b,bool bNeedSort=true);//�ַ�������Ϊ���� �硰1-2����a=1.0,b=2.0;
	float FindFixedValue();//��m_ComponentFixedValue�ҵ���ֶ�Ӧ�Ĺ̶�ϵ��ֵ
protected:
	CString m_ComponentName;//T�����
	CString m_strRange;//Tȡֵ��Χ���ַ���
	vector<float> m_vtBeforeCalcRange;//T����ǰ�Ľ�ȡֵ
	vector<float> m_vtComponentRange;//T�����Ľ�ȡֵ
	static map<CString, float> m_ComponentFixedValue;//T��ȡֵ����ʱ��ĸʹ�õĹ̶�ϵ�����������ļ��л�ȡ
};

