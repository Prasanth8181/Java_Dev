#include"TeamCenterITK.h"
void displayusage(void)
{
	cout << "\n--------------------------------------------------" << endl;
	cout << "\n usage" << endl;
	cout << "XXXX" << "-u=<user_id> -P=<password> -g=<group>" << endl;
	cout << "\n--------------------------------------------------" << endl;
}

int ITK_user_main(int argc, char* argv[])
{
	//variable declaration
    int Ifail = ITK_ok;
	char* cText =NULL;
	int iMsg;
	string value;
	
	//source code
	const char* user = ITK_ask_cli_argument("-u=");
	const char* password = ITK_ask_cli_argument("-p=");
	const char* group = ITK_ask_cli_argument("-g=");
	Ifail = ITK_init_module(user, password, group);
	if (Ifail == ITK_ok)
	{
		TC_write_syslog("Login successfull :%s", __DATE__);
		printf("Login successfull");
		printf("File :%s\n,Date: %s\n,Time: %s\n,Line: %d\n", __FILE__, __DATE__, __TIME__, __LINE__);
	}
	else
	{
		TC_write_syslog("Login not successfull :%s", __TIME__);
		if (ITK_ask_cli_argument("-h") != NULL || ITK_ask_cli_argument("-help") != NULL)
		{
			displayusage();
			exit(0);
		}
		EMH_ask_error_text(Ifail, &text);
		printf("\n\n\t Errorcode:%d Errormsg:%s", Ifail,text);
	}

	return 0;
}