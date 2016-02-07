#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

#include "config.h"
#include "version.h"
#include "standalone.h"
#include "child.h"

int main(void)
{
	struct passwd *userinfo;

	/*
	 * read the configuration file and set the program options
	 */

	if(read_config() != 0) return 1;

	start_listening();

	/*
	 * daemon must have normal user (f.ex. g-pop3d user) privilleges
	 * so we're changing uid of the process
	 */

	if(userinfo=getpwnam("nobody"))
  	{
        	setuid(userinfo->pw_uid);
	}
	else
	{
		printf("ERROR: There's no user %s in the system.\n", config.user);
		return 1;
	}

	/*
	 * become a daemon ; if fork() returns 0 the program becomes a daemon
	 */

        switch (fork())
        {
                case -1:
                        exit(0);
                case 0:
                        break;
                default:
                        _exit(0);
	}
        setsid();
	
	/*
	 * here's a daemon process code - the main loop of the listening daemon
	 */

	while(1)
	{
		/*
		 * check if there's a new incomming connection.
		 * if there's a new connection it's handled by a new child-process
		 */

		if(check_connection() == 1)
		{
			/*
			 * create child_process to handle new incomming connection
			 */

                        if(!fork())
                        {
				/*
				 * start the main child process/loop
				 */

				main_child();
			}
			close(new_fd);  // parent doesn't need this
		}
	}

	return 0;
}
