#include "GerenciadorRelatorios.h"

/*
  Construtor da classe GerenciadorRelatorios
*/
GerenciadorRelatorios::GerenciadorRelatorios() 
: gerenciadorBD(new GerenciadorBD)
{
  idRelatorios::dict_relatorios.clear();
  // Recebe as idRelatorios dos relatorios registrados no banco de dados
  vector<idRelatorios> relatorios = gerenciadorBD->selecionarRelatorios();
  // Armazena as idRelatorios em um dicionário a partir do nome
  for(auto it = relatorios.begin(); it != relatorios.end(); it++)
   idRelatorios::dict_relatorios[it->nome] = *it;
}

/*
  Desconstrutor da classe GerenciadorBD
*/
GerenciadorRelatorios::~GerenciadorRelatorios()
{
  delete gerenciadorBD;
}

/*
  Retorna a struct idRelatorios atraves do nome do relatorio
  | nome: nome do relatorio
*/
idRelatorios GerenciadorRelatorios::getId(string nome)
{
  try
  {
    return idRelatorios::dict_relatorios.at(nome);
  }
  catch(const std::exception& e)
  {
    std::cerr << "Relatorio não encontrado" << '\n';
    return RELATORIO_NULO;
  }
}

/*
  Adiciona um novo relatorio ao registro
  | nome: nome do relatorio (não é permitido repetição)
  | especie: especie da planta do relatorio
  | periodo_rega: período entre as regas
  | ph: ph ideal da planta
  | umidade: umidade ideal da planta
  | descricao (opcional): descricao do relatorio
*/
void GerenciadorRelatorios::adicionarRelatorio(idCanteiros canteiro, string nome, float ph, double umidade, string saude, string obs)
{
  if(idRelatorios::dict_relatorios.count(nome) == 0)
  {
    idRelatorios relatorioCriado = gerenciadorBD->criarRelatorio(canteiro, nome, ph, umidade, saude, obs);
    if(!relatorioEhNulo(relatorioCriado))
    {
      idRelatorios::dict_relatorios[nome] = relatorioCriado;
      idCanteiros::dict_canteiros[canteiro.nome].relatorios.push_back(relatorioCriado);
    }
    else
      cout << "Não é permitido nomes repetidos" << endl;
  }
  else
    cout << "Não é permitido nomes repetidos" << endl;
}

/*
  Remove um relatorio do registro
  | relatorio: struct idRelatorios do relatorio de interesse
*/
void GerenciadorRelatorios::removerRelatorio(idRelatorios relatorio)
{
  if(!relatorioEhNulo(relatorio))
  {
    gerenciadorBD->descartarRelatorio(relatorio);
    idRelatorios::dict_relatorios.erase(relatorio.nome);
    for(auto it = idCanteiros::dict_canteiros.begin(); it != idCanteiros::dict_canteiros.end(); it++)
      if(it->second.id == relatorio.id_cant)
        it->second.relatorios = removerDaLista(it->second.relatorios, relatorio);
  }
}

/*
  Retorna um vetor de todos os relatorios registrados
*/
vector<idRelatorios> GerenciadorRelatorios::buscarTodos()
{
  return gerenciadorBD->selecionarRelatorios();
}

/*
  Retorna um vetor de todos os relatorios que contém a substring de pesquisa
  | substring: substring de pesquisa
*/
vector<idRelatorios> GerenciadorRelatorios::buscarPorNome(string substring)
{
  vector<idRelatorios> relatoriosFiltrados;
  for(auto it = idRelatorios::dict_relatorios.begin(); it != idRelatorios::dict_relatorios.end(); it++)  
    if(it->first.find(substring) != -1)
      relatoriosFiltrados.push_back(it->second);
  return relatoriosFiltrados;
}

/*
  Retorna uma instância da classe DadosRelatorio com os dados do relatorio requisitado preenchidos
  | relatorio: struct idRelatorios do relatorio de interesse
*/
DadosRelatorio GerenciadorRelatorios::armazenarRelatorio(idRelatorios relatorio)
{
  if(!relatorioEhNulo(relatorio))
    return gerenciadorBD->armazenarLinhaRelatorios(relatorio);
  else
    return DadosRelatorio(RELATORIO_NULO, "", -1, -1, "", "ERRO NO ARMAZENAMENTO - RELATORIO NULO");
}
