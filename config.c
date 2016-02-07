#include <string.h>
#include <stdio.h>
#include "config.h"
 
FILE *config_file;

struct G_POP3D_CONFIG config;

int open_config(void)
{
	if((config_file = fopen("g-pop3d.conf","r")) == NULL) return 1;
	return 0;
}

void close_config(void)
{
	fclose(config_file);
}

int read_config(void)
{
	char *config_line;
	char *config_line_option;		// before "=" f.ex. LISTEN_PORT
	char *config_line_value;		// after "=" f.ex. 110
	int i=0;

	config_line = (char*)malloc(128);

	if(open_config() == 1)
	{
		printf("ERROR: Couldn't open config file.\n");
		return 1;
	}
	
	/*
	 * if config file was opened successfully then read the config file
	 */

	while((fgets(config_line, 128, config_file)) != NULL)
	{
		config_line_option=strtok(config_line,"=");
		config_line_value=strtok(NULL, "=");

		/*
		 * check if there's a BANNER option in the configfile
		 */

		if( strcmp(config_line_option, "BANNER") == 0)
		{	
			config.banner = (char*)malloc(strlen(config_line_value));
			strcpy(config.banner, config_line_value);
		}

		/*
		 * check if there's a LISTEN_PORT option in the configfile
		 */

		if( strcmp(config_line_option, "LISTEN_PORT") == 0)
		{
			config.listen_port = (char*)malloc(strlen(config_line_value));
			strcpy(config.listen_port, config_line_value);
		}

		/*
		 * check if there's a USER option in configfile
		 */

                if( strcmp(config_line_option, "USER") == 0)
                {
                        config.user = (char*)malloc(strlen(config_line_value));
                        strcpy(config.user, config_line_value);
                }

	}

	free(config_line);
	close_config();
	return 0;
}
