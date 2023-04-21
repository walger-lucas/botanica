#pragma once
#include "Janela.h"

class JVerRelatorio: public Janela
{
    public:
        JVerRelatorio(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};