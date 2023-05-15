#include "JVerRelatorio.h"
#include "Aplicacao.h"
#include <vector>
wxBEGIN_EVENT_TABLE(JVerRelatorio,wxWindow)
EVT_LISTBOX(ListaCanteiros::ID_SELECT,JVerRelatorio::Select)
EVT_LISTBOX(51,JVerRelatorio::SelectRelatorio)
wxEND_EVENT_TABLE()
JVerRelatorio::JVerRelatorio(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    splitter = new wxSplitterWindow(this,-1,wxDefaultPosition,wxDefaultSize,wxSP_LIVE_UPDATE);
    lC = new ListaCanteiros(splitter);
    lC->SetBackgroundColour(wxColor(100,100,200));
    wxSplitterWindow* splitter2 = new wxSplitterWindow(splitter,-1,wxDefaultPosition,wxDefaultSize,wxSP_LIVE_UPDATE);
    wxPanel* relatorios = new wxPanel(splitter2);
    pRelatorios = new PainelRelatorio(splitter2,false);

    //-------------------------------------------------- Preparando Relatorios
    wxStaticText* relat = new wxStaticText(relatorios,-1,L"Relatórios:",wxDefaultPosition,
        wxSize(160,30),wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
    wxFont font =relat->GetFont();
    font.SetPointSize(20);
    relat->SetFont(font);
    relat->SetForegroundColour(wxColor(250,250,250));
    relatorios->SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    relatorios->GetSizer()->Add(relat,wxSizerFlags(0.3).CenterHorizontal().Border(wxDirection::wxALL,10).FixedMinSize());
    relatorios->SetBackgroundColour(wxColor(50,50,90));


    wxArrayString rels;
    rels.Add("RELATORIO 1");
    rels.Add("RELATORIO 2");
    rels.Add("RELATORIO 3");
    rels.Add("RELATORIO 4");

    listRelat = new wxListBox(relatorios,51,wxDefaultPosition,wxSize(150,-1),rels);
    relatorios->GetSizer()->Add(listRelat,wxSizerFlags(1).Align(wxALIGN_TOP).FixedMinSize().Border(wxLEFT|wxBOTTOM|wxRIGHT,10).Expand());
    //--------------------------------------------------
    pRelatorios->SetBackgroundColour(wxColor(50,50,120));
    splitter->SplitVertically(lC,splitter2);
    splitter2->SplitVertically(relatorios,pRelatorios);
    splitter2->SetMinimumPaneSize(220);
    splitter->SetMinimumPaneSize(220);
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    
    GetSizer()->Add(splitter,1,wxEXPAND|wxALL);
}

void JVerRelatorio::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_RELATORIO,false);
    lC->ResetText();
    jP->SetStatusText(L"Acessar relatório cadastrado no sistema.");
    listRelat->DeselectAll();
    listRelat->Clear();
    pRelatorios->Show(false);
}

void JVerRelatorio::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_OPEN_RELATORIO,true);
}

void JVerRelatorio::Select(wxCommandEvent& evt)
{
    idCant = lC->GetIdCanteiro();
    vector<idRelatorios>::iterator it;
    for(it=idCant.relatorios.begin();it<idCant.relatorios.end();it++)
    {
        listRelat->Append((*it).nome);
    }
}

void JVerRelatorio::SelectRelatorio(wxCommandEvent& evt)
{

    pRelatorios->AdicionarRelatorio(Aplicacao::gerRel.armazenarRelatorio(idCant.relatorios[listRelat->GetSelection()]));
    pRelatorios->Show(true);
    
}