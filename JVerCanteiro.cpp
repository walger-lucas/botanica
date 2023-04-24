#include "JVerCanteiro.h"


JVerCanteiro::JVerCanteiro(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    
    splitter = new wxSplitterWindow(this,-1,wxDefaultPosition,wxDefaultSize,wxSP_LIVE_UPDATE);
    wxPanel* direito = new wxPanel(splitter);
    lC = new ListaCanteiros(splitter);
    direito->SetBackgroundColour(wxColor(50,120,50));
    splitter->SplitVertically(lC,direito);
    splitter->SetMinimumPaneSize(220);
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    
    GetSizer()->Add(splitter,1,wxEXPAND|wxALL);
}

void JVerCanteiro::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CANTEIRO,false);
    jP->SetStatusText(L"Acesso aos canteiros cadastrados.");
}

void JVerCanteiro::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CANTEIRO,true);
    lC->ResetText();
}