#include "Canteiro.h"

DadosCanteiro::DadosCanteiro(idCanteiros _idCanteiro, string _especie, int _periodo_rega, float _ph, double _umidade, string _descricao)
{
  idCanteiro = _idCanteiro;
  especie = _especie;
  periodo_rega = _periodo_rega;
  ph = _ph;
  umidade = _umidade;
  descricao = _descricao;
};