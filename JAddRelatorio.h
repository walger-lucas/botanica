#pragma once
#include "Janela.h"

class JAddRelatorio: public Janela
{
    public:
        JAddRelatorio(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};