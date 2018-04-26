//---------------------------------------------------------------------------

#ifndef FileSystemClassH
#define FileSystemClassH

#include <windows.h>
#include "Main.h"
#include <string>
#include <vector>

#include "Patterns.h"

//---------------------------------------------------------------------------

enum FSType
{
	NTFS,
	FAT,
	exFAT
};



class FileSystemClass
{
	public :

		FileSystemClass() {};
		~FileSystemClass() {};

		static FileSystemClass *CreateFileSystem(UnicodeString diskPath,FSType fsType);

		virtual DriveIterator <ClusterDisk> * GetClusterIterator()=0;
		virtual bool ReadBootBlock() =0;
		virtual bool ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer) =0;
		virtual void DestroyFileSystem(HANDLE FileSystemHandle)=0;
		virtual int GetFirstCluster() = 0;
		virtual HANDLE GetFileHandle()=0;
		virtual UINT16 GetBytesPerSector()=0;
		virtual BYTE* GetOEMName()=0;
		virtual BYTE GetSectorPerCluster()=0;
		virtual ULONGLONG GetTotalSectors()=0;
		virtual void SetFileHandle(HANDLE FileSystemHandle)=0;
} ;


#endif
