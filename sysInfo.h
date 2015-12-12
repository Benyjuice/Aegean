/*
 * sysInfo.h
 */

#ifndef SYSINFO_H_
#define SYSINFO_H_

#define  DDR_BASE					(0xC0000000)	//物理内存地址
#define  DDR_LEN					(0x08000000)	//物理内存大小128M
#define  CCS_HOLD_MEM_LEN			(0x0)	//给编译器分配内存16M
#define  MEM_CACHE_BASE				(0x11800000)	//cache
#define  MEM_CACHE_LEN				(0x00040000)	//cache长度

typedef struct _SysInfoStruct {

	 /*硬件信息-物理地址*/
	 /*unsigned char类型容易操作*/
	unsigned char *ddrBase;
	unsigned char *ccsHoldMemBase;
	unsigned char *memPoolBase;
	unsigned char *cacheBase;
	int ddrLen;
	int ccsHoldMemLen;
	int memPoolLenLimit;
	int cacheLen;

}SysInfoStruct;

extern SysInfoStruct gSysInfoStruct;//sysInfo

int sysInfoConfig(void *memBase, int memLen);

#endif /* SYSINFO_H_ */
