#include "JVerRelatorio.h"

JVerRelatorio::JVerRelatorio(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    splitter = new wxSplitterWindow(this,-1,wxDefaultPosition,wxDefaultSize,wxSP_LIVE_UPDATE);
    lC = new ListaCanteiros(splitter);
    lC->SetBackgroundColour(wxColor(100,100,200));
    wxSplitterWindow* splitter2 = new wxSplitterWindow(splitter,-1,wxDefaultPosition,wxDefaultSize,wxSP_LIVE_UPDATE);
    wxPanel* relatorios = new wxPanel(splitter2);
    wxPanel* direito = new wxPanel(splitter2);

    //-------------------------------------------------- Preparando Relatorios
    wxStaticText* relat = new wxStaticText(relatorios,-1,L"Relatórios:",wxDefaultPosition,
        wxSize(160,30),wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
    wxFont font =relat->GetFont();
    font.SetPointSize(20);
    relat->SetFont(font);
    relat->SetForegroundColour(wxColor(250,250,250));
    relatorios->SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    relatorios->GetSizer()->Add(relat,wxSizerFlags(0.3).CenterHorizontal().Border(wxDirection::wxALL,10).FixedMinSize());
    relatorios->SetBackgroundColour(wxColor(50,50,90));


    wxArrayString rels;
    rels.Add("RELATORIO 1");
    rels.Add("RELATORIO 2");
    rels.Add("RELATORIO 3");
    rels.Add("RELATORIO 4");

    wxListBox* list = new wxListBox(relatorios,-1,wxDefaultPosition,wxSize(150,-1),rels);
    relatorios->GetSizer()->Add(list,wxSizerFlags(1).Align(wxALIGN_TOP).FixedMinSize().Border(wxLEFT|wxBOTTOM|wxRIGHT,10).Expand());
    //--------------------------------------------------
    direito->SetBackgroundColour(wxColor(50,50,120));
    splitter->SplitVertically(lC,splitter2);
    splitter2->SplitVertically(relatorios,direito);
    splitter2->SetMinimumPaneSize(220);
    splitter->SetMinimumPaneSize(220);
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    
    GetSizer()->Add(splitter,1,wxEXPAND|wxALL);
}

void JVerRelatorio::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_RELATORIO,false);
    jP->SetStatusText(L"Acessar relatório cadastrado no sistema.");
    
}

void JVerRelatorio::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_RELATORIO,true);
}