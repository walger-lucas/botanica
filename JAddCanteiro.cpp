#include "JAddCanteiro.h"
#include "PainelCanteiro.h"

JAddCanteiro::JAddCanteiro(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    PainelCanteiro* panel = new PainelCanteiro(this,true);
    panel->SetBackgroundColour(wxColor(200,100,100));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel,1,wxEXPAND|wxALL);
    wxButton* button = new wxButton(panel,-1,L"Adicionar Canteiro");
    panel->GetSizer()->AddSpacer(20);
    panel->GetSizer()->Add(button,0.3,wxEXPAND|wxALL|wxBOTTOM,10);
    Layout();
    panel->Reset();
}

void JAddCanteiro::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_CANTEIRO,false);
    jP->SetStatusText(L"Cadastrar canteiro ao sistema.");
}

void JAddCanteiro::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_CANTEIRO,true);
}