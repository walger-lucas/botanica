#include "PainelRelatorio.h"
#include "Relatorio.h"

PainelRelatorio::PainelRelatorio(wxWindow* parent,bool editavel)
: wxPanel(parent), editavel(editavel)
{
    wxBoxSizer* sizer= new wxBoxSizer(wxVERTICAL);
    
    
    
    estadoText = new wxStaticText(this,-1,L"Estado: ",wxDefaultPosition,wxSize(300,20));
    estadoText->SetForegroundColour(wxColor(0,0,0));
    //-----------------Nome
    estado = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,20));
    estado->SetMaxLength(30);
    estado->ChangeValue(L"");

    descricaoText = new wxStaticText(this,-1,L"Descrição:",wxDefaultPosition,wxSize(300,20));
    descricaoText->SetForegroundColour(wxColor(0,0,0));
    descricao = new wxTextCtrl(this,-1,L"",wxDefaultPosition,wxSize(300,100),wxTE_MULTILINE);
    descricao->ChangeValue(L"Descrição qualquer de um canteiro em estado qualquer.");
    
    phText = new wxStaticText(this,-1,L"pH atual: ",wxDefaultPosition,wxSize(300,20));
    phSlider = new wxSlider(this,-1,7,0,14,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
    phText->SetForegroundColour(wxColor(0,0,0));
    phSlider->SetForegroundColour(wxColor(0,0,0));

    umidadeText = new wxStaticText(this,-1,L"Umidade atual: ",wxDefaultPosition,wxSize(300,20));
    umidadeSlider = new wxSlider(this,-1,50,0,100,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
    umidadeText->SetForegroundColour(wxColor(0,0,0));
    umidadeSlider->SetForegroundColour(wxColor(0,0,0));

    

    sizer->Add(estadoText,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
    sizer->Add(estado,wxSizerFlags(0.2).Expand().Border(wxALL,2).FixedMinSize());
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

void PainelRelatorio::Reset()
{
    phText->SetLabelText(L"pH atual: \n");
    umidadeText->SetLabelText(L"Umidade atual: \n");

    estado->ChangeValue(L"");
    descricao->ChangeValue(L"");
    phSlider->SetValue(7);
    umidadeSlider->SetValue(50);

}

void PainelRelatorio::MudarEstilo(bool editavel)
{
    this->editavel=editavel;
    Atualizar();
}

void PainelRelatorio::Atualizar()
{
    if(editavel)
    {
        estado->SetEditable(true);
        descricao->SetEditable(true);
        phSlider->Show(true);
        umidadeSlider->Show(true);
    }else
    {
        estado->SetEditable(false);
        descricao->SetEditable(false);
        phSlider->Show(false);
        umidadeSlider->Show(false);
    }
    Layout();
}

void PainelRelatorio::AdicionarRelatorio(const DadosRelatorio dadosRelatorio)
{
    phText->SetLabelText(L"pH atual: "+std::to_string(dadosRelatorio.ph));
    umidadeText->SetLabelText(L"Umidade atual: "+std::to_string(dadosRelatorio.umidade));

    estado->ChangeValue(dadosRelatorio.saude);
    descricao->ChangeValue(dadosRelatorio.obs);
    phSlider->SetValue((int)dadosRelatorio.ph);
    umidadeSlider->SetValue((int)dadosRelatorio.umidade);
}

DadosRelatorio PainelRelatorio::PegarRelatorio()
{
    idRelatorios id;
    id.id= -1;
    id.nome= "Relatorio";
    string descricaot,estadot;
    estadot=estado->GetValue().ToStdString();
    descricaot=descricao->GetValue().ToStdString();
    double umidade = (double) umidadeSlider->GetValue();
    float ph = (float) phSlider->GetValue();
    DadosRelatorio dadosRelatorio(id,"",ph,umidade,estadot,descricaot);
    return dadosRelatorio;
}