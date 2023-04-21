#include "Janela.h"

class JVerCanteiro: public Janela
{
    public:
        JVerCanteiro(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};