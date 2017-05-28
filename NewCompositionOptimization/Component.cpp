#include "StdAfx.h"
#include "Component.h"

map<CString, float> CComponent::m_ComponentFixedValue = map<CString, float>();

CComponent::CComponent(void)
{
}


CComponent::~CComponent(void)
{
}

void CComponent::SetComponentFixedValue(const map<CString, float>& mapFixedValue)
{
	if (!mapFixedValue.empty())
	{
		m_ComponentFixedValue = mapFixedValue;
	}
}

void CComponent::SetComponentName(const CString& cName)
{
	if (cName != "")
	{
		m_ComponentName = cName;
	}
}

void CComponent::SetStrComponentRange(const CString& sRange)
{
	if (sRange != "")
	{
		m_strRange = sRange;
	}
	if (m_strRange != "")
	{
		//T解析输入的范围，并存储到数组中
		float a;
		float b;
		m_vtBeforeCalcRange.clear();
		//二、转换为浮点值,由字符串解析为浮点数
		CStringToFloat(m_strRange, a, b);
		//三、按加1截断，存放到map中
		while (a + 1 < b)//做此判断的前提：确认b比a要大，这个应该在输入时做处理
		{
			m_vtBeforeCalcRange.push_back(a);
			a++;
		}
		m_vtBeforeCalcRange.push_back(a);
		m_vtBeforeCalcRange.push_back(b);
	}
	//T最后除以固定系数，得到计算时存储的值
	int iSize = m_vtBeforeCalcRange.size();
	m_vtComponentRange = m_vtBeforeCalcRange;
	float fixedValue = FindFixedValue();
	if (fixedValue > 0.0000001 || fixedValue < -0.0000001)//T获取值不为0
	{
		for (int i = 0; i < iSize; i++)
		{
			m_vtComponentRange.at(i) /= fixedValue;//每一个截取值都除以固定系数，并保存
		}
	}
}

//T使用计算后的值来查找计算前的截断值，用于显示
float CComponent::GetBeforeRangeValue(const float afterCalcValue)
{
	int iSize = m_vtComponentRange.size();
	for (int i = 0; i < iSize; i++)
	{
		if (m_vtComponentRange.at(i) - afterCalcValue < 0.0000001
			&&  m_vtComponentRange.at(i) - afterCalcValue > -0.0000001  )//T即两值相等
		{
			return m_vtBeforeCalcRange.at(i);
		}
	}
	return -1;
}



void CComponent::CStringToFloat(CString str, float &a, float &b, bool bNeedSort/*=true*/)
{
	int pos = str.Find('-');
	CString strA = str.Left(pos);
	int n = str.GetLength();
	CString strB = str.Right(n - 1 - pos);
	a = _ttof(strA);
	b = _ttof(strB);
	if (bNeedSort)//如果需要排序,排序默认为升序即a<b
	{
		if (a > b)
		{
			float t = a;
			a = b;
			b = t;
		}
	}
}

float CComponent::FindFixedValue()
{
	map<CString, float>::iterator itMap = m_ComponentFixedValue.find(m_ComponentName);
	if (itMap != m_ComponentFixedValue.end())
	{
		return itMap->second;
	}
	return 0;
}