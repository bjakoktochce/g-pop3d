#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <sys/param.h>

#define MYPORT 1100
#define BACKLOG 10

#define BANNER "My simple network server (by grypsy@2001/08/25)\r\n"

char buf[100];
int numbytes;

int pid;

int sockfd, new_fd;                     // listen on sock_fd, new connection on new_fd
struct sockaddr_in my_addr;             // my address information
struct sockaddr_in their_addr;          // connector's address information
int sin_size;
int yes=1;

int len, bytes_sent;
struct sigaction sa;


void sigchld_handler(int s)
{
        while(wait(NULL) > 0);
}

int start_listening(void)
{
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1)
        {
                perror("socket");
                exit(1);
        };
        if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
        {
                perror("setsockopt");
                exit(1);
        }

        my_addr.sin_family = AF_INET;           // host byte order
        my_addr.sin_port = htons(MYPORT);       // short, network byte order
        my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        memset(&(my_addr.sin_zero), '\0', 8);   // zero the rest of the struct

        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
        {
                perror("bind");
                exit(1);
        }
        if (listen(sockfd, BACKLOG) == -1)
        {
                perror("listen");
                exit(1);
        }

        /* Removes all dead (zombie) processes */

        sa.sa_handler = sigchld_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGCHLD, &sa, NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }
	return 0;
}

int check_connection(void)
{
        sin_size = sizeof(struct sockaddr_in);
        if(new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size))	return 1;
	return 0;
}
