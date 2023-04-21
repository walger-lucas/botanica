#include "Janela.h"


Janela::Janela(GerenciadorJanelas* gJ, wxWindow *parent, wxWindowID id,
         const wxPoint &pos, const wxSize &size, long style,  const wxString &name)
        : wxWindow(parent,id,pos,size,style,name), gJ(gJ)
        {}
Janela::Janela( wxWindow *parent, wxWindowID id,
         const wxPoint &pos, const wxSize &size, long style,  const wxString &name)
        : wxWindow(parent,id,pos,size,style,name), gJ(nullptr)
        {}