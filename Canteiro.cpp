#include "Canteiro.h"

DadosCanteiro::DadosCanteiro(idCanteiros idCanteiro, string especie, int periodo_rega, float ph, double umidade, string descricao)
: idCanteiro(idCanteiro), especie(especie), periodo_rega(periodo_rega), ph(ph), umidade(umidade), descricao(descricao)
{
}

DadosCanteiro::~DadosCanteiro()
{
}