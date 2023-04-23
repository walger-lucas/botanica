#pragma once
#include "Janela.h"
#include "ListaCanteiros.h"

class JVerCanteiro: public Janela
{
    public:
        ListaCanteiros* lC;
        JVerCanteiro(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};