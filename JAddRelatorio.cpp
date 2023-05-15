#include "JAddRelatorio.h"
#include "Aplicacao.h"
wxBEGIN_EVENT_TABLE(JAddRelatorio,wxWindow)
EVT_BUTTON(29,JAddRelatorio::Select)
wxEND_EVENT_TABLE()
JAddRelatorio::JAddRelatorio(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    
    lC = new ListaCanteiros(this);
    lC->SetBackgroundColour(wxColor(100,200,200));
    relatorios= new PainelRelatorio(this,true);
    relatorios->SetBackgroundColour(wxColor(100,200,200));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(lC,1,wxEXPAND|wxALL);
    GetSizer()->Add(relatorios,1,wxEXPAND|wxALL);
    wxButton* adicionarRelatorio = new wxButton(this,29,L"Adicionar Relatório");
    GetSizer()->Add(adicionarRelatorio,0.3,wxEXPAND|wxALL,10);
}

void JAddRelatorio::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_RELATORIO,false);
    lC->ResetText();
    relatorios->Reset();
    relatorios->Show(false);
    lC->Show(true);
    jP->SetStatusText(L"Cadastrar relatório a um canteiro cadastrado no sistema.");
    segundaPag=false;
    GetSizer()->Layout();
}

void JAddRelatorio::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_RELATORIO,true);
}

void JAddRelatorio::Select(wxCommandEvent& evt)
{
    if(!segundaPag)
    {
        id= lC->GetIdCanteiro();
        if(id.id>=0)
        {
            segundaPag=true;
            relatorios->Show(true);
            lC->Show(false);
        }
    }else
    {
        DadosRelatorio rel = relatorios->PegarRelatorio();
        rel.relatorio.id_cant = id.id;
        rel.relatorio.nome =id.nome +" - "+ to_string(id.relatorios.size()+1);

        lC->ResetText();
        relatorios->Reset();
        relatorios->Show(false);
        lC->Show(true);
        segundaPag=false;
        Aplicacao::GetGerRelatorios().adicionarRelatorio(id,rel.relatorio.nome,rel.ph,rel.umidade,rel.saude,rel.obs);
        
    }
    Layout();

}

void JAddRelatorio::SelecionarCanteiro(idCanteiros& _id)
{
        id= idCanteiros(_id);
        segundaPag=true;
        relatorios->Show(true);
        lC->Show(false);
        Layout();
}