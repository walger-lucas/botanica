#include "JCronograma.h"
#include "Aplicacao.h"


JCronograma::JCronograma(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    wxPanel* panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(400,400));
    grid = new wxGrid(panel,-1,wxDefaultPosition,wxSize(400,400));
    vector<idCanteiros> ids = Aplicacao::GetGerCanteiros().buscarTodos();
    grid->CreateGrid(200,2);
    grid->SetColSize(0,200);
    grid->SetColSize(1,200);
    grid->SetCellValue(0,0,L"Canteiro");
    grid->SetCellValue(0,1,L"Data para Rega");
    grid->DisableDragRowSize();
    grid->DisableDragColSize();
    grid->HideRowLabels();
    grid->HideColLabels();
    grid->EnableEditing(false);
    grid->SetGridLineColour(wxColor(0,0,0));
    grid->EnableGridLines(true);
    
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(grid,wxSizerFlags(1).CenterHorizontal().Border(wxALL,40).FixedMinSize());
    panel->SetSizerAndFit(sizer);

    panel->SetBackgroundColour(wxColor(200,100,200));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel,1,wxEXPAND|wxALL);
}

void JCronograma::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CRONOGRAMA,false);
    jP->SetStatusText(L"Acesso ao cronograma de rega dos canteiros cadastrados.");
    vector<idCanteiros> ids = Aplicacao::GetGerCanteiros().buscarTodos();
    grid->ClearGrid();
    grid->SetCellValue(0,0,L"Canteiro");
    grid->SetCellValue(0,1,L"Data para Rega");
    size_t size = ids.size()+1;
    for(int i =1;i<size&& i<200;i++)
    {
        grid->SetCellValue(i,0,ids[i-1].nome);
        grid->SetCellValue(i,1,ids[i-1].prox_rega);
    }
    
}

void JCronograma::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_CRONOGRAMA,true);
}