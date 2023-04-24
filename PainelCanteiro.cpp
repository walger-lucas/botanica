#include "PainelCanteiro.h"

PainelCanteiro::PainelCanteiro(wxWindow* parent,bool editavel)
: wxPanel(parent), editavel(editavel)
{
    wxBoxSizer* sizer= new wxBoxSizer(wxVERTICAL);
    
    
    
    nomeText = new wxStaticText(this,-1,L"Nome: ",wxDefaultPosition,wxSize(300,30));
    nomeText->SetForegroundColour(wxColor(0,0,0));
    wxFont font =nomeText->GetFont();
    font.SetPointSize(20);
    nomeText->SetFont(font);
    //-----------------Nome
    nome = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,30));
    nome->SetFont(font);
    nome->SetMaxLength(30);
    nome->ChangeValue(L"Canteiro Qualquer X");
    especieText = new wxStaticText(this,-1,L"Espécie: ",wxDefaultPosition,wxSize(300,30));
    especieText->SetForegroundColour(wxColor(0,0,0));
    especie = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,30));
    especieText->SetFont(font);
    especie->SetFont(font);
    especie->SetMaxLength(50);
    especie->ChangeValue(L"Espécie Qualquer V");

    descricaoText = new wxStaticText(this,-1,L"Descrição: \n oi",wxDefaultPosition,wxSize(300,30));
    descricaoText->SetForegroundColour(wxColor(0,0,0));
    descricao = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,100),wxTE_MULTILINE);
    descricaoText->SetFont(font);
    descricao->SetFont(font);
    descricao->ChangeValue(L"Descrição qualquer de um canteiro em estado qualquer.");
    
    phText = new wxStaticText(this,-1,L"PH preferido: ",wxDefaultPosition,wxSize(300,30));
    phSlider = new wxSlider(this,-1,7,0,14,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
    phText->SetForegroundColour(wxColor(0,0,0));
    phSlider->SetForegroundColour(wxColor(0,0,0));
    phText->SetFont(font);
    phSlider->SetFont(font);

    umidadeText = new wxStaticText(this,-1,L"Umidade preferida: ",wxDefaultPosition,wxSize(300,30));
    umidadeSlider = new wxSlider(this,-1,50,0,100,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
    umidadeText->SetForegroundColour(wxColor(0,0,0));
    umidadeSlider->SetForegroundColour(wxColor(0,0,0));
    umidadeText->SetFont(font);
    umidadeSlider->SetFont(font);
    

    sizer->Add(nomeText,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->Add(nome,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->AddSpacer(10);
    sizer->Add(especieText,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->Add(especie,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->AddSpacer(10);
    sizer->Add(descricaoText,wxSizerFlags(0.4).Expand().Border(wxALL,2));
    sizer->Add(descricao,wxSizerFlags(0.4).Expand().Border(wxALL,2).FixedMinSize());
    sizer->AddSpacer(10);
    sizer->Add(phText,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->Add(phSlider,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->AddSpacer(10);
    sizer->Add(umidadeText,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->Add(umidadeSlider,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());

    SetSizerAndFit(sizer);
    Atualizar();
}

void PainelCanteiro::Reset()
{
    phText->SetLabelText(L"PH preferido: \n");
    umidadeText->SetLabelText(L"Umidade preferida: \n");

    nome->ChangeValue(L"");
    especie->ChangeValue(L"");
    descricao->ChangeValue(L"");
    phSlider->SetValue(7);
    umidadeSlider->SetValue(50);

}

void PainelCanteiro::MudarEstilo(bool editavel)
{
    this->editavel=editavel;
    Atualizar();
}

void PainelCanteiro::Atualizar()
{
    if(editavel)
    {
        nome->SetEditable(true);
        especie->SetEditable(true);
        descricao->SetEditable(true);
        phSlider->Show(true);
        umidadeSlider->Show(true);
    }else
    {
        nome->SetEditable(false);
        especie->SetEditable(false);
        descricao->SetEditable(false);
        phSlider->Show(false);
        umidadeSlider->Show(false);
    }
    Layout();
}

