#pragma once

#include "Canteiro.h"
#include "Relatorio.h"
#include <vector>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

class GerenciadorBD
{
  private:
    Driver* driver;
    Connection* con;
    Statement* stmt;
    PreparedStatement *pstmt;
    ResultSet* res;
    string hostname;
    string usuario;
    string senha;
    string base_de_dados;

  public:
    GerenciadorBD();
    ~GerenciadorBD();
    int conectarBD();
    void desconectarBD();
    bool mesmoNome(string nome);
    idCanteiros criarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao = "");
    void descartarCanteiro(idCanteiros canteiro);
    void atualizarCanteiro(idCanteiros canteiro, string coluna, double valor);
    void atualizarCanteiro(idCanteiros canteiro, string coluna, string valor);
    vector<idCanteiros> selecionarCanteiros(string parametro = "", string valor = "");
    DadosCanteiro armazenarLinhaCanteiros(idCanteiros canteiros);
    idRelatorios criarRelatorio(idCanteiros canteiro, string nome, float ph = -1, double umidade = -1, string saude = "", string obs = "");
    void descartarRelatorio(idRelatorios relatorio);
    DadosRelatorio armazenarLinhaRelatorios(idRelatorios relatorio);
};