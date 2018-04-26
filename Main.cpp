//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <windows.h>
#include <memory>
#include "Main.h"
#include "IteratorThread.h"
#include <string>
#include <vector>
#include "SearchThread.h"



#include "Main.h"
//---------------------------------------------------------------------------


#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;


using namespace std;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	ResultTree->NodeDataSize = sizeof(findFile);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::SearchButtonClick(TObject *Sender)
{
	ResultTree->Clear();
	Television->Clear();
	LogBox->Items->Add("   ");
	LogBox->Items->Add("------New Search------");
	LogBox->Items->Add("   ");

	myIteratorThread1 =  new IteratorThread(PathEdit->Text, FsType->Text,Start->Text ,End->Text ,false);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::SaveClick(TObject *Sender)
{

	LogBox->Items->Add("Check that stuff");

	vector<wstring> s;
	s.resize(Television->Items->Count);

	FILE *fp = fopen ( "Attributes.txt","w");

	for (int i=0;i<Television->Items->Count; i++)
		{

			s[i]=wstring(Television->Items->Strings[i].c_str());
			fprintf(fp,"%s\n",s[i]);

		}

	fclose(fp);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopButtonClick(TObject *Sender)
{
	Application->MessageBoxW(L"Search Terminated!", L"", MB_OK);

	if (myIteratorThread1 != NULL)
	{
		myIteratorThread1->Terminate();
	}


}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResultTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
if ( !Node )
	{
		MessageBoxW( NULL, L"Ошибка выбора Node", L"Ошибка", MB_OK );
		return;
	}
	findFile * nodeData = ( findFile * )Sender->GetNodeData( Node );
	switch ( Column )
	{
	case 0:
		CellText = nodeData->currentCluster;
		break;
	case 1:
		CellText = nodeData->signature.c_str( );
		break;
	case 2:
		CellText = nodeData->extensionFile.c_str( );
		break;
	}
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
