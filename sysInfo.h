/*
 * sysInfo.h
 */

#ifndef SYSINFO_H_
#define SYSINFO_H_

#define  DDR_BASE					(0xC0000000)	//�����ڴ��ַ
#define  DDR_LEN					(0x08000000)	//�����ڴ��С128M
#define  CCS_HOLD_MEM_LEN			(0x0)	//�������������ڴ�16M
#define  MEM_CACHE_BASE				(0x11800000)	//cache
#define  MEM_CACHE_LEN				(0x00040000)	//cache����

typedef struct _SysInfoStruct {

	 /*Ӳ����Ϣ-�����ַ*/
	 /*unsigned char�������ײ���*/
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
