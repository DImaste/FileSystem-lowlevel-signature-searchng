//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------

#include "Patterns.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)


// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

// Decorator realization

DriveDecorator::DriveDecorator(DriveIterator <ClusterDisk> * it, int beginCluster, int endCluster)
{
	It= it;
	BeginCluster = beginCluster;
	EndCluster = endCluster;
}

// ------------------------------------------------------------------------------

void DriveDecorator::First()
{
	for (It->First(); !It->IsDone(); It->Next())
	{
		if (It->GetCurrentIndex() == BeginCluster)
		{
			break;
		}
	}
}

// ------------------------------------------------------------------------------

void DriveDecorator::Next()
{
	It->Next( );
}

// ------------------------------------------------------------------------------

bool DriveDecorator::IsDone() const
{
	if (It->GetCurrentIndex() > EndCluster || It->IsDone())
	{
		return true;
	}
	else
	{
		return It->IsDone();
	}
}

// ------------------------------------------------------------------------------

ClusterDisk DriveDecorator::GetCurrent()
{
	return It->GetCurrent();
}

// ------------------------------------------------------------------------------

int DriveDecorator::GetCurrentIndex() const
{
	return It->GetCurrentIndex();
}

// ------------------------------------------------------------------------------
