//---------------------------------------------------------------------------

#ifndef NTFSH
#define NTFSH

//---------------------------------------------------------------------------


#include <windows.h>
#include <string>
#include <vector>

#include "Patterns.h"
#include "FileSystemClass.h"


#pragma pack(push,1)

typedef vector <BYTE> ClusterDisk;

typedef struct
{
	BYTE Jump[3];
	BYTE OEMID[8];
	UINT16 BytesPerSector;
	BYTE SectorsPerCluster;
	BYTE padding1[2];
	BYTE padding2[5];
	BYTE typeStore;
	BYTE padding3[2];
	BYTE padding4[8];
	BYTE padding5[4];
	BYTE padding6[4];
	ULONGLONG TotalSectors;
	ULONGLONG MftStartLcn;
	ULONGLONG Mft2StartLcn;
	BYTE sizeMFT;
	BYTE padding7[3];
	BYTE sizeIndex;
	BYTE padding8[3];
	ULONGLONG VolumeSerialNumber;
	BYTE padding9[ 4 ];
	BYTE padding10[ 426 ];
	BYTE Checksum[ 2 ];

}BOOT_BLOCK_NTFS;

#pragma pack(pop)

 class NTFS_FS : public FileSystemClass
{

protected:
	HANDLE fileHandle;
	UINT16 BytesPerSector;
	BYTE SectorPerCluster;
	ULONGLONG TotalSectors;
	BYTE OEMID[9];
	WCHAR* path;


private:

	BOOT_BLOCK_NTFS* infoNTFS;
	int ClusterSize;
	__int64 Size;

public:
	NTFS_FS(UnicodeString diskPath);
	void DestroyFileSystem(HANDLE FileSystemHandle);

	DriveIterator <ClusterDisk> *GetClusterIterator();

	int GetFirstCluster() {return 0;};
	bool result;
	bool ReadBootBlock();
	bool ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer);
	HANDLE GetFileHandle();
	UINT16 GetBytesPerSector();
	BYTE* GetOEMName();
	BYTE GetSectorPerCluster();
	ULONGLONG GetTotalSectors();
	void SetFileHandle(HANDLE FileSystemHandle);

};
#endif










