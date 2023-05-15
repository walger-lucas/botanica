#include "GerenciadorCanteiros.h"

/*
  Construtor da classe GerenciadorCanteiros
*/
GerenciadorCanteiros::GerenciadorCanteiros() 
: gerenciadorBD(new GerenciadorBD())
{
  idCanteiros::dict_canteiros.clear();
  // Recebe as idCanteiros dos canteiros registrados no banco de dados
  vector<idCanteiros> canteiros = gerenciadorBD->selecionarCanteiros();
  // Armazena as idCanteiros em um dicionário a partir do nome
  for(auto it = canteiros.begin(); it != canteiros.end(); it++)
    idCanteiros::dict_canteiros[it->nome] = *it;
}

/*
  Desconstrutor da classe GerenciadorBD
*/
GerenciadorCanteiros::~GerenciadorCanteiros()
{
  if(gerenciadorBD)
    delete gerenciadorBD;
}

/*
  Retorna a struct idCanteiros atraves do nome do canteiro
  | nome: nome do canteiro
*/
idCanteiros GerenciadorCanteiros::getId(string nome)
{
  try
  {
    return idCanteiros::dict_canteiros.at(nome);
  }
  catch(const std::exception& e)
  {
    std::cerr << "Canteiro não encontrado" << '\n';
    return CANTEIRO_NULO;
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

  if(idCanteiros::dict_canteiros.count(nome) == 0 && nome!="")
  {
    idCanteiros canteiroCriado = gerenciadorBD->criarCanteiro(nome, especie, periodo_rega, ph, umidade, descricao);
    if(!canteiroEhNulo(canteiroCriado))
      idCanteiros::dict_canteiros[nome] = canteiroCriado;
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
bool GerenciadorCanteiros::adicionarCanteiro(const DadosCanteiro dadosCanteiro)
{
  return adicionarCanteiro(dadosCanteiro.canteiro.nome, dadosCanteiro.especie, dadosCanteiro.periodo_rega, dadosCanteiro.ph, dadosCanteiro.umidade, dadosCanteiro.descricao);
}

/*
  Remove um canteiro do registro
  | canteiro: struct idCanteiros do canteiro de interesse
*/
void GerenciadorCanteiros::removerCanteiro(idCanteiros canteiro)
{
  if(!canteiroEhNulo(canteiro))
  {
    gerenciadorBD->descartarCanteiro(canteiro);
    idCanteiros::dict_canteiros.erase(canteiro.nome);
  }
}

/*
  Atualiza um parametro de um canteiro
  | canteiro: struct idCanteiros do canteiro de interesse
  | parametro: parametro de interesse ("nome", "especie" ou "descricao")
  | valor: valor string que vai substituir o valor antigo
*/
void GerenciadorCanteiros::atualizarCanteiro(idCanteiros canteiro, string parametro, string valor)
{
  if(!canteiroEhNulo(canteiro))
  {
    gerenciadorBD->atualizarCanteiro(canteiro, parametro, valor);
    if(parametro == "nome")
    {
      idCanteiros::dict_canteiros.erase(canteiro.nome);
      canteiro.nome = valor;
      idCanteiros::dict_canteiros[valor] = canteiro;
    }
  }
}


/*
  Atualiza um parametro de um canteiro
  | canteiro: struct idCanteiros do canteiro de interesse
  | parametro: parametro de interesse ("nome", "especie" ou "descricao")
  | valor: valor string que vai substituir o valor antigo
*/
void GerenciadorCanteiros::atualizarCanteiro(idCanteiros canteiro, string parametro, double valor)
{
  if(!canteiroEhNulo(canteiro))
    gerenciadorBD->atualizarCanteiro(canteiro, parametro, valor);
}

/*
  Atualiza todos os parametros de um canteiro 
  | canteiro: instância DadosCanteiro
*/
void GerenciadorCanteiros::atualizarCanteiro(idCanteiros canteiro, const DadosCanteiro dadosCanteiro)
{
  atualizarCanteiro(canteiro, "nome", dadosCanteiro.canteiro.nome);
  atualizarCanteiro(canteiro, "especie", dadosCanteiro.especie);
  atualizarCanteiro(canteiro, "periodo_rega", dadosCanteiro.periodo_rega);
  atualizarCanteiro(canteiro, "ph", dadosCanteiro.ph);
  atualizarCanteiro(canteiro, "umidade", dadosCanteiro.umidade);
  atualizarCanteiro(canteiro, "descricao", dadosCanteiro.descricao);
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
  for(auto it = idCanteiros::dict_canteiros.begin(); it != idCanteiros::dict_canteiros.end(); it++)  
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

/*
  Retorna uma instância da classe DadosCanteiro com os dados do canteiro requisitado preenchidos
  | canteiro: struct idCanteiros do canteiro de interesse
*/
DadosCanteiro GerenciadorCanteiros::armazenarCanteiro(idCanteiros canteiro)
{
  if(!canteiroEhNulo(canteiro))
    return gerenciadorBD->armazenarLinhaCanteiros(canteiro);
  else
    return DadosCanteiro(CANTEIRO_NULO, "", 0, -1, -1, "ERRO NO ARMAZENAMENTO - CANTEIRO_NULO");
}