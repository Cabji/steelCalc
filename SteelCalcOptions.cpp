#include "SteelCalcMain.h"
#include "SteelCalcOptions.h"
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
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
        m_optionsCalculationFactorsBarGradeCosts->SetTableName("inventory");
		m_optionsCalculationFactorsBarGradeCosts->SetTablePrimaryKey("itemName");

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

// when the Options widget is closed (hidden from view) the following will happen: 
//  current state of grid data is collected
//  detect deleted rows
//		build & send DELETE query to database
//	detect added rows
//		build & send INSERT query to database
//	detect altered rows
//		build & send UPDATE query to database
void SteelCalcOptions::OnClose(wxCloseEvent &event)
{
	// dev-note: if you are copying & pasting this code to re-use somewhere else, you will need to update it to know 
	// which grid to use as we are working on the class member grid in here

	ResultSetGrid* grid = m_optionsCalculationFactorsBarGradeCosts;
    int rowCount = grid->GetNumberRows();
    int colCount = grid->GetNumberCols();

    // collect current state of grid data
    std::vector<wxString> currentRowKeys;
    std::vector<std::vector<wxString>> currentRows;

    // loop the grid and push data into currentRowKeys & currentRows
    for (int i = 0; i < rowCount; ++i) 
    {
        currentRowKeys.push_back(grid->GetCellValue(i, SC_OPTIONS_PK_COLUMN_INDEX));
        std::vector<wxString> rowData;
        for (int j = 0; j < colCount; ++j) 
        {
            rowData.push_back(grid->GetCellValue(i, j));
        }
        currentRows.push_back(rowData);
    }

    // 1. detect deleted rows (in original but not in current)
    std::vector<wxString> deletedKeys;
    for (size_t i = 0; i < m_originalRowKeys.size(); ++i) 
    {
        const wxString& origKey = m_originalRowKeys[i];
        // if we DON'T find the index value from the original data in the current data vector, then DELETE the row from the database
        if (std::find(currentRowKeys.begin(), currentRowKeys.end(), origKey) == currentRowKeys.end()) 
        {
            // build a DELETE query that will remove all missing data in a single database query execution
            // Row deleted: issue DELETE
            deletedKeys.push_back(origKey);
        }
    }
    // use SQL API here to issue the DELETE query
	if (!deletedKeys.empty()) 
	{
		try {
			SQLite::Database db(DEFAULT_DATABASE_FILENAME, SQLite::OPEN_READWRITE);
			SQLite::Statement delStmt(db, "DELETE FROM inventory WHERE itemName=?");
			for (const auto& key : deletedKeys) {
				delStmt.bind(1, key.ToStdString());
				delStmt.exec();
				delStmt.reset();
			}
		} catch (const std::exception& e) {
			std::cerr << "Error deleting rows: " << e.what() << std::endl;
		}	
	}

    // 2. detect new rows (in current but not in original)
	std::vector<int> newRowIndices;
    for (size_t i = 0; i < currentRowKeys.size(); ++i) 
    {
        const wxString& currKey = currentRowKeys[i];
        // if we DO FIND the index value from data in the current vector and it is not found in the original vector data, INSERT the row data to the database
        if (std::find(m_originalRowKeys.begin(), m_originalRowKeys.end(), currKey) == m_originalRowKeys.end()) 
        {
            // build an INSERT query that will add all new data in a single database query execution
            // Row inserted: issue INSERT
			newRowIndices.push_back(static_cast<int>(i));
        }
    }
    // use SQL API here to issue the INSERT query
	if (!newRowIndices.empty()) 
	{
		try {
			SQLite::Database db(DEFAULT_DATABASE_FILENAME, SQLite::OPEN_READWRITE);
			// get columnLabelMap from [this] to know what the column names are in the database
			ResultSet* l_resultSet = grid->GetResultSet();
			
            // todo: need to also add and include a category value for INSERTed new rows so the Options frame can display these new entries
			// Build the INSERT statement dynamically based on column count
			std::string insertSQL = "INSERT INTO " + grid->GetTableName() + " (";
			for (int c = 0; c < colCount; ++c) 
			{
				std::string fieldName = l_resultSet->sm_columnLabelMap[grid->GetColLabelValue(c).ToStdString()];
				insertSQL += fieldName;
				if (c < colCount - 1) insertSQL += ", ";
			}
			insertSQL += ") VALUES (";
			for (int c = 0; c < colCount; ++c) {
				insertSQL += "?";
				if (c < colCount - 1) insertSQL += ", ";
			}
			insertSQL += ")";
			SQLite::Statement insStmt(db, insertSQL);
			
			for (int rowIdx : newRowIndices) {
				for (int c = 0; c < colCount; ++c) {
					insStmt.bind(c + 1, currentRows[rowIdx][c].ToStdString());
				}
				// debug
				std::cout << "Query is: " << insStmt.getExpandedSQL() << std::endl;
				insStmt.exec();
				insStmt.reset();
			}
		} catch (const std::exception& e) {
			std::cerr << "Error inserting rows: " << e.what() << std::endl;
		}
	}

    // 3. detect modified rows (Primary Keys exists in both vectors, but row data has changed)
    // modifiedRowIndices holds the indices of the rows that have been altered since the OnShow() call
    std::vector<int> modifiedRowIndices;
    for (size_t i = 0; i < currentRowKeys.size(); ++i) 
    {
        const wxString& currKey = currentRowKeys[i];
        // it = pointer to the row in the current data vector with the altered row data
        auto it = std::find(m_originalRowKeys.begin(), m_originalRowKeys.end(), currKey);
        if (it != m_originalRowKeys.end()) 
        {
            size_t origIdx = std::distance(m_originalRowKeys.begin(), it);
            if (currentRows[i] != m_originalRows[origIdx]) 
            {
                // Row changed
                modifiedRowIndices.push_back(static_cast<int>(i));
            }
        }
    }

    // 4. save only modified rows using your SaveFromGridToDatabase
    std::vector<int> colIndicesEmpty;

    if (!modifiedRowIndices.empty()) {
        grid->SaveFromGridToDatabase(
            DEFAULT_DATABASE_FILENAME, "inventory", "itemName", modifiedRowIndices, colIndicesEmpty);
    }

    this->Hide();
    if (m_mainFrame) {
        m_mainFrame->TriggerUpdateResults();
        m_mainFrame->TriggerSaveConfig();
    }
    std::cout << "Options frame hidden!" << std::endl;
}

void SteelCalcOptions::OnShow(wxShowEvent &event)
{
    // populate the Bar Costs grid when the Options frame is shown
    // dev-note: the values for the Bar Costs are being pulled from the inventory table in the database!
    std::unordered_map<std::string, std::string> l_whereConditions = {{ "category", "Steel - per Mg" }};

    m_optionsCalculationFactorsBarGradeCosts->SetTableName("inventory");
    m_optionsCalculationFactorsBarGradeCosts->SetTablePrimaryKey("itemName");
    m_optionsCalculationFactorsBarGradeCosts->SetPopulateQuery("SELECT itemName AS 'Bar Grade', itemCost AS 'Cost per Mg', supplierName AS 'Supplier' "
                                                               "FROM #TABLENAME# "
															   "#WHERECLAUSE#");
    m_optionsCalculationFactorsBarGradeCosts->BuildQueryPopulate();
    m_newResultSet = m_optionsCalculationFactorsBarGradeCosts->RequestDatabaseData(DEFAULT_DATABASE_FILENAME);

    std::cout << "      Result size: " << m_newResultSet.rows.size() << std::endl;
    m_optionsCalculationFactorsBarGradeCosts->GridAdjustStructure(m_newResultSet);
    ResultSetGrid::GridUpdateContent(*m_optionsCalculationFactorsBarGradeCosts, m_newResultSet, false, true);
    
    // store the data as loaded by OnShow() for comparison later on in OnClose()
    m_originalRowKeys.clear();
    m_originalRows.clear();
    int rowCount = m_optionsCalculationFactorsBarGradeCosts->GetNumberRows();
    int colCount = m_optionsCalculationFactorsBarGradeCosts->GetNumberCols();
    for (int i = 0; i < rowCount; ++i) 
    {
        // add to m_originalRowKeys (Primary Key values only)
        m_originalRowKeys.push_back(m_optionsCalculationFactorsBarGradeCosts->GetCellValue(i, SC_OPTIONS_PK_COLUMN_INDEX));
        std::vector<wxString> rowData;
        for (int j = 0; j < colCount; ++j) 
        {
            // add to m_originalRows (all grid data)
            rowData.push_back(m_optionsCalculationFactorsBarGradeCosts->GetCellValue(i, j));
        }
        m_originalRows.push_back(rowData);
    }

    event.Skip();
}
