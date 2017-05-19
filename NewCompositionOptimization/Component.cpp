#include "StdAfx.h"
#include "Component.h"


CComponent::CComponent(void)
{
}


CComponent::~CComponent(void)
{
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
		m_vtComponentRange.clear();
		//二、转换为浮点值,由字符串解析为浮点数
		CStringToFloat(m_strRange, a, b);
		//三、按加1截断，存放到map中
		while (a + 1 < b)//做此判断的前提：确认b比a要大，这个应该在输入时做处理
		{
			m_vtComponentRange.push_back(a);
			a++;
		}
		m_vtComponentRange.push_back(a);
		m_vtComponentRange.push_back(b);
	}
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