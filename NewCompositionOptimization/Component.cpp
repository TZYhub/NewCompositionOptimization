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