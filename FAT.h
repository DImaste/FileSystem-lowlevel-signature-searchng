//---------------------------------------------------------------------------

#ifndef FATH
#define FATH
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
	UINT16 bytesPerSector;
	BYTE sectorPerClusterMlt;
	UINT16 reservedArea;
	BYTE countOfCopiesFAT;
	UINT16 maxCountOfFiles;
	UINT16 countOfSectors16;
	BYTE typeOfStore;
	UINT16 sizeOfCopiesFAT16;
	UINT16 sectorPerTrack;
	UINT16 countOfHeads;
	UINT32 sectorsBeforePartition;
	UINT32 countOfSectors32;
	BYTE numberDiskBIOS;
	BYTE padding;
	BYTE extSignature;
	UINT32 numberOfVolume;
	BYTE markOfVolume[ 11 ];
	BYTE markOfTypeFS[ 8 ];
	BYTE padding2[ 448 ];
	BYTE siganture[ 2 ];

}BOOT_BLOCK_FAT;

#pragma pack(pop)

 class FAT_FS : public FileSystemClass
{

protected:
	HANDLE fileHandle;
	UINT16 BytesPerSector;
	BYTE SectorPerCluster;
	ULONGLONG TotalSectors;
	UINT16 ClusterSize;
	ULONGLONG TotalClusters;

	BYTE OEMID[9];
	WCHAR* path;

    UINT32 BytesPerReservedArea;
	UINT32 BytesPerCopiesFAT;
	UINT32 BytesPerRootDirectory;

private:

	BOOT_BLOCK_FAT* infoFAT;
   //	int ClusterSize;
	__int64 Size;

public:
	FAT_FS(UnicodeString diskPath);
	void DestroyFileSystem(HANDLE FileSystemHandle);

	DriveIterator <ClusterDisk> *GetClusterIterator();

	UINT32 BeginCluster;
	bool result;
	int GetFirstCluster() {return 2;};
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


