#include "Canteiro.h"

DadosCanteiro::DadosCanteiro(idCanteiros canteiro, string especie, int periodo_rega, float ph, double umidade, string descricao)
: canteiro(canteiro), especie(especie), periodo_rega(periodo_rega), ph(ph), umidade(umidade), descricao(descricao)
{
}

DadosCanteiro::~DadosCanteiro()
{
}

/*
  Retorna se a instancia de idCanteiros é nula ou não
  | canteiro: canteiro a ser avaliado
*/
bool canteiroEhNulo(idCanteiros canteiro)
{
  return (canteiro.id == CANTEIRO_NULO.id && canteiro.nome == CANTEIRO_NULO.nome);
}