
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "SearchThread.h"
#include "IteratorThread.h"
#include "Main.h"
#include <string>
#include <vector>
#include <list>

using namespace std;

#pragma package(smart_init)

__fastcall SearchThread::SearchThread(const vector <BYTE> * dataBufferPtr,int bytesPerCluster,bool CreateSuspended, int clusterscount ) :TThread(CreateSuspended )
{
	FreeOnTerminate = true;

	BufferReadyEvent = new TEvent( NULL, true, false, "", false );
	BufferCopiedEvent = new TEvent( NULL, true, false, "", false );
	CurrentCluster = 0;
	BytesPerCluster = bytesPerCluster;
	OutBufferPtr = dataBufferPtr;
	DataBuffer = new BYTE[ bytesPerCluster ];
	point = 1;
	Form1->Progress->Max = clusterscount;
}

// ---------------------------------------------------------------------------
void __fastcall SearchThread::Execute( )
{

	while ( true )
	{

		if ( BufferReadyEvent->WaitFor( WaitDelayMs ) == wrSignaled )
		{

			CopyData( );


			BufferReadyEvent->ResetEvent( );
			BufferCopiedEvent->SetEvent( );

			// Запустить поиск
			SearchData( );
            Form1->Progress->Position = point;
			point++;
		}
		if ( Terminated )
		{
			break;
		}
	}
	// Удалить события
	delete BufferReadyEvent;
	delete BufferCopiedEvent;

	// Удалить буфер
	delete[ ]DataBuffer;
	Synchronize( & CompleteSearch );

}

// ---------------------------------------------------------------------------
void SearchThread::CopyData( )
{
	copy( OutBufferPtr->begin( ), OutBufferPtr->end( ), DataBuffer );
}

// ---------------------------------------------------------------------------
void SearchThread::SearchData( )
{
	// Провести поиск
	for ( int i = 0; i < vSignature.size( ); i++ )
	{
		if ( memcmp( DataBuffer, vSignature[ i ].signature.c_str( ), vSignature[ i ].signature.length( ) ) == 0 )
		{
			CurrentSignature = vSignature[ i ].signature;
			CurrentExtensionFile = vSignature[ i ].extensionFile;
			Synchronize( & AddMatch );
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall SearchThread::AddMatch( )
{
	PVirtualNode newNode = Form1->ResultTree->AddChild( Form1->ResultTree->RootNode );
	findFile * nodeData = ( findFile * )Form1->ResultTree->GetNodeData( newNode );
	nodeData->currentCluster = CurrentCluster;
	nodeData->signature = CurrentSignature;
	nodeData->extensionFile = CurrentExtensionFile;

}

// ---------------------------------------------------------------------------
void __fastcall SearchThread::CompleteSearch( )
{
	Application->MessageBoxW( L" Поиск завершен или остановлен !", L" Успешно ", MB_OK );
}
// ----------------------------------------------------------------------------

void SearchThread::SetCurrentCluster( int currentCluster )
{
	CurrentCluster = currentCluster;
}
// ---------------------------------------------------------------------------





































/*
__fastcall SearchThread::SearchThread(const vector <BYTE> *dataBufferPtr, int clusterSize, bool CreateSuspended, int clusterscount) : TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	Form1->Progress->Max = clusterscount;
	point = 1;

	BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	BufferCopiedEvent = new TEvent(NULL, true, false,"",false);

	CurrentCluster = 0;
	ClusterSize = clusterSize;
	OutBufferPtr = dataBufferPtr;
	DataBuffer = new BYTE[clusterSize];

   signatures.push_back("\x49\x44\x33"); //mp3
   signatures.push_back("\x21\x3C\x61\x72\x63\x68\x3E"); //deb
   signatures.push_back("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"); //png    89 50 4E 47 0D 0A 1A 0A
   signatures.push_back("\x37\x7A\xBC\xAF\x27\x1C"); //7zip    37 7A BC AF 27 1C

   sign_size.push_back(3);
   sign_size.push_back(7);
   sign_size.push_back(8);
   sign_size.push_back(6);

   sign_name.push_back(".mp3");
   sign_name.push_back(".deb");
   sign_name.push_back(".png");
   sign_name.push_back(".7z ");


}
//---------------------------------------------------------------------------
void __fastcall SearchThread::Execute()
{
	while(true)
	{
		if(BufferReadyEvent->WaitFor(WaitDelayMs) == wrSignaled)
		{
			if(true)
			{
				CopyData();

				BufferReadyEvent->ResetEvent();
				BufferCopiedEvent->SetEvent();

				SearchData();
				Form1->Progress->Position = point;
				point++;
			}
		}
		if(Terminated) break;
	}
	// Удалить события
	delete BufferReadyEvent;
	delete BufferCopiedEvent;
	//delete BufferAccessCS;

  // Удалить буфер
	delete[] DataBuffer;
	Synchronize(&CompleteSearch);
}
//---------------------------------------------------------------------------

void SearchThread::SetCurrentCluster(int Cluster)
 {
	CurrentCluster = Cluster;
 }


//---------------------------------------------------------------------------
void SearchThread::CopyData()
{
	 copy(OutBufferPtr->begin(), OutBufferPtr->end(), DataBuffer);
}

//---------------------------------------------------------------------------
void SearchThread::SearchData()
{
   for (int i=0; i<signatures.size();i++)
	{
		 if ( memcmp( DataBuffer, signatures[i], sign_size[i]) == 0 )
		{
			memcpy( signature, signatures[i], sign_size[i]);
			memcpy( extensionFile, sign_name[i], 4 );
			Synchronize(&AddMatch );
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::AddMatch()
{
	PVirtualNode newNode = Form1->ResultTree->AddChild(Form1->ResultTree->RootNode);
	FileTree* nodeData = (FileTree*)Form1->ResultTree->GetNodeData(newNode);
	nodeData-> currentCluster = CurrentCluster;
	memcpy(nodeData->signature, signature, 3);
	memcpy(nodeData->extensionFile, extensionFile, 3);
}


//---------------------------------------------------------------------------
void __fastcall SearchThread::CompleteSearch()
{
	Application->MessageBoxW(L"Поиск завершен!", L"", MB_OK);
}

*/
