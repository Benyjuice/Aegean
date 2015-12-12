#include<stdlib.h>
#include"sysInfo.h"
#include"memPool.h"

#define SIZE 100*1024*1024

int main() {
	void *p = malloc(SIZE);
	sysInfoConfig(p, SIZE);
	memPoolConfig();
	memTest();
	void *p1 = dspMalloc(1024);
	void *p2 = dspMalloc(4096);
	printf("p1=%x\n",p1);
	printf("p2=%x\n",p2);
	return 0;
}
