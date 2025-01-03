#include "SteelCalcOptions.h"

SteelCalcOptions::SteelCalcOptions( wxWindow* parent )
:
Options( parent )
{
    Bind(wxEVT_CLOSE_WINDOW, &SteelCalcOptions::OnClose, this);
}

bool SteelCalcOptions::GetAddLapTies()
{
    return m_optionsLabourAddLapTies->GetValue();
}

bool SteelCalcOptions::GetAddPerimeterTies()
{
    return m_optionsLabourAddPerimeterTies->GetValue();
}

bool SteelCalcOptions::GetAddSetupTies()
{
    return m_optionsLabourAddSetupTies->GetValue();
}

void SteelCalcOptions::OnClose(wxCloseEvent &event)
{
    // dev-note: perhaps save the options to disk here at some stage?
    this->Show(false);
    std::cout << "Options frame hidden!" << std::endl;
}
