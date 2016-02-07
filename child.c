#include "standalone.h"
#include "config.h"

int main_child(void)
{
	close(sockfd); // child doesn't need this

	/*
	 * send the greeting banner
	 */

	send(new_fd, config.banner, strlen(config.banner), 0);

	/*
	 * exit child process
	 */

        close(new_fd);
        exit(0);
	return 0;
}
