#include "JAddCanteiro.h"
#include "Aplicacao.h"

wxBEGIN_EVENT_TABLE(JAddCanteiro,wxWindow)
EVT_BUTTON(15,JAddCanteiro::AddCanteiro)
wxEND_EVENT_TABLE()
JAddCanteiro::JAddCanteiro(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    panel = new PainelCanteiro(this,true);
    panel->SetBackgroundColour(wxColor(200,100,100));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel,1,wxEXPAND|wxALL);
    wxButton* button = new wxButton(panel,15,L"Adicionar Canteiro");
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

void JAddCanteiro::AddCanteiro(wxCommandEvent& event)
{
    if(Aplicacao::gerCant.adicionarCanteiro(panel->PegarCanteiro()))
    {
        wxMessageBox("Adicionado Canteiro.","Canteiro foi adicionado com sucesso.");
        panel->Reset();
    }
    else
    {
        wxMessageBox(L"Erro",L"Não foi possível salvar o Canteiro, troque o nome.");
    }
}
