#pragma once
#include "Janela.h"

/* Janela para adicionar Relatório*/
class JAddRelatorio: public Janela
{
    public:
        JAddRelatorio(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};