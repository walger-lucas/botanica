#pragma once
#include <wx/wx.h>
#include "GerenciadorCanteiros.h"

class Aplicacao : public wxApp
{
    public:
        static GerenciadorCanteiros gerCant;
        bool OnInit();
};