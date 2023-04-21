#include "JAddCanteiro.h"

JAddCanteiro::JAddCanteiro(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    wxPanel* panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(400,400));
    panel->SetBackgroundColour(wxColor(200,100,100));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel,1,wxEXPAND|wxALL);
}

void JAddCanteiro::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_CANTEIRO,false);
    
}

void JAddCanteiro::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_CANTEIRO,true);
}