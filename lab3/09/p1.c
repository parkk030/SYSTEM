#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 16
#define QNAME_W "/1_queue"
#define QNAME_R "/2_queue"
#define PRIOR 1
char receive[BUFSIZE];
int main()
{
    pid_t pid;
    mqd_t qd;
    struct mq_attr q, old_q;
    int prio;
    char buf[BUFSIZE];
    q.mq_maxmsg = 10;       /* 큐안에서 최대 메세지 수 */
    q.mq_msgsize = BUFSIZE; /* 메세지 최대 크기*/

    pid = fork();

    if (pid == 0) //자식 부분
    {
        if ((qd = mq_open(QNAME_R, O_RDONLY | O_NONBLOCK, 0600, NULL)) == -1)
        {
            perror("mq_open failed");
            exit(1);
        }
        q.mq_flags = 0; 
        if (mq_setattr(qd, &q, NULL))
        {
            perror("mq_setattr failed");
            exit(1);
        }
        if (mq_getattr(qd, &old_q))
        {
            perror("mq_getattr failed");
            exit(1);
        }
        
        while (1)
        {
            mq_receive(qd, receive, BUFSIZE, &prio);
            printf("Talk >> %s		", receive);
        }

        if (mq_close(qd) == -1)
        {
            perror("mq_close failed");
            exit(1);
        }
        if (mq_unlink(QNAME_R) == -1)
        {
            perror("mq_unlink failed");
            exit(1);
        }
    }
    else if (pid > 0) //부모 부분
    {
        if ((qd = mq_open(QNAME_W, O_CREAT | O_WRONLY, 0600, &q)) == -1)
        {
            perror("mq_open failed");
            exit(1);
        }
        char input[BUFSIZE];
        while (1)
        {
            fgets(input, BUFSIZE, stdin);
            if (input[0] != 0)
            {
                if (mq_send(qd, input, BUFSIZE, PRIOR) == -1)
                {
                    perror("mq_send failed");
                    exit(1);
                }
                printf("\n");
            }
            memset(input, 0, BUFSIZE);
        }
        if (mq_close(qd) == -1)
        {
            perror("mq_close failed");
            exit(1);
        }
    }
    else //실패 
    {
        printf("fork failed\n");
    }
}
