
#pragma once
#undef DEBUG
#undef _DEBUG
//TCinit_includes:
#include<tcinit/tcinit.h>

//TC_includes
#include<tc/tc_startup.h>
#include<tc/emh.h>//Error Message Handler (EMH)

//tccore includes
#include<tccore/item.h>

//C_Header
#include<stdio.h>
#include<conio.h>

//Bom includes
#include<bom\bom.h>

//C++_Header
#include<iostream>
using namespace std;
#include<TCINIT\tcinit.h>
#include<tccore\aom.h>
#include<ae\dataset.h>
#include<ae\datasettype.h>
#include<tccore\grm.h>
#include<tccore\aom_prop.h>
#include<sa/user.h>
#include<tc/folder.h>
#include<epm/epm.h>
#include<epm\epm_errors.h>
#include<epm\epm_task_template_itk.h>
#include<FCLASSES\tc_date.h>
#include<LOV\lov.h>
#include <map>
#include<tccore/custom.h>
#include<tccore\project.h>
#include<tc/preferences.h>
#include<tc/envelope.h>
#include <ctime> 
//int status = ITK_ok;
int error(int iStatus);
//Macro defination