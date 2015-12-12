/*
 * memPool.h
 */
#ifndef MEMPOOL_H_
#define MEMPOOL_H_

#include "sysInfo.h"

//内存池长度
#define K			(1024)
#define M_KINDS		(16)
#define M_START		(128)
#define LEN128		(0)
#define LEN256		(0)
#define LEN512		(0)
#define LEN1K		(0)
#define LEN2K		(0)
#define LEN4K		(10)
#define LEN8K		(20)
#define LEN16K		(0)
#define LEN32K		(0)
#define LEN64K		(0)
#define LEN128K		(0)
#define LEN256K		(0)
#define LEN512K		(20)
#define LEN1M		(0)
#define LEN2M		(0)
#define LEN4M		(0)

////内存池长度
//#define K			(1024)
//#define M_KINDS		(16)
//#define M_START		(128)
//#define LEN128		(32*K)
//#define LEN256		(16*K)
//#define LEN512		(8*K)
//#define LEN1K		(4*K)
//#define LEN2K		(2*K)
//#define LEN4K		(2*K)
//#define LEN8K		(1*K)
//#define LEN16K		(512)
//#define LEN32K		(512)
//#define LEN64K		(256)
//#define LEN128K		(32)
//#define LEN256K		(16)
//#define LEN512K		(8)
//#define LEN1M		(8)
//#define LEN2M		(4)
//#define LEN4M		(2)

typedef struct _PoolBlockStruct{
	//块基地址
	unsigned char *base;
	/*page单元大小*/
	int pSize;
	//多少page
	int pNum;
	//当前分配了多少块
	int currNum;
	//指针
	unsigned char *pfree;

}PoolBlockStruct;

//内存池
typedef struct _MemPoolStruct {

	//内存池总长度，计算出来的
	int memPoolLen;
	//内存种类128-4M 16种
	int memKinds;
	//开始的单元128
	int memStart;
	//内存池
	PoolBlockStruct block[M_KINDS];

}MemPoolStruct;

extern MemPoolStruct gMemPoolStruct;

void memPoolConfig();
void *dspMalloc(int size);
int dspFree(void *p);
void memTest();

#endif /* MEMPOOL_H_ */

