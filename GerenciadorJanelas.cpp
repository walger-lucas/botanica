#include "GerenciadorJanelas.h"
#include "Janela.h"
#include "JVerCanteiro.h"
#include "JAddCanteiro.h"
#include "JVerRelatorio.h"
#include "JAddRelatorio.h"
#include "JCronograma.h"


GerenciadorJanelas::GerenciadorJanelas(JanelaPrincipal* jPrincipal)
: jP(jPrincipal), jAtual(J_VER_CANTEIRO)
{
    //------------------- Grounda as janelas;
    for(int i=0;i< J_MAX;i++)
    {
        janelas[i]=nullptr;
    }
    //------------------- Cria as Janelas necessárias

    JAddCanteiro* jACant = new JAddCanteiro(this,jP);
    janelas[J_ADD_CANTEIRO]= static_cast<Janela*>(jACant);
    JVerRelatorio* jVRel = new JVerRelatorio(this,jP);
    janelas[J_VER_RELATORIO]= static_cast<Janela*>(jVRel);
    JAddRelatorio* jARel = new JAddRelatorio(this,jP);
    janelas[J_ADD_RELATORIO]= static_cast<Janela*>(jARel);
    JCronograma* jC =new JCronograma(this,jP);
    janelas[J_CRONOGRAMA]= static_cast<Janela*>(jC);
    JVerCanteiro* jVCant = new JVerCanteiro(this,jP,jARel,jVRel);
    janelas[J_VER_CANTEIRO]=static_cast<Janela*>(jVCant);
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