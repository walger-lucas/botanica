#pragma once
#include "JanelaPrincipal.h"
#include<wx/wx.h>

using namespace std;

class Janela;

class GerenciadorJanelas
{
    private:
        Janela* janelas[Janelas::J_MAX];
        long jAtual;
        JanelaPrincipal* jP;

    public:
        
        GerenciadorJanelas(JanelaPrincipal* jPrincipal=nullptr);
        //muda de janela para janela
        void MudarJanela(int id);

        
};