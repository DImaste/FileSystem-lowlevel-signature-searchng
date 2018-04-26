//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "IteratorThread.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *PathEdit;
	TVirtualStringTree *ResultTree;
	TButton *SearchButton;
	TListBox *Television;
	TLabeledEdit *Start;
	TListBox *LogBox;
	TButton *Save;
	TButton *StopButton;
	TProgressBar *Progress;
	TLabeledEdit *End;
	TComboBox *FsType;
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall SaveClick(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall ResultTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column,
          TVSTTextType TextType, UnicodeString &CellText);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	IteratorThread *myIteratorThread1;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
