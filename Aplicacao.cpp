#include "Aplicacao.h"
#include "JanelaPrincipal.h"

wxIMPLEMENT_APP(Aplicacao);
GerenciadorCanteiros* Aplicacao::gerCant=nullptr;
GerenciadorRelatorios* Aplicacao::gerRel=nullptr;
bool Aplicacao::OnInit()
{
    gerCant = new GerenciadorCanteiros();
    gerRel= new GerenciadorRelatorios();
    JanelaPrincipal* janelaPrincipal = new JanelaPrincipal(L"Botânica");
    janelaPrincipal->SetClientSize(800,600);
    janelaPrincipal->Center();
    janelaPrincipal->Show();
    return true;
}