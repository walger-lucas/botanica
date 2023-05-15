#include "Aplicacao.h"
#include "JanelaPrincipal.h"

wxIMPLEMENT_APP(Aplicacao);
GerenciadorCanteiros Aplicacao::gerCant=GerenciadorCanteiros();
GerenciadorRelatorios Aplicacao::gerRel=GerenciadorRelatorios();
bool Aplicacao::OnInit()
{
    JanelaPrincipal* janelaPrincipal = new JanelaPrincipal(L"Botânica");
    janelaPrincipal->SetClientSize(800,600);
    janelaPrincipal->Center();
    janelaPrincipal->Show();
    return true;
}