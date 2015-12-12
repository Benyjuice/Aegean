/*
 * memPool.h
 */
#ifndef MEMPOOL_H_
#define MEMPOOL_H_

#include "sysInfo.h"

//�ڴ�س���
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

////�ڴ�س���
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
	//�����ַ
	unsigned char *base;
	/*page��Ԫ��С*/
	int pSize;
	//����page
	int pNum;
	//��ǰ�����˶��ٿ�
	int currNum;
	//ָ��
	unsigned char *pfree;

}PoolBlockStruct;

//�ڴ��
typedef struct _MemPoolStruct {

	//�ڴ���ܳ��ȣ����������
	int memPoolLen;
	//�ڴ�����128-4M 16��
	int memKinds;
	//��ʼ�ĵ�Ԫ128
	int memStart;
	//�ڴ��
	PoolBlockStruct block[M_KINDS];

}MemPoolStruct;

extern MemPoolStruct gMemPoolStruct;

void memPoolConfig();
void *dspMalloc(int size);
int dspFree(void *p);
void memTest();

#endif /* MEMPOOL_H_ */

