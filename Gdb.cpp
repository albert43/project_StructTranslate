#include "stdafx.h"
#include <iostream>
#include "Gdb.h"
using namespace std;
using namespace Al;

Gdb::Gdb(void)
{
}


Gdb::~Gdb(void)
{
}

AL_RET Gdb::gdb2default(char *pszOrigin, char **ppszResult)
{
	int		iDepth = 0;
	string	strOri;
	string	*strRes;
	int		iPos = -1;
	int		i;

	if (pszOrigin == NULL)
		return AL_RET_ERR_PARAMETER;

	strOri = pszOrigin;

	//	Remove unused characters.
	strRes = removeCharacter(strOri);
	
	//	Deal with comma
	strOri.assign(*strRes);
	delete strRes;
	strRes = CommaBrances(strOri);

	//	Deal with braces

	*ppszResult = (char *)new char[strRes->length() + 1];
	if (*ppszResult == NULL)
		return AL_RET_ERR_SYS_MEMORY;

	strcpy(*ppszResult, strRes->c_str());

	return AL_RET_SUCCESS;
}

string* Gdb::removeCharacter(string strOriginal)
{
	int				i;
	string			*strResult = new string;

	for (i = 0; i < strOriginal.length(); i++)
	{
		if ((strOriginal[i] > 32) && (strOriginal[i] < 127))
			strResult->append(strOriginal.substr(i, 1));
	}

	return strResult;
}

string* Gdb::CommaBrances(string strOriginal)
{
	string		*strResult = new string;
	int			nDepth = 0;
	int			i, j;

	for (i = 0; i < strOriginal.length(); i++)
	{
		if ((strOriginal[i] == ',') && (strOriginal[i + 1] != '\''))
		{
			strOriginal.insert(i + 1, NEW_LINE);
			i += 2;
			for (j = 0; j < nDepth; j++)
				strOriginal.insert(++i, TAB);
		}
		else if (strOriginal[i] == '{')
		{
			if (i == 0)
			{
				strOriginal.insert(i + 1, NEW_LINE);
				i += 2;
				nDepth++;
				for (j = 0; j < nDepth; j++)
					strOriginal.insert(++i, TAB);
			}
			else
			{
				strOriginal.insert(i, NEW_LINE);
				i += 2;
				for (j = 0; j < nDepth; j++)
					strOriginal.insert(i++, TAB);
				strOriginal.insert(i + 1, NEW_LINE);
				i += 2;
				nDepth++;
				for (j = 0; j < nDepth; j++)
					strOriginal.insert(++i, TAB);
			}
		}
		else if (strOriginal[i] == '}')
		{
			strOriginal.insert(i, NEW_LINE);
			i += 2;
			nDepth--;

			for (j = 0; j < nDepth; j++)
				strOriginal.insert(i++, TAB);

			strOriginal.insert(i + 1, NEW_LINE);
			i += 2;

			for (j = 0; j < nDepth; j++)
				strOriginal.insert(++i, TAB);
		}
	}

	strResult->assign(strOriginal);

	return strResult;
}
