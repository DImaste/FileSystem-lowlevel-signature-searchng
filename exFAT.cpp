//---------------------------------------------------------------------------

#pragma hdrstop

#include "exFAT.h"
//---------------------------------------------------------------------------


#include "Main.h"
#include <windows.h>

#include "Patterns.h"
#include "FSIterators.h"
#include "FileSystemClass.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

using namespace std;

//---------------------------------------------------------------------------
exFAT_FS::exFAT_FS(UnicodeString diskPath)
{
	fileHandle = CreateFileW(diskPath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
								NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
								);

	if (fileHandle != INVALID_HANDLE_VALUE)
	{
			Form1->LogBox->Items->Add("Opened Successfully");

			result = true;
	}
	else
	{
			Form1->LogBox->Items->Add("Can't open drive");
			result = false;
	}

	BytesPerSector=0;
	SectorPerCluster=0;
	TotalSectors=0;
}

//---------------------------------------------------------------------------

bool exFAT_FS::ReadBootBlock()
{
	BYTE bootSector[512];

	ULONGLONG startOffset = 0;
	LARGE_INTEGER sectorOffset;		// DWORD LowPart, LONG  HighPart, LONGLONG QuadPart
	sectorOffset.QuadPart = startOffset;


	unsigned long currentPosition = SetFilePointer
	(
			fileHandle,
			sectorOffset.LowPart,
			&sectorOffset.HighPart,
			FILE_BEGIN
	);

	if(currentPosition != sectorOffset.LowPart)
	{
			Application->MessageBoxW(L"Dont", L"", MB_OK);
	}

	DWORD bytesToRead = 512;
	DWORD bytesRead;         //already

	bool readResult = ReadFile
	(
			fileHandle,
			bootSector,
			bytesToRead,
			&bytesRead,
			NULL
	);

	if ( !readResult || bytesRead != bytesToRead )
	{
		Application->MessageBoxW(L"ReadMBRError", L"", MB_OK);
		return false;
	}

	infoexFAT = (BOOT_BLOCK_exFAT*)bootSector;

	SectorOfBitmap = infoexFAT->sectorOfBitmap;
	TotalClusters = infoexFAT->countOfCluster;
	BytesPerSector =  (1 << infoexFAT->sizeOfSector);
	SectorPerCluster = (1 << infoexFAT->clusterMlt) ;
	ClusterSize =  BytesPerSector*SectorPerCluster;
	BeginCluster = 0 ;

	strcpy_s(OEMID, strlen(infoexFAT->OEMID )+1, infoexFAT->OEMID);

	return true;
}
//---------------------------------------------------------------------------

ULONGLONG exFAT_FS::GetTotalSectors()
{
	return TotalSectors;
}

//---------------------------------------------------------------------------

BYTE exFAT_FS::GetSectorPerCluster()
{
	return SectorPerCluster;
}

//---------------------------------------------------------------------------

BYTE* exFAT_FS::GetOEMName()
{
	return OEMID;
}

//---------------------------------------------------------------------------

UINT16 exFAT_FS::GetBytesPerSector()
{
	return BytesPerSector;
}

//---------------------------------------------------------------------------

HANDLE exFAT_FS::GetFileHandle()
{
	return fileHandle;
}

//---------------------------------------------------------------------------

void exFAT_FS::SetFileHandle(HANDLE FileSystemHandle)
{
	fileHandle = FileSystemHandle;
}

//---------------------------------------------------------------------------

void exFAT_FS::DestroyFileSystem(HANDLE FileSystemHandle)
{
	CloseHandle(FileSystemHandle);
}

//---------------------------------------------------------------------------

DriveIterator <ClusterDisk> * exFAT_FS::GetClusterIterator()
{
	return new exFATIterator(this);
}

//---------------------------------------------------------------------------

bool exFAT_FS::ReadCluster(ULONGLONG StartCluster, DWORD NumberOfClusters, BYTE *dataBuffer)
{
	ULONGLONG StartOffset = 512 * SectorOfBitmap -
	2 * ClusterSize + ClusterSize * StartCluster;
	DWORD BytesToRead = NumberOfClusters*ClusterSize;
	DWORD BytesRead;
	LARGE_INTEGER SectorOffset;
	SectorOffset.QuadPart = StartOffset;

	unsigned long currentPosition = SetFilePointer
		(
			fileHandle,
			SectorOffset.LowPart,
			&SectorOffset.HighPart,
			FILE_BEGIN
		);
	if(currentPosition != SectorOffset.LowPart)
		{
			Application->MessageBoxW(L"DontCluster", L"", MB_OK);
			return false;
		}

	bool Result = ReadFile(fileHandle, dataBuffer, BytesToRead, &BytesRead, NULL);

	if(!Result || BytesRead != BytesToRead)
		{
			Application->MessageBoxW(L"DontReadClusterRead", L"", MB_OK);
			return false;
		}

	return true;
}

