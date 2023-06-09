#include "GerenciadorBD.h"

/*
  Construtor da classe GerenciadorBD
*/
GerenciadorBD::GerenciadorBD() 
: base_de_dados("botanica"), hostname("tcp://127.0.0.1:3306"), usuario("botanica"), senha("$Bromelia5")
{
  GerenciadorBD::conectarBD();

  // Cria a base de dados
  stmt->execute("CREATE DATABASE IF NOT EXISTS " + base_de_dados);
  con->setSchema(base_de_dados);

  // Cria as tabelas
  stmt->execute("CREATE TABLE IF NOT EXISTS canteiros (id INT AUTO_INCREMENT PRIMARY KEY, nome VARCHAR(50) NOT NULL, especie VARCHAR(50) NOT NULL, periodo_rega INT NOT NULL, ph FLOAT NOT NULL, umidade DOUBLE NOT NULL, descricao TEXT, criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP, n_relatorios INT DEFAULT 0, prox_rega CHAR(19) DEFAULT '2001-01-01 00:00:00')  ENGINE=INNODB;");
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
bool GerenciadorBD::conectarBD()
{
  try {
    driver = get_driver_instance();
    con = driver->connect(hostname, usuario, senha);
    stmt = con->createStatement();
    return true;
  } catch (sql::SQLException &e) {
    cout << e.what() << endl;
    return false;
  }
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
    cout << e.what() << endl;
  }
  if(con!=nullptr)
    delete con;
  if(stmt!=nullptr)
    delete stmt;
  if(pstmt!=nullptr)
    delete pstmt;
  if(res!=nullptr)
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
    // Cria linha e adiciona os parâmetros
    string query = "INSERT INTO canteiros (nome, especie, periodo_rega, ph, umidade";
    string valores = " VALUES ('" + nome + "','" + especie + "'," + to_string(periodo_rega) + "," + to_string(ph) + "," + to_string(umidade);
    if(!descricao.empty())
    {
      query+=", descricao";
      valores+=", '" + descricao + "'";
    }
    query += ")" + valores + ")";
    stmt->execute(query);

    // Cria a struct idCanteiros
    res = stmt->executeQuery("SELECT id FROM canteiros WHERE nome='" + nome + "'");
    while (res->next()) 
      canteiro.id = res->getInt("id");
    canteiro.nome = nome;
    GerenciadorBD::atualizarProxRega(&canteiro);
  }
  return canteiro;
}

/*
  Descarta uma linha da tabela canteiros e os seus relatorios a partir do seu nome
  | canteiro: struct idCanteiros do canteiro a ser descartado
*/
void GerenciadorBD::descartarCanteiro(idCanteiros canteiro)
{
  stmt->execute("DELETE FROM relatorios WHERE id_cant=" + to_string(canteiro.id));
  stmt->execute("DELETE FROM canteiros WHERE id=" + to_string(canteiro.id));
}

/*
  Atualiza parametro de canteiro
  | canteiro: struct idCanteiros do canteiro a ser atualizado
  | coluna: parametro ("nome", "especie" ou "descricao") do canteiro a ser atualizado
  | valor: valor string que vai substituir o valor antigo
*/
void GerenciadorBD::atualizarCanteiro(idCanteiros canteiro, string coluna, string valor)
{
  stmt->execute("UPDATE canteiros SET " + coluna + "=" + "'" + valor + "' WHERE id=" + to_string(canteiro.id));
}

/*
  Atualiza parametro de canteiro 
  |canteiro: struct idCanteiros do canteiro a ser atualizado
  | coluna: parametro ("ph", "periodo_rega" ou "umidade") do canteiro a ser atualizado
  | valor: valor numérico que vai substituir o valor antigo
*/
void GerenciadorBD::atualizarCanteiro(idCanteiros canteiro, string coluna, double valor)
{
  stmt->execute("UPDATE canteiros SET " + coluna + "=" + to_string(valor) + " WHERE id=" + to_string(canteiro.id));
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
  // Sem parâmetros de busca retorna todos os canteiros
  else
    res = stmt->executeQuery("SELECT * FROM canteiros");

  // Cria a lista de canteiros buscados
  vector<idCanteiros> lista_canteiros;
  while (res->next()) {
    idCanteiros canteiro;
    canteiro.id = res->getInt("id");
    canteiro.nome = res->getString("nome");
    // cout << canteiro.prox_rega << endl;
    lista_canteiros.push_back(canteiro);
  }

  // Adiciona a lista de relatorios para cada canteiro
  for(auto it = lista_canteiros.begin(); it != lista_canteiros.end(); it++)
  {
    it->relatorios = selecionarRelatorios(it->id);
    GerenciadorBD::atualizarProxRega(&(*it));
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
  return DadosCanteiro(CANTEIRO_NULO, "", 0, -1, -1, "ERRO NO ARMAZENAMENTO - CANTEIRO_NULO");
}

idRelatorios GerenciadorBD::criarRelatorio(idCanteiros canteiro, string nome, float ph, double umidade, string saude, string obs)
{
  idRelatorios relatorio;
  // Atualiza valor do id de acordo com o numero de relatorios
  res = stmt->executeQuery("SELECT n_relatorios FROM canteiros WHERE id=" + to_string(canteiro.id));
  while (res->next())
  {
    int n_relatorios = res->getInt("n_relatorios");
    stmt->execute("UPDATE canteiros SET n_relatorios = " + to_string(n_relatorios+1) + " WHERE id=" + to_string(canteiro.id));
  }
  
  // Cria linha e adiciona os parâmetros
  string query = "INSERT INTO relatorios (id_cant, nome";
  string valores = " VALUES (" + to_string(canteiro.id) + ",'" + nome + "'";
  string campos[4] = {"ph_atual", "umidade_atual", "saude", "obs"};
  

  //// Parâmetros opcionais numéricos (-1 significa nulo)
  double campos_num[2] = {ph, umidade};
  for(int i=0, j=0; i<2, j<2; i++, j++){
    if(campos_num[i] != -1){
      query+=", " + campos[j];
      valores+=", " + to_string(campos_num[i]) + "";
    }
  }

  //// Parâmetros opcionais string
  string campos_string[2] = {saude, obs};
  for(int i=0, j=2; i<2, j<4; i++, j++){
    if(!campos_string[i].empty()){
      query+=", " + campos[j];
      valores+=", '" + campos_string[i] + "'";
    }
  }

  query += ")" + valores + ")";
  cout << query << endl;
  stmt->execute(query);

  // Cria a struct idRelatorio
  res = stmt->executeQuery("SELECT id FROM relatorios WHERE nome='" + nome + "'");
  while (res->next()) 
    relatorio.id = res->getInt("id");
  relatorio.nome = nome;
  relatorio.id_cant = canteiro.id;

  return relatorio;
}

/*
  Descarta uma linha da tabela relatorios
  | relatorio: struct idCanteiros do relatorio a ser descartado
*/
void GerenciadorBD::descartarRelatorio(idRelatorios relatorio)
{
  stmt->execute("DELETE FROM relatorios WHERE id=" + to_string(relatorio.id));
}

/*
  Retorna vetor de todos os idRelatorios
*/
vector<idRelatorios> GerenciadorBD::selecionarRelatorios(int id_cant) 
{
  if(id_cant != -1)
    res = stmt->executeQuery("SELECT * FROM relatorios WHERE id_cant="+to_string(id_cant));
  // Sem parâmetros de busca retorna todos os canteiros
  else
    res = stmt->executeQuery("SELECT * FROM relatorios");

  // Cria a lista de canteiros buscados
  vector<idRelatorios> lista_relatorios;
  while (res->next()) {
    idRelatorios relatorio;
    relatorio.id = res->getInt("id");
    relatorio.nome = res->getString("nome");
    relatorio.id_cant = res->getInt("id_cant");
    lista_relatorios.push_back(relatorio);
  }
  return lista_relatorios;
}

/*
  Retorna uma instância da classe DadosRelatorio com os dados do relatorio requisitado preenchidos
  | relatorio: struct idRelatorios do relatorio de interesse
*/
DadosRelatorio GerenciadorBD::armazenarLinhaRelatorios(idRelatorios relatorio)
{
  res = stmt->executeQuery("SELECT * FROM relatorios WHERE id=" + to_string(relatorio.id));
  while (res->next()) 
  {
    return DadosRelatorio(relatorio, res->getString("data"), res->getDouble("ph_atual"), res->getDouble("umidade_atual"), res->getString("saude"), res->getString("obs"));
  }
  return DadosRelatorio(RELATORIO_NULO, "", -1, -1, "", "ERRO NO ARMAZENAMENTO - BANCO DE DADOS");
}

/*
  Retorna uma data em formato string convertida para o tipo time_t
  | sdata: data em string
*/
time_t GerenciadorBD::stringParaData(string sdata)
{
  // Extrai a data da string
  boost::posix_time::ptime data = boost::posix_time::time_from_string(sdata);
  // Converte para o tipo time_t
  time_t tdata = boost::posix_time::to_time_t(data);
  return tdata;
}

/*
  Retorna uma data em formato time_t convertida para o tipo string
  | tdata: data em time_t
*/
string GerenciadorBD::dataParaString(time_t tdata)
{
  stringstream ss;
  // Formata a data
  ss << put_time(localtime(&tdata), "%Y-%m-%d %H:%M:%S");
  // Converte para o tipo string
  string sdata = ss.str();
  return sdata;
}

/*
  Retorna uma data em formato time_t com adicao de um numero de horas dado pelo usuário
  | tdata: data em time_t
  | horas: numero de horas
*/
time_t GerenciadorBD::incrementarData(time_t tdata, int horas)
{
  // Converte time_t para a struct tm
  tm* data = localtime(&tdata);
  // Incrementa as horas
  data->tm_hour += horas;
  // Normaliza a formatacao do tempo
  mktime(data);
  // Converte da struct tm para time_t
  time_t nova_data = mktime(data);
  return nova_data;
}

/*
  Atualiza a proxima data de rega para o canteiro selecionado, no banco de dados e na própria idCanteiros dele
  | *canteiro: ponteiro para o canteiro de interesse
*/
void GerenciadorBD::atualizarProxRega(idCanteiros *canteiro)
{
  res = stmt->executeQuery("SELECT prox_rega, criado_em, periodo_rega FROM canteiros WHERE id=" + to_string(canteiro->id));
  while (res->next())
  {
    string prox_rega;
    time_t t_prox_rega;

    int periodo = res->getInt("periodo_rega");
    string s_rega_atual = res->getString("prox_rega").asStdString();
    string s_criado = res->getString("criado_em").asStdString();

    time_t t_rega_atual = GerenciadorBD::stringParaData(s_rega_atual);
    time_t t_criado = GerenciadorBD::stringParaData(s_criado);
    time_t tempo_atual = time(nullptr);
  
    time_t data_base;
    if(s_rega_atual == "01/01/2001 00:00:00")
      data_base = t_criado;
    else
      data_base = t_rega_atual;

    if(t_rega_atual < tempo_atual)
    {
      for(t_prox_rega = t_criado; t_prox_rega < tempo_atual; t_prox_rega=GerenciadorBD::incrementarData(t_prox_rega, periodo));
      prox_rega = dataParaString(t_prox_rega);
      stmt->execute("UPDATE canteiros SET prox_rega='" + prox_rega + "' WHERE id=" + to_string(canteiro->id));
    }
    else
    {
      t_prox_rega = t_rega_atual;
      prox_rega = dataParaString(t_prox_rega);
    }
    canteiro->prox_rega = prox_rega.substr(0,10);
  }
}
