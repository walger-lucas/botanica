// #include "GerenciadorCanteiros.h"
// #include "GerenciadorRelatorios.h"

// void showRelatorio(idRelatorios relatorio)
// {
//     cout << "-----idRelatorio-----" << endl;
//     cout << "id: " + to_string(relatorio.id) << endl;
//     cout << "nome: " + relatorio.nome << endl;
//     cout << "id_cant: " + to_string(relatorio.id_cant) << endl;
// }

// void showCanteiro(idCanteiros canteiro)
// {
//     cout << "-----idCanteiro-----" << endl;
//     cout << "id: " + to_string(canteiro.id) << endl;
//     cout << "nome: " + canteiro.nome << endl;
//     cout << "relatorios: " << endl;
//     for(auto it = canteiro.relatorios.begin(); it != canteiro.relatorios.end(); it++)
//         showRelatorio(*it);
// }

// void showDictCanteiros(vector<idCanteiros> canteiros)
// {
//     for(auto it = canteiros.begin(); it != canteiros.end(); it++)
//         showCanteiro(*it);
// }

// void showDictRelatorios(vector<idRelatorios> relatorios)
// {
//     for(auto it = relatorios.begin(); it != relatorios.end(); it++)
//         showRelatorio(*it);
// }

// void showDadosCanteiro(DadosCanteiro dadosCanteiro)
// {
//     cout << "-----dadosCanteiro-----" << endl;
//     showCanteiro(dadosCanteiro.canteiro);
//     cout << "especie: " + dadosCanteiro.especie << endl;
//     cout << "periodo rega: " + to_string(dadosCanteiro.periodo_rega) << endl;
//     cout << "ph: " + to_string(dadosCanteiro.ph) << endl;
//     cout << "umidade: " + to_string(dadosCanteiro.umidade) << endl;
//     cout << "descricao: " + dadosCanteiro.descricao << endl;
// }

// void showDadosRelatorio(DadosRelatorio dadosRelatorio)
// {
//     cout << "-----dadosRelatorio-----" << endl;
//     showRelatorio(dadosRelatorio.relatorio);
//     cout << "data: " + dadosRelatorio.data << endl;
//     cout << "ph: " + to_string(dadosRelatorio.ph) << endl;
//     cout << "umidade: " + to_string(dadosRelatorio.umidade) << endl;
//     cout << "saude: " + dadosRelatorio.saude << endl;
//     cout << "obs: " + dadosRelatorio.obs << endl;
// }

// int main()
// {
//     GerenciadorCanteiros gerenciadorCanteiros = GerenciadorCanteiros();
//     GerenciadorRelatorios gerenciadorRelatorios = GerenciadorRelatorios();
//     // gerenciadorCanteiros.adicionarCanteiro("Canteiro 1", "bromelia", 6, 4, 132, "bromelias cheirosas e belas");
//     // gerenciadorCanteiros.adicionarCanteiro("Canteiro 2", "lavanda", 12, 6, 23, "lavandas lilas e longas");
//     // gerenciadorCanteiros.adicionarCanteiro("Canteiro 3", "bromelia", 6, 4, 132, "bromelias cheirosas e belas"); 
//     // gerenciadorCanteiros.adicionarCanteiro("Canteiro 4", "rosas", 12, 32, 43, "rosas lindas para o meu amor");
//     // gerenciadorRelatorios.adicionarRelatorio(gerenciadorCanteiros.getId("Canteiro 3"), "Relatorio 1", 5, 120, "boa", "nanhuma");
//     // gerenciadorRelatorios.adicionarRelatorio(gerenciadorCanteiros.getId("Canteiro 3"), "Relatorio 2", 1, 88, "ruim", "nanhuma");
//     gerenciadorRelatorios.adicionarRelatorio(gerenciadorCanteiros.getId("Canteiro 2"), "Relatorio 3", 2, 38, "ruim", "nanhuma");
//     // gerenciadorRelatorios.removerRelatorio(gerenciadorRelatorios.getId("Relatorio 3"));
//     // gerenciadorCanteiros.removerCanteiro(gerenciadorCanteiros.getId("Canteiro 3"));
//     showDictCanteiros(gerenciadorCanteiros.buscarPorNome("2")); 
//     cout << "" << endl;
//     showDictRelatorios(gerenciadorRelatorios.buscarPorNome("1"));
//     cout << "" << endl;
//     showDadosCanteiro(gerenciadorCanteiros.armazenarCanteiro(gerenciadorCanteiros.getId("Canteiro 3")));
//     cout << "" << endl;
//     showDadosRelatorio(gerenciadorRelatorios.armazenarRelatorio(gerenciadorRelatorios.getId("Relatorio 2")));
//     return 0;
// }