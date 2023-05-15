#pragma once
#include "Janela.h"
#include <wx/grid.h>

/*Janela para acessar cronogramas.*/
class JCronograma: public Janela
{
        wxGrid* grid;
    public:
        JCronograma(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};