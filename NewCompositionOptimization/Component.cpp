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
		//T��������ķ�Χ�����洢��������
		float a;
		float b;
		m_vtComponentRange.clear();
		//����ת��Ϊ����ֵ,���ַ�������Ϊ������
		CStringToFloat(m_strRange, a, b);
		//��������1�ضϣ���ŵ�map��
		while (a + 1 < b)//�����жϵ�ǰ�᣺ȷ��b��aҪ�����Ӧ��������ʱ������
		{
			m_vtComponentRange.push_back(a);
			a++;
		}
		m_vtComponentRange.push_back(a);
		m_vtComponentRange.push_back(b);
	}
	//T�����Թ̶�ϵ�����õ����մ洢��ֵ
	int iSize = m_vtComponentRange.size();
	float fixedValue = FindFixedValue();
	if (fixedValue > 0.0000001 || fixedValue < -0.0000001)//T��ȡֵ��Ϊ0
	{
		for (int i = 0; i < iSize; i++)
		{
			m_vtComponentRange.at(i) /= fixedValue;//ÿһ����ȡֵ�����Թ̶�ϵ����������
		}
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
	if (bNeedSort)//�����Ҫ����,����Ĭ��Ϊ����a<b
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