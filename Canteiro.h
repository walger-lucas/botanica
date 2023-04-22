#ifndef CANTEIRO_H
#define CANTEIRO_H

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

using namespace std;

struct idCanteiros
{
  int id;
  string nome;
};

class DadosCanteiro
{
private:  
  idCanteiros idCanteiro;
  string especie;
  int periodo_rega;
  float ph;
  double umidade;
  string descricao;

public:
  DadosCanteiro(idCanteiros idCanteiro, string especie, int periodo_rega, float ph, double umidade, string descricao = "");
  ~DadosCanteiro();
  void alterarDado();
  void acessarDado();
};

#endif //CANTEIRO_H