/*
 * sysInfo.c
 */

#include "sysInfo.h"

SysInfoStruct gSysInfoStruct;//sysInfo

int sysInfoInit(SysInfoStruct *info, void *memBase, int memLen);

//sysInfo整体配置
int sysInfoConfig(void *memBase, int memLen) {
	sysInfoInit(&gSysInfoStruct, memBase, memLen);
}

int sysInfoInit(SysInfoStruct *info, void *memBase, int memLen) {

	//ddr地址
	unsigned char *ddrBase = (unsigned char *)memBase;
	int ddrLen = memLen;
	//ccs地址计算
	unsigned char *ccsHoldMemBase = ddrBase;
	int ccsHoldMemLen = CCS_HOLD_MEM_LEN;
	//memPool地址计算
	unsigned char *memPoolBase = ddrBase+ccsHoldMemLen;
	int memPoolLenLimit = ddrLen-ccsHoldMemLen;
	//缓存地址计算
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
