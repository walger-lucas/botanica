#include "Relatorio.h"

DadosRelatorio::DadosRelatorio(idRelatorios relatorio, string data, float ph, double umidade, string saude, string obs)
: relatorio(relatorio), data(data), ph(ph), umidade(umidade), saude(saude), obs(obs)
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

vector<idRelatorios> removerDaLista(vector<idRelatorios> lista, idRelatorios relatorio)
{
  vector<idRelatorios> nova_lista;
  for(auto it = lista.begin(); it != lista.end(); it++)
    if(it->id != relatorio.id)
      nova_lista.push_back(relatorio);
  return nova_lista;  
}