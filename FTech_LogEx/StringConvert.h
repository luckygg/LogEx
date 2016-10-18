#pragma once

//----------------------------------------------------------
// String Conversion Functions
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2016-10-17 10:26
// Modified by William Kim
//----------------------------------------------------------

class CStringConvert
{
public :
	CStringConvert();
	~CStringConvert();

public :
	static bool CStringToChar(const CString strIn, char* pchOut)
	{
		if (pchOut == NULL) return false;

		size_t szCvt = 0;
		wcstombs_s(&szCvt, pchOut, strIn.GetLength()+1, strIn, _TRUNCATE);

		return true;
	}
};