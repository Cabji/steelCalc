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
        // local data acquisition
        CustomGridCellEditor* 	floatEditor 		= new CustomGridCellEditor();
        CustomGridCellEditor* 	stringEditor 		= new CustomGridCellEditor();
        wxGridCellAttr* 		rightAlignAttr 		= new wxGridCellAttr();
        wxArrayString 			barClassifications 	= m_mainFrame->GetBarClassifications();
        int						colCount			= m_optionsCalculationFactorsBarGradeCosts->GetNumberCols();
        floatEditor->SetValidationType(CustomGridCellEditor::ValidationType::FLOAT);
        stringEditor->SetValidationType(CustomGridCellEditor::ValidationType::STRING);
        rightAlignAttr->SetAlignment(wxALIGN_RIGHT, wxALIGN_CENTER);
        
        // ensure grid has 2 columns
        if (colCount < 2) { m_optionsCalculationFactorsBarGradeCosts->AppendCols((2 - colCount)); }
        
		// set grid/column attributes
		m_optionsCalculationFactorsBarGradeCosts->SetDefaultEditor(stringEditor);
		m_optionsCalculationFactorsBarGradeCosts->SetColLabelValue(0, "Bar Name");
        m_optionsCalculationFactorsBarGradeCosts->SetColLabelValue(1, "Cost per Mg");
        m_optionsCalculationFactorsBarGradeCosts->SetColAttr(1, rightAlignAttr);
        m_optionsCalculationFactorsBarGradeCosts->SetColFormatFloat(1, 0, 2);

        // Populate rows with bar classifications and costs
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
        wxSize uiSize = m_optionsCalculationFactorsBarGradeCosts->GetSize();
        m_optionsCalculationFactorsBarGradeCosts->SetMinSize(uiSize);
        m_optionsCalculationFactorsBarGradeCosts->EnableScrolling(false, true);
        // update user-seen UI
        m_optionsCalculationFactorsBarGradeCosts->Layout();
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

    int rowCount = m_optionsCalculationFactorsBarGradeCosts->GetNumberRows();
    for (int i = 0; i < rowCount; ++i)
    {
        wxString barGrade	= m_optionsCalculationFactorsBarGradeCosts->GetCellValue(i, 0);
        wxString costPerMg	= m_optionsCalculationFactorsBarGradeCosts->GetCellValue(i, 1);
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

