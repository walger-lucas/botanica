#ifndef GERENCIADOR_BD_H
#define GERENCIADOR_BD_H

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
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
    string user;
    string password;
    string base_de_dados;
    vector<string> lista_canteiros;

  public:
    GerenciadorBD();
    ~GerenciadorBD();
    int ConectarBD();
    void DesconectarBD();
    int criarCanteiro(string nome, string especie, int periodo_rega, float ph, double umidade, string descricao = "");
    void selecionarCanteiros();
    void removerCanteiro(int id);
};

#endif // GERENCIADOR_BD_H