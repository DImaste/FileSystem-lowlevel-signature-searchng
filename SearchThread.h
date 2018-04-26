//---------------------------------------------------------------------------

#ifndef SearchThreadH
#define SearchThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <string>
#include <vector>
#include <list>

using namespace std;


typedef struct
{
	string signature;
	string extensionFile;

} nodeSignature;

typedef struct
{
	__int64 currentCluster;
	string signature;
	string extensionFile;
} findFile;

const int WaitDelayMs = 200;
const int NumSignatures = 3;
const nodeSignature signatures[ NumSignatures ] =
{

	{
		"\xff\xfb",
		".mp3"
	} ,
	{
		"\x49\x44\x33",
		".mp3"
	} ,
	{
		"\x37\x7a\xbc\xaf\x27\x1c",
		".7z"
	}

} ;
const vector < nodeSignature > vSignature(
				 signatures,
	signatures + NumSignatures );

// ---------------------------------------------------------------------------
class SearchThread : public TThread
{
private:
	int BytesPerCluster;
	const vector < BYTE > *OutBufferPtr;
	BYTE * DataBuffer;
	int CurrentCluster;
	string CurrentSignature;
	string CurrentExtensionFile;
	__int64 point;


	void CopyData( );
	void SearchData( );
	void __fastcall AddMatch( );
	void __fastcall CompleteSearch( );

protected:
	void __fastcall Execute( );

public:
	__fastcall SearchThread(
		const vector < BYTE > * dataBufferPtr,
		int                     clusterSize,
		bool                    CreateSuspended, int clusterscount );
	void SetCurrentCluster( int curCluster );

	// События, используемые для синхронизации
	TEvent * BufferReadyEvent;
	TEvent * BufferCopiedEvent;

} ;



















/*
//---------------------------------------------------------------------------
const int WaitDelayMs = 2000;
//---------------------------------------------------------------------------

typedef struct
{
	__int64 currentCluster;
	BYTE signature[4];
	BYTE extensionFile[4];
} FileTree;


class SearchThread : public TThread
{
private:
	int ClusterSize;
	const vector < BYTE > *OutBufferPtr;
	BYTE *DataBuffer;
	int CurrentCluster;
	BYTE signature[5];
	BYTE extensionFile[5];
	__int64 point;


	void CopyData();
	void SearchData();
	void __fastcall AddMatch();
	void __fastcall CompleteSearch();


protected:
	void __fastcall Execute();

	//vectors
	vector<const char *> signatures;
	vector<int> sign_size;
	vector<const char *> sign_name;






public:
   //	__fastcall SearchThread(BYTE *dataBufferPtr, int clusterSize, bool CreateSuspended, int clusterscount);
	 void SetCurrentCluster(int Cluster);
	__fastcall SearchThread(const vector <BYTE> *dataBufferPtr,int clusterSize,bool CreateSuspended, int clusterscount );

	// События, используемые для синхронизации
	TEvent *BufferReadyEvent;
	TEvent *BufferCopiedEvent;



};   */
//---------------------------------------------------------------------------
#endif


