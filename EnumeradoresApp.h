#pragma once

//IDs para funcoes de menu
enum MenuID
{
    ID_NEW_CANTEIRO = 1,
    ID_OPEN_CANTEIRO,
    ID_NEW_RELATORIO,
    ID_OPEN_RELATORIO,
    ID_OPEN_CRONOGRAMA,
    //Adicionar novos IDS acima
    ID_MAX
};

//IDs das Janelas controladas por GerenciadorJanela
enum Janelas
{
    J_VER_CANTEIRO = 0,
    J_ADD_CANTEIRO,
    /*J_ADD_RELATORIO,
    J_VER_RELATORIO,
    J_CRONOGRAMA,*/
    //Adicionar novas janelas aqui.
    J_MAX
};