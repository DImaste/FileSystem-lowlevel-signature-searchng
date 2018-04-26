//---------------------------------------------------------------------------

#ifndef FSIteratorsH
#define FSIteratorsH


#include "NTFS.h"
#include "FAT.h"
#include "exFAT.h"
#include "Patterns.h"
//---------------------------------------------------------------------------

class NTFSIterator : public DriveIterator <ClusterDisk>
{
private:
	NTFS_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	NTFSIterator(NTFS_FS *fs);
	~NTFSIterator();
	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;

//---------------------------------------------------------------------------

class FATIterator : public DriveIterator <ClusterDisk>
{
private:
	FAT_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	FATIterator(FAT_FS *fs);
	~FATIterator();
	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;

//---------------------------------------------------------------------------

class exFATIterator : public DriveIterator <ClusterDisk>
{
private:
	exFAT_FS * FileSystem;
	ClusterDisk Cluster;
	int CurrentCluster;
	int BytesPerCluster;
	BYTE * DataBuffer;

public:
	exFATIterator(exFAT_FS *fs);
	~exFATIterator();
	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;


#endif
