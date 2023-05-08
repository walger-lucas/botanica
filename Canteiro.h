#pragma once

/* Standard C++ includes */
#include <string>
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

public:
  idCanteiros idCanteiro;
  string especie;
  int periodo_rega;
  float ph;
  double umidade;
  string descricao;
  DadosCanteiro(idCanteiros idCanteiro, string especie, int periodo_rega, float ph, double umidade, string descricao = "");
  ~DadosCanteiro();
};