#include "SteelCalcMain.h"

SteelCalcMain::SteelCalcMain( wxWindow* parent )
:
Main( parent )
{
    this->Fit();
}

SteelCalcMain::SteelCalcMain(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : Main(parent, id, title, pos, size, style)
{
    // Set the title of the frame
    SetTitle(title);
    m_chbCircularInput->Hide();
    
    this->SetSizer(m_mainSizer);
    this->Fit();
}
