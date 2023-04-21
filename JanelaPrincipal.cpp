#include "JanelaPrincipal.h"
#include "GerenciadorJanelas.h"

//conecta ids com funcoes em compilador
wxBEGIN_EVENT_TABLE(JanelaPrincipal,wxFrame)
    EVT_MENU(ID_NEW_CANTEIRO,JanelaPrincipal::NewCanteiro)
    EVT_MENU(ID_OPEN_CANTEIRO,JanelaPrincipal::OpenCanteiro)
    EVT_MENU(ID_NEW_RELATORIO,JanelaPrincipal::NewRelatorio)
    EVT_MENU(ID_OPEN_RELATORIO,JanelaPrincipal::OpenRelatorio)
    EVT_MENU(ID_OPEN_CRONOGRAMA,JanelaPrincipal::OpenCronograma)
wxEND_EVENT_TABLE()


JanelaPrincipal::JanelaPrincipal(const wxString &titulo)
: wxFrame(nullptr,wxID_ANY,titulo)
{
    PrepararJanela();
    SetSizerAndFit(new wxBoxSizer(wxHORIZONTAL));
    gJ= new GerenciadorJanelas(this);

    
}

JanelaPrincipal::~JanelaPrincipal()
{
    delete gJ;
}
//Prepara toda a parte visual da janela, incluindo preparar a barra de menu.
void JanelaPrincipal::PrepararJanela()
{
    //INICIO - PREPARANDO MENUS---------------------------------------------------
    //prepara subcategorias de menuCanteiro
    menuCanteiro = new wxMenu;
   
    menuCanteiro->Append(ID_NEW_CANTEIRO,L"&Adicionar Canteiro...\tCtrl-N",
    "Adiciona um novo Canteiro ao Sistema.");
    menuCanteiro->AppendSeparator();
    menuCanteiro->Append(ID_OPEN_CANTEIRO,L"&Visualizar Canteiros...",
     "Acessa os Canteiros previamente cadastrados.");

    //prepara subcategorias menuRelatorio
    menuRelatorio = new wxMenu;
    menuRelatorio->Append(ID_NEW_RELATORIO,L"&Adicionar Relatório...\tCtrl-R",
     L"Registra novo Relatório de um Canteiro ao sistema.");
    menuRelatorio ->AppendSeparator();
    menuRelatorio-> Append(ID_OPEN_CANTEIRO,L"&Visualizar Relatórios...",
     L"Acessa Relatórios previamente cadastrados.");


    //prepara subcategorias de menuCronograma
    menuCronograma = new wxMenu;
    menuCronograma-> Append(ID_OPEN_CRONOGRAMA,L"&Acessar Cronograma de Rega...",
    L"Acessa Cronograma de rega de todos os canteiros registrados.");

    //Adiciona menus à barra de menu.
    wxMenuBar* barraMenu = new wxMenuBar;
    barraMenu->Append(menuCanteiro,L"&Canteiros");
    barraMenu->Append(menuRelatorio,L"&Relatórios");
    barraMenu->Append(menuCronograma,L"Crono&grama");
    //Apresenta barra de menus.
    SetMenuBar(barraMenu);
    CreateStatusBar();
    SetStatusText(L"Bem vinde ao Botânica, o aplicativo de registro de canteiros.");
    //Conecta funcoes com as opcoes do menu
    
    //FIM - PREPARANDO MENUS----------------------------------------------------

}


void JanelaPrincipal::NewCanteiro(wxCommandEvent& ev)
{
    cout<<"add canteiro\n";
    gJ->MudarJanela(Janelas::J_ADD_CANTEIRO);
    
}
void JanelaPrincipal::OpenCanteiro(wxCommandEvent& ev)
{
    cout<<"ver canteiro\n";
    gJ->MudarJanela(Janelas::J_VER_CANTEIRO);
    
}