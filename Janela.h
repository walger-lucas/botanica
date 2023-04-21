#pragma once
#include "JanelaPrincipal.h"
#include "GerenciadorJanelas.h"
#include "EnumeradoresApp.h"
//inteface para as janelas do aplicativo.
class Janela: public wxWindow
{
    protected:
        GerenciadorJanelas* gJ;
    public:
        //Apresenta tudo necessário
        virtual void Inicializar(JanelaPrincipal* jP)=0;
        //Desliga o necessário
        virtual void Desligar(JanelaPrincipal* jP)=0;
        Janela(GerenciadorJanelas* gJ,wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition,
         const wxSize &size=wxDefaultSize, long style=0, 
         const wxString &name=wxPanelNameStr);
        Janela(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition,
         const wxSize &size=wxDefaultSize, long style=0, 
         const wxString &name=wxPanelNameStr);

};