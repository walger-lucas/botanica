#include "GerenciadorBD.h"

using namespace std;

GerenciadorBD::GerenciadorBD()
{
  base_de_dados = "botanica";

  GerenciadorBD::ConectarBD();

  string query = "CREATE DATABASE IF NOT EXISTS ";
  query+=base_de_dados;
  stmt->execute(query);
  con->setSchema(base_de_dados);

  stmt->execute("CREATE TABLE IF NOT EXISTS canteiros (id INT AUTO_INCREMENT PRIMARY KEY, nome VARCHAR(50) NOT NULL, especie VARCHAR(50) NOT NULL, status TINYTEXT,periodo_rega INT NOT NULL, ph FLOAT NOT NULL, umidade DOUBLE NOT NULL, descricao TEXT, criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP)  ENGINE=INNODB;");  
}

GerenciadorBD::~GerenciadorBD()
{
  GerenciadorBD::DesconectarBD();
}

int GerenciadorBD::ConectarBD()
{
  string hostname = "tcp://127.0.0.1:3306";
  string usuario = "botanica";
  string senha = "$Bromelia5";

  driver = get_driver_instance();
  con = driver->connect(hostname, usuario, senha);
  
  stmt = con->createStatement();
}

void GerenciadorBD::DesconectarBD()
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

// Retorna a ID do Canteiro
idCanteiros GerenciadorBD::criarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao)
{
  res = stmt->executeQuery("SELECT id FROM canteiros WHERE nome='" + nome + "'");
  while (res->next()) 
  {
    if(res->getInt("id") != 0)
    {
      cout << "Nomes repetidos nao sao permitidos" << endl;
    }
  }

  string query = "INSERT INTO canteiros (nome, especie, periodo_rega, ph, umidade";
  string valores = " VALUES ('" + nome + "','" + especie + "'," + to_string(periodo_rega) + "," + to_string(ph) + "," + to_string(umidade);
  if(!descricao.empty())
  {
    query+=", descricao";
    valores+=", '" + descricao + "'";
  }
  query += ")" + valores + ")";
  stmt->execute(query);

  res = stmt->executeQuery("SELECT id FROM canteiros WHERE nome='" + nome + "'");

  idCanteiros canteiro;

  while (res->next()) 
  {
    canteiro.id = res->getInt("id");
    canteiro.nome = res->getInt("nome");
  }

  return canteiro;
}

void GerenciadorBD::descartarCanteiro(string nome)
{
  res = stmt->executeQuery("DELETE FROM canteiros WHERE nome='" + nome + "'");
  cout << res << endl;
}

// Parametro deve ser somente nome ou especie
vector<idCanteiros> GerenciadorBD::selecionarCanteiros(string parametro, string valor) 
{
  if(parametro != "" && valor != "")
  {
    res = stmt->executeQuery("SELECT * FROM canteiros WHERE "+parametro+"='"+valor+"'");
  }
  else
    res = stmt->executeQuery("SELECT * FROM canteiros");

  vector<idCanteiros> lista_canteiros;

  while (res->next()) {
    idCanteiros canteiro;
    int id = res->getInt("id");
    string nome = res->getString("nome");
    cout << "ID: " << id << ", Name: " << nome << endl;
    canteiro.id = id;
    canteiro.nome = nome;
    lista_canteiros.push_back(canteiro);
  }
  return lista_canteiros;
}


