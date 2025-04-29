#include "SteelCalcMain.h"
#include "SteelCalcOptions.h"
#include <wx/msgdlg.h>

SteelCalcOptions::SteelCalcOptions( wxWindow* parent)
:
Options( parent )
{
    m_mainFrame = dynamic_cast<SteelCalcMain*>(parent);
    
    // Bind event handlers
    this->Bind(wxEVT_CLOSE_WINDOW, &SteelCalcOptions::OnClose, this); 
    m_optionsCalculationFactorsBarGradeCosts->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &SteelCalcOptions::OnBarClassificationValueChange, this);
    
    // Populate the Bar Grade Costs widget
    if (m_optionsCalculationFactorsBarGradeCosts)
    {
        // Add columns with header titles
        m_optionsCalculationFactorsBarGradeCosts->AppendTextColumn("Bar Grade", wxDATAVIEW_CELL_EDITABLE, 75, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
        m_optionsCalculationFactorsBarGradeCosts->AppendTextColumn("Cost per Mg", wxDATAVIEW_CELL_EDITABLE, 75, wxALIGN_RIGHT);

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
    // update user-seen UI
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

wxVector<std::pair<wxString, wxString>> SteelCalcOptions::GetBarClassificationData()
{
    wxVector<std::pair<wxString, wxString>> barData;

    unsigned int rowCount = m_optionsCalculationFactorsBarGradeCosts->GetItemCount();
    for (unsigned int i = 0; i < rowCount; ++i)
    {
        wxString barGrade	= m_optionsCalculationFactorsBarGradeCosts->GetTextValue(i, 0);
        wxString costPerMg	= m_optionsCalculationFactorsBarGradeCosts->GetTextValue(i, 1);
		barData.push_back(std::make_pair(barGrade, costPerMg));
    }
    return barData;
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

void SteelCalcOptions::OnBarClassificationValueChange(wxDataViewEvent &event)
{
    // when the data in the Bar Cost class table changes, we need to check what the user inputs and sanitize it
    // column 0 can be any string value (it's the Bar Name / label)
    // column 1 has to be a float (it's the Bar Cost, so it's a currency value - ?rem to write this for multi-locale support)
    
    // get row & col of changed value event.
    int row = m_optionsCalculationFactorsBarGradeCosts->ItemToRow(event.GetItem());
    int col = event.GetColumn();

    // get changed value
    wxString newValue = m_optionsCalculationFactorsBarGradeCosts->GetTextValue(row, col);
    
    // bar label/name
    if (col == 0)
    {
        // allow string value, trim whitespace
        newValue = newValue.Trim().Trim(false);
        if (newValue.IsEmpty()) 
        {
            wxMessageBox("Bar name cannot be empty.", "Invalid input", wxOK | wxICON_ERROR);
            m_optionsCalculationFactorsBarGradeCosts->SetTextValue("", row, col);
        }
        else
        {
            m_optionsCalculationFactorsBarGradeCosts->SetValue(newValue, row, col);
        }
    }
    else if (col == 1)
    {
        // allow only a valid float or int value
        double cost;
        if (!newValue.ToDouble(&cost) || cost < 0)
        {
            wxMessageBox("Bar cost must be a valid non-negative number.", "Invalid Input", wxOK | wxICON_ERROR);
            m_optionsCalculationFactorsBarGradeCosts->SetTextValue("0", row, col);
        }
        else
        {
            m_optionsCalculationFactorsBarGradeCosts->SetValue(wxString::Format("%.2f", cost), row, col);
        }
    }
    event.Skip();
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

