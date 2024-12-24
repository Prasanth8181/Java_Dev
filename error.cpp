#include "TeamCenterITK.h"

int error(int iStatus)
{
	char* cMessage = NULLTAG;
	if (iStatus != ITK_ok)
	{
		EMH_ask_error_text(iStatus, &cMessage);
		if (cMessage)
		{
			cout << "Error: " << cMessage << endl;
			return 0;
		}
		else
		{
			cout << "Unknown error occurred with status code: " << iStatus << endl;
		}
	}
	return 0;
}
