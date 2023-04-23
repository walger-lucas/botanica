#include "GerenciadorCanteiros.h"

GerenciadorCanteiros::GerenciadorCanteiros()
{
  gerenciadorBD = GerenciadorBD();
  vector<idCanteiros> canteiros = gerenciadorBD.selecionarCanteiros();
  for(auto it = canteiros.begin(); it != canteiros.end(); it++)
    dict_canteiros[it->nome] = *it;
}

GerenciadorCanteiros::~GerenciadorCanteiros()
{
}

void GerenciadorCanteiros::adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao)
{
  dict_canteiros[nome] = gerenciadorBD.criarCanteiro(nome, especie, periodo_rega, ph, umidade, descricao);
}

void GerenciadorCanteiros::removerCanteiro(idCanteiros canteiro)
{
  gerenciadorBD.descartarCanteiro(canteiro.nome);
  dict_canteiros.erase(canteiro.nome);
}

vector<idCanteiros> GerenciadorCanteiros::buscarPorNome(string filtro)
{
  return gerenciadorBD.selecionarCanteiros("nome", filtro);
}

int main()
{
  GerenciadorCanteiros gerenciadorCanteiros = GerenciadorCanteiros();
  gerenciadorCanteiros.removerCanteiro(gerenciadorCanteiros.dict_canteiros.at("Bromelia 1"));
  return 0;
}