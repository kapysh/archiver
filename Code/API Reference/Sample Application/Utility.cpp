#include "stdafx.h"

int GetIntFromString( TCHAR * ptszNumString )
{
	int num = 0;

	#ifdef UNICODE 
		CHAR strTmp[20]; 
		wcstombs(strTmp, (const wchar_t *) ptszNumString, sizeof(strTmp)); 
		num = atoi(strTmp); 
    #else 
	    num = atoi(ptszNumString); 
    #endif 

	return (num);
}