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
    //m_optionsCalculationFactorsBarGradeCosts->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &SteelCalcOptions::OnBarClassificationValueChange, this);
    
    // Populate the Bar Grade Costs widget
    if (m_optionsCalculationFactorsBarGradeCosts)
    {
        // ensure grid has 2 columns
        int colCount = m_optionsCalculationFactorsBarGradeCosts->GetNumberCols();
        if (colCount < 2)
        {
            m_optionsCalculationFactorsBarGradeCosts->AppendCols((2 - colCount));
        }
        m_optionsCalculationFactorsBarGradeCosts->SetColLabelValue(0, "Bar Name");
        m_optionsCalculationFactorsBarGradeCosts->SetColLabelValue(1, "Cost per Mg");

        // set text alignment of second col
        wxGridCellAttr* rightAlignAttr = new wxGridCellAttr();
        rightAlignAttr->SetAlignment(wxALIGN_RIGHT, wxALIGN_CENTER);
        m_optionsCalculationFactorsBarGradeCosts->SetColAttr(1, rightAlignAttr);

        // Populate rows with default values
        wxArrayString barClassifications = m_mainFrame->GetBarClassifications();
        int row = 0;
        for (const wxString& barType : barClassifications)
        {
            // ensure there are enough rows on the grid
            if (m_optionsCalculationFactorsBarGradeCosts->GetNumberRows() <= row)
            {
                m_optionsCalculationFactorsBarGradeCosts->AppendRows(1);
            }

            m_optionsCalculationFactorsBarGradeCosts->SetCellValue(row, 0, barType);
            m_optionsCalculationFactorsBarGradeCosts->SetCellValue(row, 1, "0");
            row++;
        }

        // set grid's size and scroll behaviour
        m_optionsCalculationFactorsBarGradeCosts->SetMinSize(wxSize(-1, 200));
        m_optionsCalculationFactorsBarGradeCosts->EnableScrolling(false, true);
    }
    // update user-seen UI
    m_optionsCalculationFactorsBarGradeCosts->Layout();
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

    // unsigned int rowCount = m_optionsCalculationFactorsBarGradeCosts->GetItemCount();
    // for (unsigned int i = 0; i < rowCount; ++i)
    // {
    //     wxString barGrade	= m_optionsCalculationFactorsBarGradeCosts->GetTextValue(i, 0);
    //     wxString costPerMg	= m_optionsCalculationFactorsBarGradeCosts->GetTextValue(i, 1);
	// 	barData.push_back(std::make_pair(barGrade, costPerMg));
    // }
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

// void SteelCalcOptions::OnBarClassificationValueChange(wxDataViewEvent &event)
// {
//     // when the data in the Bar Cost class table changes, we need to check what the user inputs and sanitize it
//     // column 0 can be any string value (it's the Bar Name / label)
//     // column 1 has to be a float (it's the Bar Cost, so it's a currency value - ?rem to write this for multi-locale support)
    
//     // get row & col of changed value event.
//     int row = m_optionsCalculationFactorsBarGradeCosts->ItemToRow(event.GetItem());
//     int col = event.GetColumn();

//     // get changed value
//     wxString newValue = m_optionsCalculationFactorsBarGradeCosts->GetTextValue(row, col);
    
//     // bar label/name
//     if (col == 0)
//     {
//         // allow string value, trim whitespace
//         newValue = newValue.Trim().Trim(false);
//         if (newValue.IsEmpty()) 
//         {
//             wxMessageBox("Bar name cannot be empty.", "Invalid input", wxOK | wxICON_ERROR);
//             m_optionsCalculationFactorsBarGradeCosts->SetTextValue("", row, col);
//         }
//         else
//         {
//             m_optionsCalculationFactorsBarGradeCosts->SetValue(newValue, row, col);
//         }
//     }
//     else if (col == 1)
//     {
//         // allow only a valid float or int value
//         double cost;
//         if (!newValue.ToDouble(&cost) || cost < 0)
//         {
//             wxMessageBox("Bar cost must be a valid non-negative number.", "Invalid Input", wxOK | wxICON_ERROR);
//             m_optionsCalculationFactorsBarGradeCosts->SetTextValue("0", row, col);
//         }
//         else
//         {
//             m_optionsCalculationFactorsBarGradeCosts->SetValue(wxString::Format("%.2f", cost), row, col);
//         }
//     }
//     event.Skip();
// }

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

