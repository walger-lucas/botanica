#pragma once
#include "Janela.h"
#include "ListaCanteiros.h"

/* Janela para adicionar Relatório*/
class JAddRelatorio: public Janela
{
        ListaCanteiros* lC;
    public:
        JAddRelatorio(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};