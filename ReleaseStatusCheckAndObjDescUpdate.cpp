#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	tag_t itemRevision = NULLTAG;
	int no_of_statuses = 0;
	tag_t* statuses = NULLTAG;
	char* statusName = NULL;
	tag_t statusType = NULLTAG;
	tag_t processTemplate = NULLTAG;
	tag_t datasetName = NULLTAG;
	int attachmentType = 3;
	tag_t verifiedTemplate = NULLTAG;
	tag_t parentTaskTemplate = NULLTAG;
	tag_t wfProcess = NULLTAG;
	tag_t attachments[1];
	int attachment_types[1];
	tag_t newProcess = NULLTAG;


	if (ITK_init_module("infodba", "infodba", "dba") == ITK_ok)
	{
		ITEM_find_rev("000068", "A", &itemRevision);
		if (AOM_ask_value_tags(itemRevision, "release_status_list", &no_of_statuses, &statuses) == ITK_ok)
		{
			cout << "Number of release statuses: %d\n" << no_of_statuses;
			if (no_of_statuses == 0)
			{
				attachments[0] = itemRevision;
				attachment_types[0] = EPM_target_attachment;
				EPM_find_process_template("TCM Release Process", &wfProcess);//find the existing process template
				error(EPM_create_process("TCM Release Process", "TCM Release Process", wfProcess, 1 , attachments, attachment_types, &newProcess));//initiating the workflow
				AOM_save_without_extensions(newProcess);
				AOM_set_value_string(itemRevision, "object_desc", "ITK released");
				AOM_save_without_extensions(itemRevision);
			}
			else
			{
				AOM_set_value_string(itemRevision, "object_desc", "Released");
			}
		}
	}
	return 0;
}
