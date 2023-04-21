#include "GerenciadorJanelas.h"
#include "Janela.h"
#include "JVerCanteiro.h"
#include "JAddCanteiro.h"



GerenciadorJanelas::GerenciadorJanelas(JanelaPrincipal* jPrincipal)
: jP(jPrincipal), jAtual(J_ADD_CANTEIRO)
{
    //------------------- Grounda as janelas;
    for(int i=0;i< J_MAX;i++)
    {
        janelas[i]=nullptr;
    }
    //------------------- Cria as Janelas necessárias
    JVerCanteiro* jVCant = new JVerCanteiro(this,jP);
    janelas[0]=static_cast<Janela*>(jVCant);
    JAddCanteiro* jACant = new JAddCanteiro(this,jP);
    janelas[1]= static_cast<Janela*>(jACant);


    //------------------- Desaparece com todas as janelas e coloca no sizer de jP
    wxSizer* sizer = jP->GetSizer();
    for(int i=0;i< J_MAX;i++)
    {
        if(janelas[i]!=nullptr)
        {
            sizer->Add((wxWindow*) janelas[i],wxSizerFlags(1).Expand().Border(wxALL,0));
            janelas[i]->Show(false);
        }
    }
    //------------------- Inicializa a primeira janela
    janelas[jAtual]->Inicializar(jP);
    janelas[jAtual]->Show(true);
    jP->Layout();
}

void GerenciadorJanelas::MudarJanela(int id)
{
    if(id != jAtual && id < J_MAX && id >= 0 
        && janelas[id]!= nullptr)
    {
        janelas[jAtual]->Desligar(jP); //desliga janela atual
        janelas[jAtual]->Show(false);
        jAtual = id; //atualiza qual eh a janela atual
        janelas[id]->Inicializar(jP); //prepara nova Janela
        janelas[id]->Show(true);
        jP->Layout(); //redesenha o layout do frame.
    }
}