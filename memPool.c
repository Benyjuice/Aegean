/*
 * memPool.c
 */
#include <stdio.h>
#include "memPool.h"
#include "sysInfo.h"
#define P_SIZE	(2097152)
MemPoolStruct gMemPoolStruct;

void *poolMalloc(MemPoolStruct *memPoolInfo, int size);
int poolFree(MemPoolStruct *memPoolInfo, void *p);
int memPoolInit(SysInfoStruct *sysInfo, MemPoolStruct *memPoolInfo);

//memPool整体配置
void memPoolConfig() {
	memPoolInit(&gSysInfoStruct, &gMemPoolStruct);
}

void *dspMalloc(int size) {
	return poolMalloc(&gMemPoolStruct, size);
}

int dspFree(void *p) {
	return poolFree(&gMemPoolStruct, p);
}

void *blockMalloc(PoolBlockStruct *block, int size) {
	int pSize = block->pSize;
	int pNum = block->pNum;
	int currNum = block->currNum;

	//获取自由指针
	unsigned char *p = block->pfree;

	unsigned char **ppfree = (unsigned char **)block->pfree;
	if((currNum==pNum) || (pSize<size)) return NULL;
	block->pfree = *ppfree;
	block->currNum++;
	//满了之后pfree为空指针
	if(block->currNum==pSize) block->pfree=NULL;
	return (void *)p;
}

int blockFree(PoolBlockStruct *block, void *p) {
	int pSize = block->pSize;
	int pNum = block->pNum;

	//地址范围
	unsigned char *base = block->base;
	unsigned char *nextBase = base+pSize*pNum;

	unsigned char **ppfree = (unsigned char **)p;

	//判断传入地址合法性
	if((unsigned char *)p<base || (unsigned char *)p>=nextBase) return -1;
	if((((unsigned char *)p-base)%pSize)!=0) return -1;
	*ppfree = block->pfree;
	block->pfree = p;
	block->currNum--;
	return 1;
}

void *poolMalloc(MemPoolStruct *memPoolInfo, int size) {

	int memKinds = memPoolInfo->memKinds;
	PoolBlockStruct *block = memPoolInfo->block;
	void *p = NULL;

	int i, j, k;

	//搜索内存池,第一个不小于pSize
	i=0;
	j=memKinds-1;
	while(i<=j) {
		k = (i+j)/2;
		if(block[k].pSize > size) {
			j=k-1;
		} else if(block[k].pSize < size) {
			i=k+1;
		} else {
			i=k;
			break;
		}
	}
	k=i;
	while(k<memKinds) {
		p = blockMalloc(&block[k], size);
		if(p) break;
		k++;
	}
	return p;
}

int poolFree(MemPoolStruct *memPoolInfo, void *p) {
	int memKinds = memPoolInfo->memKinds;
	PoolBlockStruct *block = memPoolInfo->block;
	int i, j ,k;
	i = 0;
	j = memKinds-1;
	//第一个小于等于p的地址
	while(i<=j) {
		k=(i+j)/2;
		if((void *)block[k].base > p) {
			j=k-1;
		} else if((void *)block[k].base < p) {
			i=k+1;
		} else {
			j=k;
			break;
		}
	}
	k=j;
	return blockFree(&block[k], p);
}

/*block初始化*/
void blockInit(PoolBlockStruct *block) {

	int pSize = block->pSize;
	int pNum = block->pNum;
	unsigned char *base = block->base;
	unsigned char *pfree = base;
	unsigned char **ppfree;

	int i;
	for(i=0; i<pNum; i++) {
		ppfree = (unsigned char **)pfree;
		pfree = pfree+pSize;
		*ppfree = pfree;
	}
	ppfree=NULL;
}

/*初始化内存池
 * 参数sysInfo:系统信息
 * 参数memPoolInfo:内存池信息
 * 返回值:1成功吗 -1失败
 * */
int memPoolInit(SysInfoStruct *sysInfo, MemPoolStruct *memPoolInfo) {

	int memKinds = M_KINDS;
	int memStart = M_START;

	//各内存池内部块数量
	int pNum[M_KINDS] = {LEN128, LEN256, LEN512, LEN1K, \
			LEN2K, LEN4K, LEN8K, LEN16K, LEN32K, LEN64K,\
			LEN128K, LEN256K, LEN512K, LEN1M, LEN2M, LEN4M};

	PoolBlockStruct *block =  memPoolInfo->block;
	int i;

	//初始化各个内存池block的基地址+poolSize
	block[0].base = sysInfo->memPoolBase;
	block[0].pSize = memStart;
	block[0].pNum = pNum[0];
	block[0].pfree = block[0].base;

	for(i=1; i<memKinds+1; i++) {
		block[i].base = block[i-1].base+block[i-1].pSize*block[i-1].pNum;
		block[i].pSize = block[i-1].pSize*2;
		block[i].pNum = pNum[i];
		block[i].pfree = block[i].base;
	}

	//初始化内存block
	for(i=0; i<memKinds; i++) {
		blockInit(&block[i]);
	}
	memPoolInfo->memPoolLen = block[memKinds].base-block[0].base;
	memPoolInfo->memKinds = memKinds;
	memPoolInfo->memStart = memStart;


	//输出memPool大小
	printf("memPoolSize\t\t%dK\n",memPoolInfo->memPoolLen/(1024));

	if(memPoolInfo->memPoolLen > sysInfo->memPoolLenLimit) {
		printf("error: memPool extends memory Limit!!\n");
		return -1;
	}
	return 1;
}

//查看内存池分配情况
void memTest() {
	MemPoolStruct *info = &gMemPoolStruct;
	PoolBlockStruct *block = info->block;
	int i;
	for(i=0; i<16; i++) {
		printf("block[%d]\tbase=%x\tpSize=%d\tpNum=%d\t\tcurrNum=%d\n",\
				i,block[i].base, block[i].pSize, block[i].pNum, block[i].currNum);
	}
}
