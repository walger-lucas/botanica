#include "GerenciadorCanteiros.h"

/*
  Construtor da classe GerenciadorCanteiros
*/
GerenciadorCanteiros::GerenciadorCanteiros() 
: gerenciadorBD(new GerenciadorBD)
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
void GerenciadorCanteiros::adicionarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao)
{
  if(dict_canteiros.count(nome) == 0)
  {
    idCanteiros canteiroCriado = gerenciadorBD->criarCanteiro(nome, especie, periodo_rega, ph, umidade, descricao);
    if(!canteiroEhNulo(canteiroCriado))
      dict_canteiros[nome] = canteiroCriado;
    else
      cout << "Não é permitido nomes repetidos" << endl;
  }
  else
    cout << "Não é permitido nomes repetidos" << endl;
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
    dict_canteiros.erase(canteiro.nome);
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
      dict_canteiros.erase(canteiro.nome);
      canteiro.nome = valor;
      dict_canteiros[valor] = canteiro;
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
  Retorna um vetor de todos os canteiros registrados
*/
vector<idCanteiros> GerenciadorCanteiros::buscarTodos()
{
  return gerenciadorBD->selecionarCanteiros();
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

/*
  Retorna uma instância da classe DadosCanteiro com os dados do canteiro requisitado preenchidos
  | canteiro: struct idCanteiros do canteiro de interesse
*/
DadosCanteiro GerenciadorCanteiros::armazenarCanteiro(idCanteiros canteiro)
{
  if(!canteiroEhNulo(canteiro))
  {
    DadosCanteiro canteiroArmazenado = gerenciadorBD->armazenarLinhaCanteiros(canteiro);
    cout << canteiroArmazenado.canteiro.nome << endl;
    cout << canteiroArmazenado.especie << endl;
    cout << to_string(canteiroArmazenado.periodo_rega) << endl;
    cout << to_string(canteiroArmazenado.ph) << endl;
    cout << to_string(canteiroArmazenado.umidade) << endl;
    cout << canteiroArmazenado.descricao << endl;
    return canteiroArmazenado;
  }
}

// int main()
// {
//   GerenciadorCanteiros gerenciadorCanteiros = GerenciadorCanteiros();
// //   // gerenciadorCanteiros.buscarPorNome("Jarra");
// //   // gerenciadorCanteiros.adicionarCanteiro("Jardim Zen", "Bonsai", 15, 14, 55.2, "Canteiro zen de bonsais"); //OK
// //   // gerenciadorCanteiros.atualizarCanteiro(gerenciadorCanteiros.getId("Jardim Zen"), "umidade", 455); //OK, adicionar tratamento de erro de elemento nao existente
// //   // gerenciadorCanteiros.armazenarCanteiro(gerenciadorCanteiros.getId("Jardim Zen"));
// //   gerenciadorCanteiros.removerCanteiro(gerenciadorCanteiros.getId("Jardim")); //OK, adicionar tratamento de erro de elemento nao existente
//   return 0;
// }
