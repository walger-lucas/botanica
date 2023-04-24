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
add_executable(botanica Aplicacao.cpp JanelaPrincipal.cpp Janela.cpp GerenciadorJanelas.cpp JVerCanteiro.cpp JAddCanteiro.cpp JVerRelatorio.cpp JAddRelatorio.cpp JCronograma.cpp ListaCanteiros.cpp PainelCanteiro.cpp)

target_link_libraries(botanica ${wxWidgets_LIBRARIES})
include(CPack)
