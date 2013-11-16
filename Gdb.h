#pragma once
#define	NEW_LINE	"\r\n"
#define	TAB			"\t"
using namespace std;

namespace Al
{
	enum AL_RET
	{
		AL_RET_ERR_PARAMETER,
		AL_RET_ERR_SYS = -900,
		AL_RET_ERR_SYS_MEMORY,
		AL_RET_SUCCESS = 0
	};

	class Gdb
	{
	public:
		Gdb(void);
		~Gdb(void);

		AL_RET gdb2default(char *pszOrigin, char **ppszResult);

	private:
		string* removeCharacter(string strOriginal);
		string* CommaBrances(string strOriginal);
	};
}


