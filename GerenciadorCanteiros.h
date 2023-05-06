#pragma once

#include "GerenciadorBD.h"
#include "Canteiro.h"

class GerenciadorCanteiros
{
private:  
  GerenciadorBD *gerenciadorBD;
public:
  map<string, idCanteiros> dict_canteiros;
  DadosCanteiro *dadosCanteiro;
  GerenciadorCanteiros();
  ~GerenciadorCanteiros();
  idCanteiros getId(string nome);
  bool adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao);
  bool adicionarCanteiro(const DadosCanteiro canteiro);
  void removerCanteiro(idCanteiros canteiro);
  void atualizarCanteiro(idCanteiros canteiro, string parametro, string valor);
  void atualizarCanteiro(idCanteiros canteiro, string parametro, double valor);
  void atualizarCanteiro(idCanteiros idCanteiro, const DadosCanteiro canteiro);
  vector<idCanteiros> buscarTodos();
  vector<idCanteiros> buscarPorNome(string nome="");
  vector<idCanteiros> buscarPorEspecie(string especie="");
  DadosCanteiro armazenarCanteiro(idCanteiros canteiro);
};