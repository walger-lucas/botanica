#include "JVerCanteiro.h"

JVerCanteiro::JVerCanteiro(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    wxPanel* panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(400,400));
    panel->SetBackgroundColour(wxColor(100,200,100));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel,1,wxEXPAND|wxALL);
}

void JVerCanteiro::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CANTEIRO,false);
    
}

void JVerCanteiro::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CANTEIRO,true);
}