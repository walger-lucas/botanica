#ifndef GERENCIADOR_CANTEIROS_H
#define GERENCIADOR_CANTEIROS_H

#include "GerenciadorBD.h"
#include "Canteiro.h"

class GerenciadorCanteiros
{
private:  
  GerenciadorBD gerenciadorBD;
public:
  map<string, idCanteiros> dict_canteiros;
  GerenciadorCanteiros();
  ~GerenciadorCanteiros();
  void adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao);
  void removerCanteiro(idCanteiros canteiro);
  vector<idCanteiros> buscarPorNome(string filtro="");
};

#endif // GERENCIADOR_CANTEIROS_H