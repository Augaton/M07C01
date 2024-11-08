//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	TrackBar1->Enabled = false;
	TrackBar2->Enabled = false;
	TrackBar3->Enabled = false;

	Button1->Enabled = false;
	Button2->Enabled = false;
	Button3->Enabled = false;
	Button4->Enabled = false;
	Button5->Enabled = false;
	Button6->Enabled = false;
	Button7->Enabled = false;
	Button8->Enabled = false;
	Button10->Enabled = false;
	Button11->Enabled = false;

	Image1->Top = (Bevel2->Height + Bevel2->Top) - (Bevel2->Height / 2 + Image1->Height/2);
	Image1->Left = (Bevel2->Width + Bevel2->Left) - (Bevel2->Width / 2 + Image1->Height/2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
	Label2 ->Caption = AnsiString( (TrackBar3->Position) * 10 ) + " cm/s";
	drone->Avant( (TrackBar3->Position) * 10 );
	Label4->Caption = "forward " + AnsiString( (TrackBar3->Position) * 10 );

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button9Click(TObject *Sender)
{
	/*
	if (drone) {
		throw drone;
	}
	*/

	drone = new TelloClientUDP(AnsiString(Edit1->Text).c_str());
	Label4->Caption = "command";
	drone->ModeCommande();

    // activation bouton
	TrackBar1->Enabled = true;
	TrackBar2->Enabled = true;
	TrackBar3->Enabled = true;

	Button1->Enabled = true;
	Button2->Enabled = true;
	Button3->Enabled = true;
	Button4->Enabled = true;
	Button5->Enabled = true;
	Button6->Enabled = true;
	Button7->Enabled = true;
	Button8->Enabled = true;
	Button10->Enabled = true;
	Button11->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Label4->Caption = "takeoff";
	drone->Decoller();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Label4->Caption = "land";
	drone->Atterir();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	Label3 ->Caption = AnsiString( (TrackBar1->Position) * 25 ) + " cm";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	drone->Monter( (TrackBar1->Position) * 25 );
	Label4->Caption = "up " + AnsiString( (TrackBar1->Position) * 25 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
	drone->Descendre( (TrackBar1->Position) * 25 );
	Label4->Caption = "down " + AnsiString( (TrackBar1->Position) * 25 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
	Label1->Caption = AnsiString( (TrackBar2->Position) * 30 ) + " deg";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button10Click(TObject *Sender)
{
 	drone->TournerTrigo( (TrackBar2->Position) * 30 );
	Label4->Caption = "cw " + AnsiString( (TrackBar2->Position) * 30 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
	drone->TournerHoraire( (TrackBar2->Position) * 30 );
	Label4->Caption = "ccw " + AnsiString( (TrackBar2->Position) * 30 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	drone->Avant( (TrackBar1->Position) * 25 );
	Label4->Caption = "forward " + AnsiString( (TrackBar1->Position) * 25 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	drone->Droite( (TrackBar1->Position) * 25 );
	Label4->Caption = "right " + AnsiString( (TrackBar1->Position) * 25 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	drone->Arriere( (TrackBar1->Position) * 25 );
	Label4->Caption = "back " + AnsiString( (TrackBar1->Position) * 25 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	drone->Gauche( (TrackBar1->Position) * 25 );
	Label4->Caption = "left " + AnsiString( (TrackBar1->Position) * 25 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	int haut = Image1->Top + Y - Image1->Height/2;
	int gauche = Image1->Left + X - Image1->Width/2;

	if (TrackBar3->Enabled == false) {
        return;
	}

	if (click == true && gauche>Bevel2->Left
					  && haut>Bevel2->Top
					  && gauche+Image1->Width < Bevel2->Left+Bevel2->Width
					  && haut+Image1->Height < Bevel2->Top+Bevel2->Height) {
		Image1->Top = haut;
		Image1->Left = gauche;

		int formulahaut = ((haut - 81) - Bevel2->Height / 2 + Image1->Height/2) * 10;
		int formulagauche = ((gauche - 282) - Bevel2->Width / 2 + Image1->Height/2) * 10;

		if (formulahaut > 500) {
			Label5->Caption = 500;
		}
		else if (formulahaut < -500)
		{
			Label5->Caption = -500;
		}
		else
		{
			Label5->Caption = formulahaut;
		}

		if (formulagauche > 500) {
			Label6->Caption = 500;
		}
		else if (formulagauche < -500)
		{
			Label6->Caption = -500;
		}
		else
		{
			Label6->Caption = formulagauche;
		}



	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if (TrackBar3->Enabled == false && TrackBar1->Enabled == false) {
        return;
	}

	click = false;

	int haut = Image1->Top + Y - Image1->Height/2;
	int gauche = Image1->Left + X - Image1->Width/2;

	Image1->Top = (Bevel2->Height + Bevel2->Top) - (Bevel2->Height / 2 + Image1->Height/2);
	Image1->Left = (Bevel2->Width + Bevel2->Left) - (Bevel2->Width / 2 + Image1->Height/2);

	int formulahaut = ((haut - 81) - Bevel2->Height / 2 + Image1->Height/2) * 10;
	int formulagauche = ((gauche - 282) - Bevel2->Width / 2 + Image1->Height/2) * 10;

	int GotoX, GotoY, GotoZ;

	if (formulahaut > 500) {
		GotoX = 500;
	}
	else if (formulahaut < -500)
	{
		GotoX = -500;
	}
	else
	{
		GotoX = formulahaut;
	}

	if (formulagauche > 500) {
		GotoY = 500;
	}
	else if (formulagauche < -500)
	{
		GotoY = -500;
	}
	else
	{
		GotoY = formulagauche;
	}

	GotoZ = (TrackBar1->Position) * 25;

	drone->DeplacerXYZ(GotoX,GotoY,GotoZ, (TrackBar3->Position) * 10);
	Label4->Caption = "goto " + AnsiString( GotoX ) + " " + AnsiString( GotoY ) + " " + AnsiString( GotoZ ) + " " + AnsiString( (TrackBar3->Position) * 10 );


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	click = true;
}
//---------------------------------------------------------------------------


