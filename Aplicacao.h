#pragma once
#include <wx/wx.h>
#include "GerenciadorCanteiros.h"
#include "GerenciadorRelatorios.h"

class Aplicacao : public wxApp
{
    static GerenciadorCanteiros* gerCant;
    static GerenciadorRelatorios* gerRel;
    public:
        bool OnInit();
        static GerenciadorCanteiros& GetGerCanteiros() {return *gerCant;};
        static GerenciadorRelatorios& GetGerRelatorios() {return *gerRel;};
};