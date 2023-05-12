#pragma once

#include "GerenciadorBD.h"
#include "Relatorio.h"

class GerenciadorRelatorios : private DictCanteiros
{
private:  
  GerenciadorBD *gerenciadorBD;
public:
  DadosRelatorio *dadosRelatorio;
  GerenciadorRelatorios();
  ~GerenciadorRelatorios();
  idRelatorios getId(string nome);
  void adicionarRelatorio(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao);
  void removerRelatorio(idRelatorios relatorio);
  void GerenciadorRelatorios::atualizarRelatorio(idRelatorios relatorio, const DadosRelatorio dadosRelatorio);
  vector<idRelatorios> buscarTodos();
  vector<idRelatorios> buscarPorNome(string nome="");
  vector<idRelatorios> buscarPorEspecie(string especie="");
  DadosRelatorio armazenarRelatorio(idRelatorios relatorio);
};