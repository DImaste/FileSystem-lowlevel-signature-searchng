//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "SearchThread.h"
#include "string"
//---------------------------------------------------------------------------


class IteratorThread : public TThread
{
private:

	HANDLE FileSystemHandle;
	SearchThread *MySearchThread1;

protected:
	void __fastcall Execute();
	UnicodeString Path;
	UnicodeString StringTypeFs;
	UnicodeString StartCluster;
	UnicodeString EndCluster;

	vector <BYTE> CurrentCluster;

public:

	__fastcall IteratorThread(UnicodeString filePath, UnicodeString fsType,
	UnicodeString startCluster,UnicodeString endCluster, bool CreateSuspended);

};
//---------------------------------------------------------------------------
#endif
