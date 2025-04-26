#include "SteelCalcMain.h"
#include "SteelCalcOptions.h"

SteelCalcOptions::SteelCalcOptions( wxWindow* parent)
:
Options( parent )
{
    m_mainFrame = dynamic_cast<SteelCalcMain*>(parent);
    
    // Bind the close event handler
    Bind(wxEVT_CLOSE_WINDOW, &SteelCalcOptions::OnClose, this); 
    
    // Populate the Bar Grade Costs widget
    if (m_optionsCalculationFactorsBarGradeCosts)
    {
        // Add columns with header titles
        m_optionsCalculationFactorsBarGradeCosts->AppendTextColumn("Bar Grade", wxDATAVIEW_CELL_INERT, 150, wxALIGN_LEFT);
        m_optionsCalculationFactorsBarGradeCosts->AppendTextColumn("Cost per Mg", wxDATAVIEW_CELL_EDITABLE, 150, wxALIGN_RIGHT);

        // Populate rows with default values
        wxArrayString barClassifications = m_mainFrame->GetBarClassifications();
        for (const wxString& barType : barClassifications)
        {
            wxVector<wxVariant> row;
            row.push_back(wxVariant(barType)); // Bar Grade
            row.push_back(wxVariant("0"));    // Default Cost
            m_optionsCalculationFactorsBarGradeCosts->AppendItem(row);
        }
    }
    this->Layout();
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

void SteelCalcOptions::SetAddLapTies(const bool &value)
{
    m_optionsLabourAddLapTies->SetValue(value);
}

void SteelCalcOptions::SetAddPerimeterTies(const bool &value)
{
    m_optionsLabourAddPerimeterTies->SetValue(value);
}

void SteelCalcOptions::SetAddSetupTies(const bool &value)
{
    m_optionsLabourAddSetupTies->SetValue(value);
}

void SteelCalcOptions::OnClose(wxCloseEvent &event)
{
    // dev-note: perhaps save the options to disk here at some stage?
    this->Hide();
    if (m_mainFrame)
    {
        m_mainFrame->TriggerUpdateResults();
        m_mainFrame->TriggerSaveConfig();
    }
    std::cout << "Options frame hidden!" << std::endl;
}
