#include "Canteiro.h"

DadosCanteiro::DadosCanteiro(idCanteiros idCanteiro, string especie, int periodo_rega, float ph, double umidade, string descricao)
{
  this->idCanteiro = idCanteiro;
  this->especie = especie;
  this->periodo_rega = periodo_rega;
  this->ph = ph;
  this->umidade = umidade;
  this->descricao = descricao;
};

DadosCanteiro::~DadosCanteiro()
{

}