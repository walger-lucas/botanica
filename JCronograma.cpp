#include "JCronograma.h"

JCronograma::JCronograma(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    wxPanel* panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(400,400));
    panel->SetBackgroundColour(wxColor(200,100,200));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel,1,wxEXPAND|wxALL);
}

void JCronograma::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CRONOGRAMA,false);
    jP->SetStatusText(L"Acesso ao cronograma de rega dos canteiros cadastrados.");
    
}

void JCronograma::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CRONOGRAMA,true);
}