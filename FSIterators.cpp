//---------------------------------------------------------------------------

#pragma hdrstop

#include "FSIterators.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//NTFS Iterator

 NTFSIterator::NTFSIterator(NTFS_FS *fs)
{
   FileSystem = fs;
   CurrentCluster = FileSystem->GetFirstCluster();
   BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
   DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void NTFSIterator::First()
{
	CurrentCluster = FileSystem->GetFirstCluster();
}

// ------------------------------------------------------------------------------
void NTFSIterator::Next()
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool NTFSIterator::IsDone() const
{
	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	return (CurrentCluster >= TotalClusters);
}

// ------------------------------------------------------------------------------
ClusterDisk NTFSIterator::GetCurrent()
{
	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	return Cluster;
}

// ------------------------------------------------------------------------------
NTFSIterator::~NTFSIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

int NTFSIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

//FAT Iterator

 FATIterator::FATIterator(FAT_FS *fs)
{
   FileSystem = fs;
   CurrentCluster = FileSystem->GetFirstCluster();
   BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
   DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void FATIterator::First()
{
	CurrentCluster = FileSystem->GetFirstCluster();
}

// ------------------------------------------------------------------------------
void FATIterator::Next()
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool FATIterator::IsDone() const
{
	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	return (CurrentCluster >= TotalClusters);
}

// ------------------------------------------------------------------------------
ClusterDisk FATIterator::GetCurrent()
{
	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	return Cluster;
}

// ------------------------------------------------------------------------------
FATIterator::~FATIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

int FATIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

//exFAT Iterator

 exFATIterator::exFATIterator(exFAT_FS *fs)
{
   FileSystem = fs;
   CurrentCluster = FileSystem->GetFirstCluster();
   BytesPerCluster = FileSystem->GetBytesPerSector() * FileSystem->GetSectorPerCluster();
   DataBuffer = new BYTE[ BytesPerCluster ];
}

// ------------------------------------------------------------------------------
void exFATIterator::First()
{
	CurrentCluster = FileSystem->GetFirstCluster();
}

// ------------------------------------------------------------------------------
void exFATIterator::Next()
{
	CurrentCluster++ ;
}

// ------------------------------------------------------------------------------
bool exFATIterator::IsDone() const
{
	int TotalClusters = FileSystem->GetTotalSectors() / FileSystem->GetSectorPerCluster();
	return (CurrentCluster >= TotalClusters);
}

// ------------------------------------------------------------------------------
ClusterDisk exFATIterator::GetCurrent()
{
	FileSystem->ReadCluster(CurrentCluster, 1, DataBuffer);
	Cluster.assign(DataBuffer, DataBuffer + BytesPerCluster);
	return Cluster;
}

// ------------------------------------------------------------------------------
exFATIterator::~exFATIterator()
{
	delete[ ] DataBuffer;
}

// ------------------------------------------------------------------------------

int exFATIterator::GetCurrentIndex() const
{
	return CurrentCluster;
}