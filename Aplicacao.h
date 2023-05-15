#pragma once
#include <wx/wx.h>
#include "GerenciadorCanteiros.h"
#include "GerenciadorRelatorios.h"

class Aplicacao : public wxApp
{
    public:
        static GerenciadorCanteiros gerCant;
        static GerenciadorRelatorios gerRel;
        bool OnInit();
};