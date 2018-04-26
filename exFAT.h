//---------------------------------------------------------------------------

#ifndef exFATH
#define exFATH

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
	BYTE machInstruction[ 3 ];
	BYTE OEMID[ 8 ];
	BYTE padding[ 61 ];
	ULONGLONG countOfSectors;
	UINT32 sectorOfFAT;
	UINT32 sizeOfFAT;
	UINT32 sectorOfBitmap;
	UINT32 countOfCluster;
	UINT32 clusterOfRoot;
	UINT32 numberOfVolume;
	BYTE padding2[ 4 ];
	BYTE sizeOfSector;
	BYTE clusterMlt;
	BYTE padding3[ 400 ];
	BYTE signature[ 2 ];

}BOOT_BLOCK_exFAT;

#pragma pack(pop)

 class exFAT_FS : public FileSystemClass
{

protected:
	HANDLE fileHandle;
	UINT16 BytesPerSector;
	BYTE SectorPerCluster;
	ULONGLONG TotalSectors;
	BYTE OEMID[9];
	WCHAR* path;
    UINT16 ClusterSize;
	ULONGLONG TotalClusters;

	UINT32 SectorOfBitmap;

private:

	BOOT_BLOCK_exFAT* infoexFAT;
	//int ClusterSize;
	__int64 Size;

public:
	exFAT_FS(UnicodeString diskPath);

	void DestroyFileSystem(HANDLE FileSystemHandle);

	DriveIterator <ClusterDisk> *GetClusterIterator();

	UINT32 BeginCluster;
	bool result;
	int GetFirstCluster() {return 0;};
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
