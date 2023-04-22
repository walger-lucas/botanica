#pragma once
#include "Janela.h"

class JCronograma: public Janela
{
    public:
        JCronograma(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};