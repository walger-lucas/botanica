#include "GerenciadorCanteiros.h"

GerenciadorCanteiros::GerenciadorCanteiros()
{
}

GerenciadorCanteiros::~GerenciadorCanteiros()
{
}

void GerenciadorCanteiros::adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao)
{
  idCanteiros canteiro;
  canteiro.id = gerenciadorBD.criarCanteiro(nome, especie, periodo_rega, ph, umidade, descricao);
  canteiro.nome = nome;
  lista_canteiros.push_back(canteiro);
}
