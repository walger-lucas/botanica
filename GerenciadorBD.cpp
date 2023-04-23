#include "GerenciadorBD.h"


/*
  Construtor da classe GerenciadorBD
*/
GerenciadorBD::GerenciadorBD()
{
  base_de_dados = "botanica";

  GerenciadorBD::conectarBD();

  string query = "CREATE DATABASE IF NOT EXISTS ";
  query+=base_de_dados;
  stmt->execute(query);
  con->setSchema(base_de_dados);

  stmt->execute("CREATE TABLE IF NOT EXISTS canteiros (id INT AUTO_INCREMENT PRIMARY KEY, nome VARCHAR(50) NOT NULL, especie VARCHAR(50) NOT NULL, status TINYTEXT,periodo_rega INT NOT NULL, ph FLOAT NOT NULL, umidade DOUBLE NOT NULL, descricao TEXT, criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP)  ENGINE=INNODB;");  
}


/*
  Desconstrutor da classe GerenciadorBD
*/
GerenciadorBD::~GerenciadorBD()
{
  GerenciadorBD::desconectarBD();
}


/*
  Retorna status de conexão
  Conecta ao servidor local do banco de dados
*/
int GerenciadorBD::conectarBD()
{
  string hostname = "tcp://127.0.0.1:3306";
  string usuario = "botanica";
  string senha = "$Bromelia5";

  driver = get_driver_instance();
  con = driver->connect(hostname, usuario, senha);
  
  stmt = con->createStatement();
}

/*
  Desconecta do servidor local do banco de dados e desconstroi os parametros de classe
*/
void GerenciadorBD::desconectarBD()
{
  if (stmt) stmt->close();
  if (pstmt) pstmt->close();
  if (con) con->close();
  try {
    driver = get_driver_instance();
    driver->threadEnd();
  } catch (sql::SQLException &e) {
    // do nothing
  }
  delete con;
  delete stmt;
  delete pstmt;
  delete res;
}

/*
  Retorna se o nome de interesse já existe no banco de dados
  | nome: nome de interesse
*/
bool GerenciadorBD::mesmoNome(string nome)
{
  res = stmt->executeQuery("SELECT id FROM canteiros WHERE nome='" + nome + "'");
  while (res->next()) 
  {
    if(res->getInt("id") != 0)
    {
      cout << "Nomes repetidos nao sao permitidos" << endl;
      return true;
    }
  }
  return false;
}
/*
  Retorna a struct idCanteiros para cada canteiro criado | id = -1 se o nome for repetido
  | nome: nome do canteiro (não é permitido repetição)
  | especie: especie da planta do canteiro
  | periodo_rega: período entre as regas
  | ph: ph ideal da planta
  | umidade: umidade ideal da planta
  | descricao (opcional): descricao do canteiro
*/
idCanteiros GerenciadorBD::criarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao)
{
  idCanteiros canteiro;

  if(GerenciadorBD::mesmoNome(nome))
  {
    canteiro.id = -1;
  }
  else
  {
    string query = "INSERT INTO canteiros (nome, especie, periodo_rega, ph, umidade";
    string valores = " VALUES ('" + nome + "','" + especie + "'," + to_string(periodo_rega) + "," + to_string(ph) + "," + to_string(umidade);
    if(!descricao.empty())
    {
      query+=", descricao";
      valores+=", '" + descricao + "'";
    }
    query += ")" + valores + ")";
    stmt->execute(query);

    res = stmt->executeQuery("SELECT * FROM canteiros WHERE nome='" + nome + "'");
    while (res->next()) 
    {
      canteiro.id = res->getInt("id");
      canteiro.nome = res->getInt("nome");
    }
  }
  return canteiro;
}

/*
  Descarta uma linha do banco de dados a partir do seu nome
  | nome: nome do canteiro a ser descartado
*/
void GerenciadorBD::descartarCanteiro(int id)
{
  stmt->execute("DELETE FROM canteiros WHERE id=" + to_string(id));
}

/*
  Atualiza parametro de canteiro 
  | nome: nome do canteiro a ser atualizado
  | coluna: parametro ("nome", "especie" ou "descricao") do canteiro a ser atualizado
  | valor: valor string que vai substituir o valor antigo
*/
void GerenciadorBD::atualizarCanteiro(int id, string coluna, string valor)
{
  string query = "UPDATE canteiros SET " + coluna + "=";
  // if(coluna == "nome" && GerenciadorBD::mesmoNome(nome))
  //   return;
  query += "'" + valor + "' WHERE id=" + to_string(id);
  stmt->execute(query);
}

/*
  Atualiza parametro de canteiro 
  | nome: nome do canteiro a ser atualizado
  | coluna: parametro ("ph", "periodo_rega" ou "umidade") do canteiro a ser atualizado
  | valor: valor numérico que vai substituir o valor antigo
*/
void GerenciadorBD::atualizarCanteiro(int id, string coluna, double valor)
{
  stmt->execute("UPDATE canteiros SET " + coluna + "=" + to_string(valor) + " WHERE id=" + to_string(id));
}

/*
  Retorna vetor de idCanteiros para cada canteiro selecionado 
  | coluna: parametro de busca ("nome" ou "especie")
  | valor: valor string de filtro
*/
vector<idCanteiros> GerenciadorBD::selecionarCanteiros(string coluna, string valor) 
{
  if(coluna != "" && valor != "")
  {
    res = stmt->executeQuery("SELECT * FROM canteiros WHERE "+coluna+"='"+valor+"'");
  }
  else
    res = stmt->executeQuery("SELECT * FROM canteiros");

  vector<idCanteiros> lista_canteiros;

  while (res->next()) {
    idCanteiros canteiro;
    canteiro.id = res->getInt("id");
    canteiro.nome = res->getString("nome");
    lista_canteiros.push_back(canteiro);
  }
  return lista_canteiros;
}

DadosCanteiro GerenciadorBD::armazenarLinha(idCanteiros canteiro)
{
  res = stmt->executeQuery("SELECT * FROM canteiros WHERE id=" + to_string(canteiro.id));
  while (res->next()) 
  {
    return DadosCanteiro(canteiro, res->getString("especie"), res->getInt("periodo_rega"), res->getDouble("ph"), res->getDouble("umidade"), res->getString("descricao"));
  }
}

