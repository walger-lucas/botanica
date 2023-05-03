#include "PainelCanteiro.h"
#include "Canteiro.h"

PainelCanteiro::PainelCanteiro(wxWindow* parent,bool editavel)
: wxPanel(parent), editavel(editavel)
{
    wxBoxSizer* sizer= new wxBoxSizer(wxVERTICAL);
    
    
    
    nomeText = new wxStaticText(this,-1,L"Nome: ",wxDefaultPosition,wxSize(300,20));
    nomeText->SetForegroundColour(wxColor(0,0,0));
    //-----------------Nome
    nome = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,20));
    nome->SetMaxLength(30);
    nome->ChangeValue(L"Canteiro Qualquer X");
    especieText = new wxStaticText(this,-1,L"Espécie: ",wxDefaultPosition,wxSize(300,20));
    especieText->SetForegroundColour(wxColor(0,0,0));
    especie = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,20));
    especie->SetMaxLength(50);
    especie->ChangeValue(L"Espécie Qualquer V");

    descricaoText = new wxStaticText(this,-1,L"Descrição:",wxDefaultPosition,wxSize(300,20));
    descricaoText->SetForegroundColour(wxColor(0,0,0));
    descricao = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,100),wxTE_MULTILINE);
    descricao->ChangeValue(L"Descrição qualquer de um canteiro em estado qualquer.");
    
    phText = new wxStaticText(this,-1,L"pH preferido: ",wxDefaultPosition,wxSize(300,20));
    phSlider = new wxSlider(this,-1,7,0,14,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
    phText->SetForegroundColour(wxColor(0,0,0));
    phSlider->SetForegroundColour(wxColor(0,0,0));

    umidadeText = new wxStaticText(this,-1,L"Umidade preferida: ",wxDefaultPosition,wxSize(300,20));
    umidadeSlider = new wxSlider(this,-1,50,0,100,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
    umidadeText->SetForegroundColour(wxColor(0,0,0));
    umidadeSlider->SetForegroundColour(wxColor(0,0,0));

    periodoText = new wxStaticText(this,-1,L"Perído de rega em horas: ",wxDefaultPosition,wxSize(300,20));
    periodoSlider = new wxSlider(this,-1,24,1,720,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
    periodoText->SetForegroundColour(wxColor(0,0,0));
    periodoSlider->SetForegroundColour(wxColor(0,0,0));

    

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
    sizer->AddSpacer(10);
    sizer->Add(periodoText,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->Add(periodoSlider,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());

    SetSizerAndFit(sizer);
    Atualizar();
}

void PainelCanteiro::Reset()
{
    phText->SetLabelText(L"pH preferido: \n");
    umidadeText->SetLabelText(L"Umidade preferida: \n");
    periodoText->SetLabelText(L"Período de rega em horas:");

    nome->ChangeValue(L"");
    especie->ChangeValue(L"");
    descricao->ChangeValue(L"");
    phSlider->SetValue(7);
    umidadeSlider->SetValue(50);
    periodoSlider->SetValue(24);

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
        periodoSlider->Show(true);
    }else
    {
        nome->SetEditable(false);
        especie->SetEditable(false);
        descricao->SetEditable(false);
        phSlider->Show(false);
        umidadeSlider->Show(false);
        periodoSlider->Show(false);
    }
    Layout();
}

void PainelCanteiro::AdicionarCanteiro(const DadosCanteiro canteiro)
{
    phText->SetLabelText(L"pH preferido: "+std::to_string(canteiro.ph));
    umidadeText->SetLabelText(L"Umidade preferida: "+std::to_string(canteiro.umidade));
    periodoText->SetLabelText(L"Período de rega em horas:"+std::to_string(canteiro.periodo_rega));

    nome->ChangeValue(canteiro.idCanteiro.nome);
    especie->ChangeValue(canteiro.especie);
    descricao->ChangeValue(canteiro.descricao);
    phSlider->SetValue((int)canteiro.ph);
    umidadeSlider->SetValue((int)canteiro.umidade);
    periodoSlider->SetValue(canteiro.periodo_rega);
}

DadosCanteiro PainelCanteiro::PegarCanteiro()
{
    idCanteiros id;
    id.id= -1;
    id.nome= nome->GetValue().mb_str();
    string especiet, descricaot;
    especiet=especie->GetValue().mb_str();
    descricaot=descricao->GetValue().mb_str();
    double umidade = (double) umidadeSlider->GetValue();
    float ph = (float) phSlider->GetValue();
    int periodo = periodoSlider->GetValue();
    DadosCanteiro canteiro(id,especiet,periodo,ph,umidade,descricaot);
    return canteiro;
}