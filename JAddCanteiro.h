#include "Janela.h"

class JAddCanteiro: public Janela
{
    public:
        JAddCanteiro(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};