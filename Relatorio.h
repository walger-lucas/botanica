#pragma once

/* Standard C++ includes */
#include <string>
#include <iostream>

using namespace std;

struct idRelatorios
{
  int id;
  string nome;
  int id_cant;
};

const idRelatorios RELATORIO_NULO = {-1, "__nulo__", -1};
bool relatorioEhNulo(idRelatorios relatorio);

class DadosRelatorio
{
private:  

public:
  idRelatorios idRelatorio;
  string data;
  float ph;
  double umidade;
  string saude;
  string obs;
  DadosRelatorio(idRelatorios idRelatorio, string data, float ph = -1, double umidade = -1, string saude = "", string obs = "");
  ~DadosRelatorio();
};