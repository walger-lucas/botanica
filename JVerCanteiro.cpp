#include "JVerCanteiro.h"
#include "Aplicacao.h"

wxBEGIN_EVENT_TABLE(JVerCanteiro,wxWindow)
EVT_BUTTON(101,JVerCanteiro::DeleteCanteiro)
EVT_BUTTON(104,JVerCanteiro::AddRelatorio)
EVT_LISTBOX(ListaCanteiros::ID_SELECT,JVerCanteiro::Select)
wxEND_EVENT_TABLE()


JVerCanteiro::JVerCanteiro(GerenciadorJanelas* gJ, wxWindow* parent,JAddRelatorio* _jRel)
: Janela(gJ,parent,wxID_ANY)
{
    jRel=_jRel;
    splitter = new wxSplitterWindow(this,-1,wxDefaultPosition,wxDefaultSize,wxSP_LIVE_UPDATE);
    direito = new wxPanel(splitter,-1);

    //Cria painel dos canteiros
    direito->SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    painelCanteiro = new PainelCanteiro(direito,false);
    painelCanteiro->SetBackgroundColour(wxColor(50,120,50));
    direito->GetSizer()->Add(painelCanteiro,wxSizerFlags(1).Expand());

    //cria painel de botões
    botoes = new wxPanel(direito,-1);
    botoes->SetBackgroundColour(wxColor(50,120,50));
    botoes->SetSizerAndFit(new wxBoxSizer(wxHORIZONTAL));
    botaoDeletar = new wxButton(botoes,101,L"Deletar Canteiro");
    botaoAcessarRelatorio = new wxButton(botoes,103,L"Acessar Relatório");
    botaoAdicionarRelatorio = new wxButton(botoes,104,L"Adicionar Relatório");
    botoes->GetSizer()->Add(botaoDeletar);
    botoes->GetSizer()->Add(botaoAcessarRelatorio);
    botoes->GetSizer()->Add(botaoAdicionarRelatorio);
    botoes->Layout();
    direito->GetSizer()->Add(botoes,wxSizerFlags(1).Expand());
    direito->Layout();
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
    lC->ResetText();
    jP->SetStatusText(L"Acesso aos canteiros cadastrados.");
    lC->Atualizar();
    botoes->Show(false);
    painelCanteiro->Show(false);
}

void JVerCanteiro::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CANTEIRO,true);
    
}

void JVerCanteiro::DeleteCanteiro(wxCommandEvent& evt)
{
    Aplicacao::gerCant.removerCanteiro(idSelecionado);
    lC->Atualizar();
    botoes->Show(false);
    painelCanteiro->Show(false);
    Layout();
}

void JVerCanteiro::Select(wxCommandEvent& evt)
{
    idCanteiros id =lC->GetIdCanteiro();
    if(id.id>=0)
    {
        idSelecionado=lC->GetIdCanteiro();
        painelCanteiro->AdicionarCanteiro(Aplicacao::gerCant.armazenarCanteiro(idSelecionado));
        botoes->Show(true);
        painelCanteiro->Show(true);
        botoes->Layout();
        painelCanteiro->Layout();
        direito->Layout();
    }
}

void JVerCanteiro::AddRelatorio(wxCommandEvent& evt)
{
    idCanteiros idCant=lC->GetIdCanteiro();
    if(idCant.id>=0)
    {
        gJ->MudarJanela(J_ADD_RELATORIO);
        jRel->SelecionarCanteiro(idCant);
    }
}