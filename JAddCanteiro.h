#pragma once
#include "Janela.h"

/*Janela para adicionar canteiro*/
class JAddCanteiro: public Janela
{
    public:
        JAddCanteiro(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};