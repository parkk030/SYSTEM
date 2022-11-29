#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(void)

{
	int fd;
	int nread, cnt=0, errcnt=0, good=0;
	char ch, text1[] = "I CAN FLY";
	char text2[] = "I AM BLUE";
	char text3[] = "HELLOW";
	time_t start, end;
 
	struct termios init_attr, new_attr;
	fd = open(ttyname(fileno(stdin)), O_RDWR);
	tcgetattr(fd, &init_attr);
	new_attr = init_attr;
	new_attr.c_lflag &= ~ICANON;
	new_attr.c_lflag &= ~ECHO; /* ~(ECHO | ECHOE | ECHOK | ECHONL); */
	new_attr.c_cc[VMIN] = 1;
	new_attr.c_cc[VTIME] = 0;

	if (tcsetattr(fd, TCSANOW, &new_attr) != 0) {
		fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
	}

	printf("다음 문장을 그대로 입력하세요.\n");
	start = time(NULL);
	printf("%s\n",text1);
	while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
		if (ch == text1[cnt++]){
			write(fd, &ch, 1);
			good++;
			}
		else {
			write(fd, "*", 1);
			errcnt++;
		}
	}
	cnt=0;
	printf("\n%s\n",text2);
	while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
		if (ch == text2[cnt++]){
			write(fd, &ch, 1);
			good++;
			}
		else {
			write(fd, "*", 1);
			errcnt++;
		}
	}
	cnt=0;
	printf("\n%s\n",text3);
	while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
		if (ch == text3[cnt++]){
			write(fd, &ch, 1);
			good++;
			}
		else {
			write(fd, "*", 1);
			errcnt++;
		}
	}
	cnt=0;
	end=time(NULL);
	printf("Time start: %d\n", start);
	printf("Time end: %d\n", end);
	printf("During the time: %d\n", end-start);	
	printf("Typing false: %d\n", errcnt);
	printf("Typing speed: %0.4f\n", (float)good/(end-start));
	tcsetattr(fd, TCSANOW, &init_attr);
	close(fd);
}
