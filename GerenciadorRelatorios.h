#pragma once

#include "GerenciadorBD.h"
#include "Relatorio.h"

class GerenciadorRelatorios : private DictRelatorios
{
private:  
  GerenciadorBD *gerenciadorBD;
public:
  DadosRelatorio *dadosRelatorio;
  GerenciadorRelatorios();
  ~GerenciadorRelatorios();
  idRelatorios getId(string nome);
  void adicionarRelatorio(idCanteiros canteiro, string nome, float ph = -1, double umidade = -1, string saude = "", string obs = "");
  void removerRelatorio(idRelatorios relatorio);
  vector<idRelatorios> buscarTodos();
  vector<idRelatorios> buscarPorNome(string nome="");
  DadosRelatorio armazenarRelatorio(idRelatorios relatorio);
};