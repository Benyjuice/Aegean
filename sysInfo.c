/*
 * sysInfo.c
 */

#include "sysInfo.h"

SysInfoStruct gSysInfoStruct;//sysInfo

int sysInfoInit(SysInfoStruct *info, void *memBase, int memLen);

//sysInfo��������
int sysInfoConfig(void *memBase, int memLen) {
	sysInfoInit(&gSysInfoStruct, memBase, memLen);
}

int sysInfoInit(SysInfoStruct *info, void *memBase, int memLen) {

	//ddr��ַ
	unsigned char *ddrBase = (unsigned char *)memBase;
	int ddrLen = memLen;
	//ccs��ַ����
	unsigned char *ccsHoldMemBase = ddrBase;
	int ccsHoldMemLen = CCS_HOLD_MEM_LEN;
	//memPool��ַ����
	unsigned char *memPoolBase = ddrBase+ccsHoldMemLen;
	int memPoolLenLimit = ddrLen-ccsHoldMemLen;
	//�����ַ����
	unsigned char *cacheBase = (unsigned char *)MEM_CACHE_BASE;
	int cacheLen = MEM_CACHE_LEN;

	info->ddrBase = ddrBase;
	info->ddrLen = ddrLen;
	info->ccsHoldMemBase = ccsHoldMemBase;
	info->ccsHoldMemLen = ccsHoldMemLen;
	info->memPoolBase = memPoolBase;
	info->memPoolLenLimit = memPoolLenLimit;
	info->cacheBase = cacheBase;
	info->cacheLen = cacheLen;

	if(ddrLen<=ccsHoldMemLen) return -1;
	return 1;
}
