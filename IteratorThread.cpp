//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include <windows.h>
#include "IteratorThread.h"
#include "Patterns.h"
#include <iostream>
#include <map>
#include "FileSystemClass.h"

using namespace std;
#pragma package(smart_init)

__fastcall IteratorThread::IteratorThread(UnicodeString filePath, UnicodeString fsType,
UnicodeString startCluster, UnicodeString endCluster, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	Path= filePath;
	StringTypeFs=fsType;
	StartCluster = startCluster;
	EndCluster = endCluster;
}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	  FSType StructTypeFs;

	  map <UnicodeString, FSType> mapper;

	  if (mapper.count(StringTypeFs))
	  {
		  StructTypeFs =  mapper[StringTypeFs] ;
      }

	  FileSystemClass *mydisk = FileSystemClass::CreateFileSystem(Path ,StructTypeFs);
	  FileSystemHandle = mydisk->GetFileHandle();

	  int BytesPerCluster;
	  int TotalClusters;

			Form1->LogBox->Items->Add("Ok");

			mydisk->SetFileHandle(FileSystemHandle);

			if (FileSystemHandle == 0)
			{
				Application->MessageBoxW(L"Handle Lost", L"", MB_OK);
			}

			if (mydisk->ReadBootBlock())
			{
				TotalClusters = mydisk->GetTotalSectors() / mydisk->GetSectorPerCluster( );
				BytesPerCluster = mydisk->GetBytesPerSector() * mydisk->GetSectorPerCluster( );
				int TotalSectors  = mydisk->GetTotalSectors();
				int BytesPerSector = mydisk->GetBytesPerSector();


				Form1->Television->Items->Add("Sector Size = "+ IntToStr(BytesPerSector)+" Bytes" );
				Form1->Television->Items->Add("Total Sectors = "+ IntToStr(TotalSectors));
				Form1->Television->Items->Add("Cluster Size = "+ IntToStr(BytesPerCluster)+" Bytes");
				Form1->Television->Items->Add("Total Clusters = "+ IntToStr(TotalClusters));

				Form1->LogBox->Items->Add("Read Boot Record successfully!");
			}
			else
			{
				Form1->LogBox->Items->Add("Read Boot Record Error!");
			}

	__int64 BeginClusterInt=0;
	__int64 LastClusterInt=0;

	if  (EndCluster=="end" && StartCluster=="start")
	{
		BeginClusterInt = mydisk->GetFirstCluster();
		LastClusterInt = TotalClusters;
	}

	if  (EndCluster!="end" && StartCluster=="start")
	{
		BeginClusterInt = mydisk->GetFirstCluster();
		LastClusterInt = StrToInt(EndCluster);
	}

	if  (EndCluster=="end" && StartCluster!="start")
	{
		BeginClusterInt = StrToInt(StartCluster);
		LastClusterInt = TotalClusters;
	}

	if  (EndCluster!="end" && StartCluster!="start")
	{
		BeginClusterInt = StrToInt(StartCluster);
		LastClusterInt = StrToInt(EndCluster);
	}

	if (BeginClusterInt > LastClusterInt)
	{
		MessageBoxW( NULL, L"Конечный кластер не может быть больше начального", L"Ошибка", MB_OK );
		return;
	}

	int clusterSize = BytesPerCluster;
	BYTE *dataBuffer = new BYTE[clusterSize];

	DriveIterator <ClusterDisk> *It = mydisk->GetClusterIterator();

	DriveIterator <ClusterDisk> *Dec = new DriveDecorator( It, BeginClusterInt, LastClusterInt );

	ClusterDisk CurrentCluster;
	MySearchThread1 = new SearchThread( &CurrentCluster, clusterSize, false, LastClusterInt );


		for (Dec->First(); !Dec->IsDone(); Dec->Next())
			{
				CurrentCluster = Dec->GetCurrent();
				MySearchThread1->BufferReadyEvent->SetEvent();

				while(MySearchThread1->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled)
				{
				}

				MySearchThread1->SetCurrentCluster(Dec->GetCurrentIndex());

				MySearchThread1->BufferCopiedEvent->ResetEvent();

				if ( Terminated )
				{
					break;
				}
			}

	Form1->LogBox->Items->Add("Read Clusters succesfully!");

	MySearchThread1->Terminate();

	mydisk->DestroyFileSystem(FileSystemHandle);

	//delete[] dataBuffer;
	delete mydisk;
   //	delete[] Dec; //decorator
	//delete[] It;  //iterator

}
//---------------------------------------------------------------------------


