#include "StdAfx.h"
#include "Nature.h"


CNature::CNature(void)
{
}


CNature::~CNature(void)
{
}

void CNature::SetNatureName(const CString& nName)
{
	if (nName != "")
	{
		m_natureName = nName;
	}
}

void CNature::SetStrNatureRange(const CString& sRange)
{
	if (sRange != "")
	{
		m_strNRange = sRange;
	}
	if (m_strNRange != "")
	{
		//T��������ķ�Χ�����洢��������
		float a;
		float b;
		m_vtNatureRange.clear();
		//����ת��Ϊ����ֵ,���ַ�������Ϊ������
		CStringToFloat(m_strNRange, a, b);
		//��������1�ضϣ���ŵ�map��
		while (a + 1 < b)//�����жϵ�ǰ�᣺ȷ��b��aҪ�����Ӧ��������ʱ������
		{
			m_vtNatureRange.push_back(a);
			a++;
		}
		m_vtNatureRange.push_back(a);
		m_vtNatureRange.push_back(b);
	}
}


void CNature::CStringToFloat(CString str, float &a, float &b, bool bNeedSort/*=true*/)
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

