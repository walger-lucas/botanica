#include "Relatorio.h"

DadosRelatorio::DadosRelatorio(idRelatorios idRelatorio, string data, float ph, double umidade, string saude, string obs)
: idRelatorio(idRelatorio), data(data), ph(ph), umidade(umidade), saude(saude), obs(obs)
{
}

DadosRelatorio::~DadosRelatorio()
{
}

/*
  Retorna se a instancia de idRelatorios é nula ou não
  | relatorio: relatorio a ser avaliado
*/
bool relatorioEhNulo(idRelatorios relatorio)
{
  return (relatorio.id == RELATORIO_NULO.id && relatorio.nome == RELATORIO_NULO.nome);
}