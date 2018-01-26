#include"header.h"
int len = 0,sfd = 0,nsfd = 0;pthread_t t2;
char abc[50] = {0};
void* ReadNodeandDisplay()
{
        while(1)
        {
                while(read (sfd, abc, sizeof(abc)))
                {
                        //printf("%s\n",abc);
                        printf("%s",abc);
                }
        }
}

int main(int argc, char **argv)
{
	struct sockaddr_in v;
	size_t length = 0; char *p = NULL;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	perror("socket:");
	v.sin_family = AF_INET;
	v.sin_port = htons(atoi(argv[1]));
	v.sin_addr.s_addr = inet_addr("127.0.0.1");
	len = sizeof(v);
	bind(sfd, (struct sockaddr*)&v, len);
	perror("bind:");
	connect(sfd, (struct sockaddr*)&v, len);
	perror("connect:");
        pthread_create(&t2,NULL,ReadNodeandDisplay,NULL);

	while(1)
	{
		//scanf("%s", abc);
		getline(&p, &length, stdin);
		p[length] = '\0';
		//scanf("%[^\n]s", abc);
		write(sfd, p, length);
		free(p);
		p = NULL;length = 0;
		//send(sfd, abc, sizeof(abc), MSG_OOB);
	}
}
