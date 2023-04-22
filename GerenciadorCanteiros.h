#ifndef GERENCIADOR_CANTEIROS_H
#define GERENCIADOR_CANTEIROS_H

#include "GerenciadorBD.h"
#include "Canteiro.h"

class GerenciadorCanteiros
{
private:  
  vector<idCanteiros> lista_canteiros;
  GerenciadorBD gerenciadorBD = GerenciadorBD();
public:
  GerenciadorCanteiros();
  ~GerenciadorCanteiros();
  void adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao);
};



#endif // GERENCIADOR_CANTEIROS_H