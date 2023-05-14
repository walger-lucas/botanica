cmake_minimum_required(VERSION 3.0.0)
project(botanica VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
find_library(MYSQLCPPCONN_LIBRARY mysqlcppconn)

set(CPACK_PROJECT_NAME ${PROJECT_NAME}) 
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# add_executable(banco GerenciadorCanteiros.cpp GerenciadorRelatorios.cpp GerenciadorBD.cpp Canteiro.cpp Relatorio.cpp)
add_executable(botanica Aplicacao.cpp JanelaPrincipal.cpp Janela.cpp GerenciadorJanelas.cpp JVerCanteiro.cpp JAddCanteiro.cpp JVerRelatorio.cpp JAddRelatorio.cpp JCronograma.cpp ListaCanteiros.cpp PainelCanteiro.cpp Canteiro.cpp GerenciadorCanteiros.cpp GerenciadorRelatorios.cpp Relatorio.cpp GerenciadorBD.cpp)

target_link_libraries(botanica ${wxWidgets_LIBRARIES})
target_link_libraries(botanica ${MYSQLCPPCONN_LIBRARY})
target_include_directories(botanica PUBLIC ${MYSQLCPP_INCLUDE_DIRS})
# target_link_libraries(banco ${MYSQLCPPCONN_LIBRARY})
# target_include_directories(banco PUBLIC ${MYSQLCPP_INCLUDE_DIRS})
include(CPack)
