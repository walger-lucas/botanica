#ifndef GERENCIADOR_CANTEIROS_H
#define GERENCIADOR_CANTEIROS_H

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
  void adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao);
  void removerCanteiro(idCanteiros canteiro);
  void atualizarCanteiro(idCanteiros canteiro, string parametro, string valor);
  void atualizarCanteiro(idCanteiros canteiro, string parametro, double valor);
  vector<idCanteiros> buscarTodos();
  vector<idCanteiros> buscarPorNome(string nome="");
  vector<idCanteiros> buscarPorEspecie(string especie="");
};

#endif // GERENCIADOR_CANTEIROS_H