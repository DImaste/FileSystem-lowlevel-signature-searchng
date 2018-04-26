//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystemClass.h"
#include <string>

#include "NTFS.h"
#include "FAT.h"
#include "exFAT.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

FileSystemClass *FileSystemClass::CreateFileSystem(UnicodeString diskPath,FSType fsType)
{
	FileSystemClass * FS;

	switch (fsType)
	{
			case NTFS: FS = new NTFS_FS(diskPath);
				break;
			case FAT: FS = new FAT_FS(diskPath);
				break;
			case exFAT: FS = new exFAT_FS(diskPath);
				break;
			default: FS = NULL;
				break;
	}

	return FS;
}








