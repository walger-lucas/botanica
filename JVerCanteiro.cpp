#include "JVerCanteiro.h"


JVerCanteiro::JVerCanteiro(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    lC = new ListaCanteiros(this);
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(lC,1,wxEXPAND|wxALL);
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