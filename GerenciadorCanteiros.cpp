#include "GerenciadorCanteiros.h"

/*
  Construtor da classe GerenciadorCanteiros
*/
GerenciadorCanteiros::GerenciadorCanteiros() 
: gerenciadorBD(new GerenciadorBD())
{
  // Recebe as idCanteiros dos canteiros registrados no banco de dados
  vector<idCanteiros> canteiros = gerenciadorBD->selecionarCanteiros();
  // Armazena as idCanteiros em um dicionário a partir do nome
  for(auto it = canteiros.begin(); it != canteiros.end(); it++)
    dict_canteiros[it->nome] = *it;
}

/*
  Desconstrutor da classe GerenciadorBD
*/
GerenciadorCanteiros::~GerenciadorCanteiros()
{
  if(gerenciadorBD)
    delete gerenciadorBD;
  dict_canteiros.clear();
}

/*
  Retorna a struct idCanteiros atraves do nome do canteiro
  | nome: nome do canteiro
*/
idCanteiros GerenciadorCanteiros::getId(string nome)
{
  try
  {
    return dict_canteiros.at(nome);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
}

/*
  Adiciona um novo canteiro ao registro
  | nome: nome do canteiro (não é permitido repetição)
  | especie: especie da planta do canteiro
  | periodo_rega: período entre as regas
  | ph: ph ideal da planta
  | umidade: umidade ideal da planta
  | descricao (opcional): descricao do canteiro
*/
bool GerenciadorCanteiros::adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao)
{

  if(dict_canteiros.count(nome) == 0 && nome!="")
  {
    idCanteiros canteiroCriado = gerenciadorBD->criarCanteiro(nome, especie, periodo_rega, ph, umidade, descricao);
    cout << "Canteiro criado" << endl;
    if(canteiroCriado.id != -1)
      dict_canteiros[nome] = canteiroCriado;
    else
      return false;
  }
  else
    return false;
  return true;
}

/*
  Adiciona um novo canteiro ao registro
  | canteiro: instância DadosCanteiro
*/
bool GerenciadorCanteiros::adicionarCanteiro(const DadosCanteiro canteiro)
{
  return adicionarCanteiro(canteiro.idCanteiro.nome, canteiro.especie, canteiro.periodo_rega, canteiro.ph, canteiro.umidade, canteiro.descricao);
}

/*
  Remove um canteiro do registro
  | canteiro: struct idCanteiros do canteiro de interesse
*/
void GerenciadorCanteiros::removerCanteiro(idCanteiros canteiro)
{
  gerenciadorBD->descartarCanteiro(canteiro.id);
  dict_canteiros.erase(canteiro.nome);
}

/*
  Atualiza um parametro de um canteiro
  | canteiro: struct idCanteiros do canteiro de interesse
  | parametro: parametro de interesse ("nome", "especie" ou "descricao")
  | valor: valor string que vai substituir o valor antigo
*/
void GerenciadorCanteiros::atualizarCanteiro(idCanteiros canteiro, string parametro, string valor)
{
  gerenciadorBD->atualizarCanteiro(canteiro.id, parametro, valor);
  if(parametro == "nome")
  {
    dict_canteiros.erase(canteiro.nome);
    canteiro.nome = valor;
    dict_canteiros[valor] = canteiro;
  }
}


/*
  Atualiza um parametro de um canteiro 
  | nome: nome do canteiro a ser atualizado
  | coluna: parametro ("ph", "periodo_rega" ou "umidade") do canteiro a ser atualizado
  | valor: valor numérico que vai substituir o valor antigo
*/
void GerenciadorCanteiros::atualizarCanteiro(idCanteiros canteiro, string parametro, double valor)
{
  gerenciadorBD->atualizarCanteiro(canteiro.id, parametro, valor);
}

/*
  Atualiza todos os parametros de um canteiro 
  | canteiro: instância DadosCanteiro
*/
void GerenciadorCanteiros::atualizarCanteiro(idCanteiros idCanteiro, const DadosCanteiro canteiro)
{
  atualizarCanteiro(idCanteiro, "nome", canteiro.idCanteiro.nome);
  atualizarCanteiro(idCanteiro, "especie", canteiro.especie);
  atualizarCanteiro(idCanteiro, "periodo_rega", canteiro.periodo_rega);
  atualizarCanteiro(idCanteiro, "ph", canteiro.ph);
  atualizarCanteiro(idCanteiro, "umidade", canteiro.umidade);
  atualizarCanteiro(idCanteiro, "descricao", canteiro.descricao);
}

/*
  Retorna um vetor de todos os canteiros registrados
*/
vector<idCanteiros> GerenciadorCanteiros::buscarTodos()
{
  return gerenciadorBD->selecionarCanteiros();
}

/*
  Retorna um vetor de todos os canteiros que contém a substring de pesquisa
  | substring: substring de pesquisa
*/
vector<idCanteiros> GerenciadorCanteiros::buscarPorNome(string substring)
{
  vector<idCanteiros> canteirosFiltrados;
  for(auto it = dict_canteiros.begin(); it != dict_canteiros.end(); it++)  
    if(it->first.find(substring) != -1)
      canteirosFiltrados.push_back(it->second);
  return canteirosFiltrados;
}

/*
  Retorna um vetor de todos os canteiros de uma especie
  | especie: especie de interesse
*/
vector<idCanteiros> GerenciadorCanteiros::buscarPorEspecie(string especie)
{
  return gerenciadorBD->selecionarCanteiros("especie", especie);
}

DadosCanteiro GerenciadorCanteiros::armazenarCanteiro(idCanteiros canteiro)
{
  DadosCanteiro canteiroArmazenado = gerenciadorBD->armazenarLinha(canteiro);
  cout << canteiroArmazenado.idCanteiro.nome << endl;
  cout << canteiroArmazenado.especie << endl;
  cout << to_string(canteiroArmazenado.periodo_rega) << endl;
  cout << to_string(canteiroArmazenado.ph) << endl;
  cout << to_string(canteiroArmazenado.umidade) << endl;
  cout << canteiroArmazenado.descricao << endl;
  return canteiroArmazenado;
}
