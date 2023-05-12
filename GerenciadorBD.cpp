#include "GerenciadorBD.h"

/*
  Construtor da classe GerenciadorBD
*/
GerenciadorBD::GerenciadorBD() 
: base_de_dados("botanica"), hostname("tcp://127.0.0.1:3306"), usuario("botanica"), senha("$Bromelia5")
{
  GerenciadorBD::conectarBD();

  stmt->execute("CREATE DATABASE IF NOT EXISTS " + base_de_dados);
  con->setSchema(base_de_dados);

  stmt->execute("CREATE TABLE IF NOT EXISTS canteiros (id INT AUTO_INCREMENT PRIMARY KEY, nome VARCHAR(50) NOT NULL, especie VARCHAR(50) NOT NULL, periodo_rega INT NOT NULL, ph FLOAT NOT NULL, umidade DOUBLE NOT NULL, descricao TEXT, criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP, n_relatorios INT DEFAULT 0)  ENGINE=INNODB;");
  stmt->execute("CREATE TABLE IF NOT EXISTS relatorios(id INT AUTO_INCREMENT PRIMARY KEY, nome varchar(100), ph_atual float, umidade_atual double, saude tinytext, obs text, data timestamp DEFAULT CURRENT_TIMESTAMP, id_cant int NOT NULL, FOREIGN KEY (id_cant) REFERENCES canteiros(id)) ENGINE=INNODB;");    
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
  Retorna se o nome de interesse já existe na tabela canteiros
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
  Retorna a struct idCanteiros para cada canteiro criado | canteiroNulo se 
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
    canteiro = CANTEIRO_NULO;
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
  Descarta uma linha da tabela canteiros e os seus relatorios a partir do seu nome
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
  stmt->execute("UPDATE canteiros SET " + coluna + "=" + "'" + valor + "' WHERE id=" + to_string(id));
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

/*
  Retorna uma instância da classe DadosCanteiro com os dados do canteiro requisitado preenchidos
  | canteiro: struct idCanteiros do canteiro de interesse
*/
DadosCanteiro GerenciadorBD::armazenarLinhaCanteiros(idCanteiros canteiro)
{
  res = stmt->executeQuery("SELECT * FROM canteiros WHERE id=" + to_string(canteiro.id));
  while (res->next()) 
  {
    return DadosCanteiro(canteiro, res->getString("especie"), res->getInt("periodo_rega"), res->getDouble("ph"), res->getDouble("umidade"), res->getString("descricao"));
  }
}

idRelatorios GerenciadorBD::criarRelatorio(idCanteiros canteiro, string nome, float ph, double umidade, string saude, string obs)
{
  idRelatorios relatorio;
  int id_rel = -1;

  res = stmt->executeQuery("SELECT n_relatorios FROM canteiros WHERE id=" + to_string(canteiro.id));
  while (res->next())
  {
    id_rel = res->getInt("n_relatorios");
    stmt->execute("UPDATE canteiros SET n_relatorios = " + to_string(id_rel+1) + " WHERE id=" + to_string(canteiro.id));
  }
  
  if(id_rel > -1){
    double campos_num[2] = {ph, umidade};
    string campos_string[2] = {saude, obs};
    string campos[4] = {"ph", "umidade", "saude", "obs"};
    string query = "INSERT INTO canteiros (id_cant, nome";
    string valores = " VALUES (" + to_string(canteiro.id) + ",'" + nome + "',";
    for(int i=0, j=0; i<2, j<2; i++, j++){
      if(campos_num[i] != -1){
        query+=", " + campos[j];
        valores+=", " + to_string(campos_num[i]) + "";
      }
    }
    for(int i=0, j=2; i<2, j<4; i++, j++){
      if(!campos_string[i].empty()){
        query+=", " + campos[j];
        valores+=", '" + campos_string[i] + "'";
      }
   }
    query += ")" + valores + ")";
    stmt->execute(query);

    relatorio.id_cant = canteiro.id;
    relatorio.nome = canteiro.nome + to_string(id_rel);
  }
  relatorio.id_rel = id_rel;

  return relatorio;
}

