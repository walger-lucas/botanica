#include "ListaCanteiros.h"

ListaCanteiros::ListaCanteiros(wxWindow* parent)
: wxPanel(parent)
{
    SetBackgroundColour(wxColor(100,200,100));
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);
    wxStaticText* title = new wxStaticText(this,wxID_ANY,L"Canteiros:",wxDefaultPosition,wxSize(160,30),wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
    title->SetForegroundColour(wxColor(250,250,250));
    wxFont font =title->GetFont();
    font.SetPointSize(20);
    title->SetFont(font);
    sizer->Add(title,wxSizerFlags(0.3).CenterHorizontal().Border(wxDirection::wxALL,10).FixedMinSize());
    text = new wxTextCtrl(this,ID_TEXT,"",wxDefaultPosition,wxSize(150,30));
    text->SetMaxLength(30);
    sizer->Add(text,wxSizerFlags(0.3).Align(wxALIGN_TOP).FixedMinSize().Border(wxDirection::wxALL,10).Expand());
    
    wxArrayString cants;
    cants.Add("Canteiro Esquerdo Num 1");
    cants.Add("Canteiro Esquerdo Num 2");
    cants.Add("Canteiro Esquerdo Num 3");
    cants.Add("Canteiro Esquerdo Num 4");
    cants.Add("Canteiro Esquerdo Num 5");

    list = new wxListBox(this,ID_SELECT,wxDefaultPosition,wxSize(150,-1),cants);
    sizer->Add(list,wxSizerFlags(1).Align(wxALIGN_TOP).FixedMinSize().Border(wxLEFT|wxBOTTOM|wxRIGHT,10).Expand());

}

void ListaCanteiros::ResetText()
{
    text->ChangeValue("");
}