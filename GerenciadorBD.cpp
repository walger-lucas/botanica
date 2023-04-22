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
int GerenciadorBD::criarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao)
{
  res = stmt->executeQuery("SELECT id FROM canteiros WHERE nome='" + nome + "'");
  while (res->next()) 
  {
    if(res->getInt("id") != 0)
    {
      cout << "Nomes repetidos nao sao permitidos" << endl;
      return -1;
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

  lista_canteiros.push_back(nome);

  res = stmt->executeQuery("SELECT id FROM canteiros WHERE nome='" + nome + "'");
  int id = -1;
  while (res->next()) 
  {
    id = res->getInt("id");
  }

  return id;
}

void GerenciadorBD::removerCanteiro(int id)
{
  stmt->executeQuery("DELETE FROM canteiros WHERE id=" + id);
  // Adicionar remoção da lista de canteiros
}

void GerenciadorBD::selecionarCanteiros() 
{
  res = stmt->executeQuery("SELECT * FROM canteiros");

  while (res->next()) {
    int id = res->getInt("id");
    string name = res->getString("nome");
    cout << "ID: " << id << ", Name: " << name << endl;
  }
}

int main()
{
  GerenciadorBD gerenciadorBD = GerenciadorBD();
  gerenciadorBD.criarCanteiro("Bromelia 1", "Bromelia", 6, 7.0, 10.5);
  gerenciadorBD.selecionarCanteiros();
  return 0;
}


