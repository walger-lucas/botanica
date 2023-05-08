#include "Relatorio.h"

DadosRelatorio::DadosRelatorio(idRelatorios idRelatorio, string data, float ph, double umidade, string saude, string obs)
: idRelatorio(idRelatorio), data(data), ph(ph), umidade(umidade), saude(saude), obs(obs)
{
}

DadosRelatorio::~DadosRelatorio()
{
}