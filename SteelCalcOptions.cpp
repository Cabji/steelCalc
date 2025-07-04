#include "SteelCalcMain.h"
#include "SteelCalcOptions.h"
#include <algorithm>
#include <vector>
#include <string>
#include <wx/msgdlg.h>

SteelCalcOptions::SteelCalcOptions( wxWindow* parent)
:
Options( parent )
{
    // dev-note: m_optionsCalculationFactorBarGradeCosts is a ResultSetGrid object from the base class. 
    //   it is defined as a ResultSetGrid in the wxFormBuilder project.
    // Populate the Bar Grade Costs widget
    if (m_optionsCalculationFactorsBarGradeCosts)
    {
        // local data acquisition
        // dev-note: CustomGridCell editors are assigned to a wxGrid to give us input validation/sanitation
        CustomGridCellEditor* 	floatEditor 		= new CustomGridCellEditor();
        CustomGridCellEditor* 	stringEditor 		= new CustomGridCellEditor();
        wxGridCellAttr* 		rightAlignAttr 		= new wxGridCellAttr();
        int						colCount			= m_optionsCalculationFactorsBarGradeCosts->GetNumberCols();
        floatEditor->SetValidationType(CustomGridCellEditor::ValidationType::FLOAT);
        stringEditor->SetValidationType(CustomGridCellEditor::ValidationType::STRING);
        rightAlignAttr->SetAlignment(wxALIGN_RIGHT, wxALIGN_CENTER);
        


        // // ensure grid has 2 columns
        if (colCount < 2) { m_optionsCalculationFactorsBarGradeCosts->AppendCols((2 - colCount)); }
        
		// // set grid/column attributes
        // m_optionsCalculationFactorsBarGradeCosts->DeleteRows(0, m_optionsCalculationFactorsBarGradeCosts->GetNumberRows());
		m_optionsCalculationFactorsBarGradeCosts->SetDefaultEditor(stringEditor);
        m_optionsCalculationFactorsBarGradeCosts->SetColAttr(1, rightAlignAttr);
        m_optionsCalculationFactorsBarGradeCosts->SetColFormatFloat(1, 0, 2);
        m_optionsCalculationFactorsBarGradeCosts->SetSortingColumn(0);

        // set grid's size and scroll behaviour
        wxSize uiSize = m_optionsCalculationFactorsBarGradeCosts->GetSize();
        m_optionsCalculationFactorsBarGradeCosts->SetMinSize(uiSize);
        m_optionsCalculationFactorsBarGradeCosts->EnableScrolling(false, true);
        // update user-seen UI
        m_optionsCalculationFactorsBarGradeCosts->Layout();
    }

    m_mainFrame = dynamic_cast<SteelCalcMain*>(parent);

    // Bind event handlers
    this->Bind(wxEVT_CLOSE_WINDOW, &SteelCalcOptions::OnClose, this); 
    this->Bind(wxEVT_SHOW, &SteelCalcOptions::OnShow, this);
    m_optionsCalculationFactorsBarGradeCosts->Bind(wxEVT_GRID_COL_SORT, &ResultSetGrid::GridSort);
    m_optionsCalculationFactorsBarGradeCosts->Bind(wxEVT_KEY_DOWN, &SteelCalcOptions::OnGridKeyDown, this);
    
    
    // update user-seen UI
    m_optionsCalculationFactorsBarGradeCosts->SetFocus();
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

// this function handles if the user presses Enter or Down Arrow key while at the bottom row of a wxGrid
// it will add a new row to the grid
//      this code should be improved to check if the grid is allowing editing or not. if read-only, it should NOT add a new row.
void SteelCalcOptions::OnGridKeyDown(wxKeyEvent &event)
{
	std::cout << "OnGridKeyDown event handler is happening." << std::endl;
    // wxGrid* grid = dynamic_cast<wxGrid*>(event.GetEventObject());
     wxGrid* grid = m_optionsCalculationFactorsBarGradeCosts;
    if (!grid)
    {
        std::cout << "!! Grid object was " << grid << std::endl;
        // allow regular processing and return
        event.Skip();
        return;
    }

    // std::cout << "GetKeyCode: " << event.GetKeyCode() << std::endl;
    if (event.GetKeyCode() == WXK_DOWN || event.GetKeyCode() == WXK_NUMPAD_DOWN)
    {
        // local data acquisition
        int currentRow  = grid->GetGridCursorRow();
        int currentCol  = grid->GetGridCursorCol();
        int lastRow     = grid->GetNumberRows() - 1;

        // check if enter was pressed in last row
        if (currentRow == lastRow)
	{
		// check if all cells in lastRow are empty before adding a new row
		bool isRowEmpty = true;
		for(int col = 0; col < grid->GetNumberCols(); ++col)
		{
			if (!grid->GetCellValue(currentRow, col).IsEmpty())
			{
				isRowEmpty = false;
				break;
			}
		}
		// return if the last row was empty as we don't want to create a new row.
		if (isRowEmpty) { event.Skip(); return; }

        std::cout << "  Adding new row to grid." << std::endl;
		// add new row
		grid->AppendRows(1);

		// shift focus to left-most cell of new row
		grid->SetGridCursor(lastRow + 1, 0);
		grid->MakeCellVisible(lastRow + 1,0);
	}
    }
    else if (event.GetKeyCode() == WXK_DELETE)
    {
        std::cout << "  Delete key pressed." << std::endl
                  << "    Selected row blocks size: " << grid->GetSelectedRowBlocks().size() << std::endl
                  << "    Number of cols: " << grid->GetNumberCols() << std::endl;

        // dev-note: wxGrid::GetSelectedRows() returns a vector of int values which are *only* rows that have *all* cells selected.
        auto selectedRows = grid->GetSelectedRows();

        std::cout << "    Deleting rows: " << std::endl;
        // delete all the *entirely selected* rows
        for (int rowToDelete : selectedRows)
        {
            std::cout << "      " << rowToDelete << std::endl;
            grid->DeleteRows(rowToDelete);    
        }
        // shift focus to left most cell of the row above the deleted row
        if (selectedRows.size() > 0)
        {
            int rowAbove = selectedRows[0] - 1;
            if (rowAbove >= 0)
            {
                grid->SetGridCursor(rowAbove, 0);
                grid->MakeCellVisible(rowAbove, 0);
            }
        }
        else
        {
            // no rows selected, so just move the cursor to the first cell of the grid
            grid->SetGridCursor(0, 0);
            grid->MakeCellVisible(0, 0);
        }
    }
	event.Skip();
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

void SteelCalcOptions::SetBarClassificationData(const wxVector<std::pair<wxString, wxString>> &barData)
{
    // this method will be called AFTER the constructor has been called
    // so we have to handle the barData and populate the m_optionsCalculationFactorBarGradeCosts grid with it

    // dev-note: we need to clear the grid and ensure it has enough rows to hold items from barData
    int rowCount = m_optionsCalculationFactorsBarGradeCosts->GetNumberRows();
    int barDataCount = barData.size();
    if (rowCount < barDataCount)
    {
       m_optionsCalculationFactorsBarGradeCosts->AppendRows(barDataCount - rowCount);
    }
    else if (rowCount > barDataCount)
    {
        m_optionsCalculationFactorsBarGradeCosts->DeleteRows(barDataCount, rowCount - barDataCount);
    }

    // local data acquisition
    m_barGradeAndCostData = barData;
    for (int i = 0; i < barData.size(); ++i)
    {
        m_optionsCalculationFactorsBarGradeCosts->SetCellValue(i, 0, m_barGradeAndCostData[i].first);
        m_optionsCalculationFactorsBarGradeCosts->SetCellValue(i, 1, m_barGradeAndCostData[i].second);
    }
    std::cout << "Updated bar classification data in the Options frame." << std::endl;
}

void SteelCalcOptions::OnClose(wxCloseEvent &event)
{
    // std::vector<std::vector<std::pair<std::string, std::string>>> dbResults;
    // dbResults = m_mainFrame->m_dbViewerFrame->RequestDatabaseData("SELECT * FROM inventory");
    // std::cout << "Number of results from Requested Database Data: " << dbResults.size() << std::endl;
    // dev-note: perhaps save the options to disk here at some stage?
    
    // get data from Bar Grade Costs grid and try to send to inventory to update
    std::vector<int> cols, rows;
    ResultSet gridValues = m_optionsCalculationFactorsBarGradeCosts->RequestGridData(rows, cols);
    // temp show the values we got in the ResultSet
    gridValues.OutputResultSetInfo();
    // call function that creates the SQL UPDATE query(ies) 
    std::vector<int> empty;
    m_optionsCalculationFactorsBarGradeCosts->SaveFromGridToDatabase(DEFAULT_DATABASE_FILENAME, "inventory", "itemName", empty, empty);

    this->Hide();
    // save program options to relevnt config file(s)
    if (m_mainFrame)
    {
        m_mainFrame->TriggerUpdateResults();
        m_mainFrame->TriggerSaveConfig();
    }
    std::cout << "Options frame hidden!" << std::endl;
}

void SteelCalcOptions::OnShow(wxShowEvent &event)
{
    // ensure the Bar Grade Costs grid is updated/populated
    // dev-note: the values for the Bar Costs are being pulled from the inventory table in the database!
    std::cout << "  Options: SQL Query is " << m_queryBarRates << std::endl;
    m_newResultSet = ResultSetGrid::RequestDatabaseData(DEFAULT_DATABASE_FILENAME, m_queryBarRates);
    std::cout << "      Result size: " << m_newResultSet.rows.size() << std::endl;
    m_optionsCalculationFactorsBarGradeCosts->GridAdjustStructure(m_newResultSet);
    ResultSetGrid::GridUpdateContent(*m_optionsCalculationFactorsBarGradeCosts, m_newResultSet, false, true);
    event.Skip();
}
