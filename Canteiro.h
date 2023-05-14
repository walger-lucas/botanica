#pragma once

/* Standard C++ includes */
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Relatorio.h"

using namespace std;

struct idCanteiros
{
  int id;
  string nome;
  vector<idRelatorios> relatorios;
};

const idCanteiros CANTEIRO_NULO = {-1, "__nulo__"};
bool canteiroEhNulo(idCanteiros canteiro);

class DictCanteiros
{
public:
  map<string, idCanteiros> dict_canteiros;
};

class DadosCanteiro
{
private:  

public:
  idCanteiros canteiro;
  string especie;
  int periodo_rega;
  float ph;
  double umidade;
  string descricao;
  DadosCanteiro(idCanteiros canteiro, string especie, int periodo_rega, float ph, double umidade, string descricao = "");
  ~DadosCanteiro();
};