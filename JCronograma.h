#pragma once
#include "Janela.h"

/*Janela para acessar cronogramas.*/
class JCronograma: public Janela
{
    public:
        JCronograma(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};