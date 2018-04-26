//---------------------------------------------------------------------------

#ifndef PatternsH
#define PatternsH
//---------------------------------------------------------------------------
#include <windows.h>

#include <vector>
#include <iostream>


using namespace std;

//---------------------------------------------------------------------------

typedef vector <BYTE> ClusterDisk;

 // Template Iterator

  template <class Type>
class Iterator
{
protected:

public:
	Iterator()  {};
	virtual ~Iterator()  {};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Type GetCurrent() = 0;
} ;

//---------------------------------------------------------------------------


//Iterator Class
template <class Type>
  class DriveIterator : public Iterator <Type>
{
private:

public:
	DriveIterator() {};
	virtual ~DriveIterator() {} ;
	virtual void First()=0;
	virtual void Next()=0;
	virtual bool IsDone() const =0 ;
	virtual Type GetCurrent()=0;
	virtual int GetCurrentIndex() const =0;
} ;

//---------------------------------------------------------------------------
//Decorator Class

class DriveDecorator : public DriveIterator <ClusterDisk>
{
protected:
	int BeginCluster;
	int EndCluster;
	DriveIterator <ClusterDisk> *It;

public:

	DriveDecorator(DriveIterator <ClusterDisk> * it, int beginCluster, int endCluster);

	void First();
	void Next();
	bool IsDone() const ;
	ClusterDisk GetCurrent();
	int GetCurrentIndex() const ;
} ;

//---------------------------------------------------------------------------
#endif
