#include"header.h"
//int nsfd [5] = {-1,-1,-1,-1,-1};
int nsfd [2] = {-1,-1};
int sfd = -1;
struct sockaddr_in v,v1;
int len = 0, i = 0;//,sfd = 0,nsfd = 0;
char abc[50] = {0}, sms[50] = {0};
void* acceptance()
{
	
	while(i < 2)
	{
		nsfd[i] = accept(sfd, (struct sockaddr*)&v1, &len);
		perror("accept:");
		i++;
	}
}
void* ReadNodeOneWriteToOther()
{
	while(1)
	{
			while(read (nsfd[0], abc, sizeof(abc)) > 0)
			{
				strcpy(sms,"Node_1: ");strcat(sms,abc);
				if(strlen(abc) > 0)
				{
					write(nsfd[1], sms, sizeof(sms));
			                //send(nsfd[1], sms, sizeof(sms), MSG_OOB);
				}
				break;
			}
	}
}
void* ReadNodeTwoWriteToOther()
{
	while(1)
	{
		while(read (nsfd[1], abc, sizeof(abc)) > 0)
		{
			strcpy(sms,"Node_2: ");strcat(sms,abc);
			if(strlen(abc) > 0)
			{
				write(nsfd[0], sms, sizeof(sms));
			        //send(nsfd[0], sms, sizeof(sms), MSG_OOB);
			}
				break;
		}
	}
}
int main(int argc, char **argv)
{
	pthread_t t = 0, t1 = 0, t2 = 0;

	sfd = socket(AF_INET,SOCK_STREAM,0);
	perror("socket:");

	v.sin_family = AF_INET;
	v.sin_port = htons(atoi(argv[1]));
	v.sin_addr.s_addr = inet_addr("0.0.0.0");
	len = sizeof(v);
	bind(sfd, (struct sockaddr*)&v, len);
	perror("bind:");

	listen(sfd, 5);
	perror("listen:");

        pthread_create(&t,NULL,acceptance,NULL);

		while (1)
		{
			if ((nsfd[0] != -1) && (nsfd [1] != -1))
		        {
				pthread_create(&t2,NULL,ReadNodeOneWriteToOther,NULL);
			        pthread_create(&t1,NULL,ReadNodeTwoWriteToOther,NULL);
				break;
			}
		}
	while(1);
}





