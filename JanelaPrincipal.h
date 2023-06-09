#pragma once
#include <wx/wx.h>
#include <iostream>
#include "EnumeradoresApp.h"

class GerenciadorJanelas;

/*Frame principal, onde todas as Janelas se conectam*/
class JanelaPrincipal : public wxFrame
{
    public:
    JanelaPrincipal(const wxString &titulo);
    ~JanelaPrincipal();


    private:

    wxMenuBar *barraMenu; //parte visual com todos os menus.
    wxMenu *menuCanteiro; //menu com opcoes para atividades com canteiros
    wxMenu *menuRelatorio; //menu com opcoes para atividades com relatorios
    wxMenu *menuCronograma; // menu com opcoes para atividades com cronogramas
    GerenciadorJanelas* gJ; // Gerenciador de Janelas do APP

    void PrepararJanela();

    
    //chamado quando Adicionar Canteiro é escolhido.
    void NewCanteiro(wxCommandEvent& event);
    //chamado quando Visualizar Canteiros é escolhido.
    void OpenCanteiro(wxCommandEvent& event);
    //chamado quando Adicionar Relatorio é escolhido.
    void NewRelatorio(wxCommandEvent& event);
    //chamado quando Visualizar Relatorios é escolhido.
    void OpenRelatorio(wxCommandEvent& event);
    //chamado quando Visualizar Cronograma é escolhido
    void OpenCronograma(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

