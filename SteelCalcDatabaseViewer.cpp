#include "SteelCalcDatabaseViewer.h"
#include <set>
#include <string>
#include <wx/msgdlg.h>

SteelCalcDatabaseViewer::SteelCalcDatabaseViewer( wxWindow* parent )
:
SteelCalcDatabaseViewer(parent, DEFAULT_DATABASE_FILENAME, "")
{
    // delegated to overloaded ctr
}

SteelCalcDatabaseViewer::SteelCalcDatabaseViewer( wxWindow* parent, const std::string& dbFilename, const std::string& tableName )
:
DatabaseViewer(parent)
{
	// dev-note: the SteelCalcDatabaseViewer default ctr delegates to here

	// connect to/create SQLite3 database file - use default filename if none given
    if (dbFilename.empty()) 
	{
		m_dbFilename	= DEFAULT_DATABASE_FILENAME;
		std::cerr << "	!! - No database filename was passed to SteelCalcDatabaseViewer constructor so using default value instead." << std::endl;
    }
	else
	{
		m_dbFilename	= dbFilename;
	}
	// attempt to make database connection instance
    m_dbConnection	= std::make_unique<SQLite::Database>(m_dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

	// return with failure message if connection failed
    if (!m_dbConnection)
	{
		std::cerr << "	Connection to database file '" << m_dbFilename << "' failed." << std::endl;
		return;		
	}

	// todo: create required tables if needed
    CheckAndCreateTables(*m_dbConnection, expectedSchema);
	//m_dbQuery = std::make_unique<SQLite::Statement> (*m_dbConnection, "CREATE TABLE inventory");

	// data acquisition
	m_dbAvailableTableNames = DatabaseFetchTableNames(*m_dbConnection);

	// update UI

	// set the grid mode to editable (because wx is freaking painful, we can't set it to read-only and make whichever rows we want to be editable)
	m_uiTableGrid->EnableEditing(true);
	UpdateUI("databaseViewerTables");

	// bind event handlers
	m_uiChoicesDBTables->Bind   (wxEVT_CHOICE,              &SteelCalcDatabaseViewer::OnDatabaseActiveTableChoiceChanged, this);
    m_uiTableGrid->Bind         (wxEVT_GRID_CELL_CHANGED,   &SteelCalcDatabaseViewer::OnGridCellChanged, this);
    this->Bind                  (wxEVT_CLOSE_WINDOW,		&SteelCalcDatabaseViewer::OnClose, this);
}

std::set<std::string> SteelCalcDatabaseViewer::DatabaseFetchTableNames(const SQLite::Database& dbConnection)
{
	// get table names from a SQLite database connection
	std::set<std::string> l_setTableNames;
	m_dbQuery = std::make_unique<SQLite::Statement> (dbConnection, "SELECT name FROM sqlite_master WHERE type='table'");

	while (m_dbQuery->executeStep())
	{
		for (int i = 0; i < m_dbQuery->getColumnCount(); i++)
		{
			// get the returned table names and inset into l_setTableNames
			l_setTableNames.insert(m_dbQuery->getColumn(i));
		}
	}
	std::cout << "Number of table names we are returning: " << l_setTableNames.size() << std::endl;
	return l_setTableNames;
}

// update a wxGrid's structure/size to match a result set's size
void SteelCalcDatabaseViewer::GridAdjustStructure(wxGrid& grid, const std::vector<std::vector<std::pair<std::string, std::string>>>& resultSet)
{
    int resultSetColCount = 0;
    int resultSetRowCount = static_cast<int>(resultSet.size());
    std::vector<std::string> colNames;

    if (!resultSet.empty()) 
    {
        resultSetColCount = static_cast<int>(resultSet[0].size());
        for (int col = 0; col < resultSetColCount; ++col) 
        {
            colNames.push_back(resultSet[0][col].first);
        }
    } else if (!m_dbActiveTableName.empty()) 
    {
        // resultSet is empty, get column names from schema
        std::string pragmaSQL = "PRAGMA table_info(" + m_dbActiveTableName + ")";
        try {
            SQLite::Statement pragmaStmt(*m_dbConnection, pragmaSQL);
            while (pragmaStmt.executeStep()) {
                colNames.push_back(pragmaStmt.getColumn("name").getString());
            }
            resultSetColCount = static_cast<int>(colNames.size());
        } catch (...) {
            resultSetColCount = 0;
        }
    }

    // ensure the grid has the correct number of columns
    if (grid.GetNumberCols() != resultSetColCount) 
    {
        if (grid.GetNumberCols() < resultSetColCount)
            grid.AppendCols(resultSetColCount - grid.GetNumberCols());
        else
            grid.DeleteCols(0, grid.GetNumberCols() - resultSetColCount);
    }

    // set column labels
    for (int col = 0; col < resultSetColCount; ++col) 
    {
        grid.SetColLabelValue(col, wxString(colNames[col]));
        grid.AutoSizeColLabelSize(col);
    }

    // ensure the grid has the correct number of rows
    if (grid.GetNumberRows() != resultSetRowCount) 
    {
        if (grid.GetNumberRows() < resultSetRowCount)
            grid.AppendRows(resultSetRowCount - grid.GetNumberRows());
        else
            grid.DeleteRows(0, grid.GetNumberRows() - resultSetRowCount);
    }
}
void SteelCalcDatabaseViewer::GridInsertFilterRow(wxGrid &grid)
{
    // create the filter row at the top
    grid.InsertRows(0,1);
    grid.SetRowLabelValue(0, "Filter");
    // create filter row's background colour
    wxColour filterBg(220, 240, 255);

    // set the filter row's cells attributes here
    for (int col = 0; col < grid.GetNumberCols(); ++col) 
    {
        // dev-note: wx f0rces us to make the entire grid editable by default and then enf0rce read-only to cells that shouldn't be edited.
        // we can't do it the other way around, so we don't need to make the filter row editable.
        grid.SetCellBackgroundColour(0, col, filterBg);
        grid.SetCellBackgroundColour(1, col, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    }
}

// update a wxGrid with result set data - this method does NOT alter the grid's structure, only changes the cell data
void SteelCalcDatabaseViewer::GridUpdateContent(wxGrid& grid, const std::vector<std::vector<std::pair<std::string, std::string>>>& resultSet, const bool cellsReadOnly)
{
    grid.ClearGrid();
    if (resultSet.empty())
    {
        std::cout << "SteelCalcDV::GridUpdateContent(): There were no results returned for this table." << std::endl;
        return;    
    }
 
    int resultSetColCount = static_cast<int>(resultSet[0].size());
    int resultSetRowCount = static_cast<int>(resultSet.size());

    // fill grid with data, set the cells to read-only/editable depending on cellsReadOnly argument
    for (int row = 0; row < resultSetRowCount; ++row) 
    {
        for (int col = 0; col < resultSetColCount; ++col) 
        {
            grid.SetCellValue(row, col, wxString(resultSet[row][col].second));
            grid.SetReadOnly(row, col, cellsReadOnly);
        }
    }
}

void SteelCalcDatabaseViewer::OnClose(wxCloseEvent& event)
{
    this->Hide();
    // prevent automatic destruction of this by using Veto()
    event.Veto();
}

void SteelCalcDatabaseViewer::OnDatabaseActiveTableChoiceChanged(wxEvent &event)
{
	// handle when user chooses which database table to view

	// 1. get the selected table name from the wxChoice widget
    int selectionIndex = m_uiChoicesDBTables->GetSelection();
    if (selectionIndex == wxNOT_FOUND) {
        std::cerr << "No table selected." << std::endl;
        return;
    }

    m_dbActiveTableName = m_uiChoicesDBTables->GetString(selectionIndex).ToStdString();

    // 2. Query the selected table
    std::string query = "SELECT * FROM " + m_dbActiveTableName;
    m_dbResult = RequestDatabaseData(query);

    // 3. up grid's structure and content
    GridAdjustStructure(*m_uiTableGrid, m_dbResult);
    GridUpdateContent(*m_uiTableGrid, m_dbResult);
    GridInsertFilterRow(*m_uiTableGrid);
}

void SteelCalcDatabaseViewer::OnGridCellChanged(wxGridEvent& event)
{
    int row = event.GetRow();
    if (row == 0) 
    {
        // handle filter row
        wxObject*   tripperObj  = event.GetEventObject();
        wxGrid*     grid        = dynamic_cast<wxGrid*>(tripperObj);
        if (!grid)
        {
            std::cerr << "OnGridCellChanged: grid object was not available? returning.";
            return;
        }

		// save filter row values
		// holds the values currently found in the filter row
		std::vector<wxString> filterValues;
        for (int col = 0; col < grid->GetNumberCols(); ++col)
            filterValues.push_back(grid->GetCellValue(0, col));
		// dev-note: please note - filterValues holds the value of each cell in the filter row, even if there is no value in a cell


        std::string query       = "SELECT * FROM " + m_dbActiveTableName + " WHERE ";
            // build SQL query
        for (int col = 0; col < grid->GetNumberCols(); col++)
        {
            std::string cellValue   = grid->GetCellValue(0, col);
            if (cellValue != wxEmptyString)
            {
                // get the column Name
                std::string colName = grid->GetColLabelValue(col);
                // append the query string firstly with "AND" if this is not the first appendation
                if (!query.ends_with(" WHERE ")) { query += " AND "; }
                query +=  colName + " LIKE '%" + cellValue + "%'";
            }
        }
        std::cout << "Filtration query is: " << query << std::endl;
        // send query to database, get result set - use RequestDatabaseData
        m_dbResult = RequestDatabaseData(query);
        std::cout << "Result set size: " << m_dbResult.size() << std::endl;
        // update results into grid
        GridAdjustStructure(*m_uiTableGrid, m_dbResult);
        GridUpdateContent(*m_uiTableGrid, m_dbResult);
        GridInsertFilterRow(*m_uiTableGrid);

		// restore the filter row's filter values
		for (int col = 0; col < static_cast<int>(filterValues.size()); ++col)
            m_uiTableGrid->SetCellValue(0, col, filterValues[col]);
    } 
    else 
    {
		// for now, just skip the event if not row index 0
        event.Skip();
        // Handle data row edits (future)
    }
}
void SteelCalcDatabaseViewer::UpdateUI(const std::string &sectionName)
{
	// dev-note: you can refresh UI elements by specific section name
	// or all UI elements by using section name "all" (or empty sectionName)

	std::cout << "Updating UI: " << std::endl;
	if (sectionName == "databaseViewerTables" || sectionName == "dbvt" || sectionName == "all" || sectionName.empty())
	{
		std::cout << "	Database Viewer" << std::endl;
		// dev-note: std::set will automatically sort the table names alphanumeric for us
		if (m_dbAvailableTableNames.size() > 0) { m_statusBar->SetStatusText("View only"); }
		for (const std::string tableName : m_dbAvailableTableNames)
		{
			m_uiChoicesDBTables->Append(wxString(tableName));
		}
	}
	Layout();
	Refresh();
	std::cout << "Updating UI done." << std::endl;
}

// send a std::string query to the current database connection and retrieve the result set in a std::vector format
std::vector<std::vector<std::pair<std::string, std::string>>> SteelCalcDatabaseViewer::RequestDatabaseData(std::string query)
{
	std::vector<std::vector<std::pair<std::string, std::string>>>   l_result;

    try
    {
		m_dbQuery	= std::make_unique<SQLite::Statement>(*m_dbConnection, query);
        // convert the result into std vector<vector<pair<string, string>>> data type and return
        while (m_dbQuery->executeStep()) 
        {
            std::vector<std::pair<std::string, std::string>>    l_row;
            for (int col = 0; col < m_dbQuery->getColumnCount(); ++col)
            {
                std::string colName	= m_dbQuery->getColumnName(col);
                std::string value = m_dbQuery->getColumn(col).getText();
                l_row.emplace_back(colName, value);
            }
            l_result.push_back(std::move(l_row));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "SQL Query failed, error: " << e.what() << '\n';
    }

    return l_result;
}

void SteelCalcDatabaseViewer::CheckAndCreateTables(SQLite::Database& dbConnection, const DatabaseSchema& expectedSchema)
{
    bool success = true;
    std::set<std::string> availableTableNames;
    // query the database for existing table names
    SQLite::Statement tableQuery(dbConnection, "SELECT name FROM sqlite_master WHERE type='table'");
    while (tableQuery.executeStep()) {
        availableTableNames.insert(tableQuery.getColumn(0).getText());
    }

    // loop through the expectedSchema
    for (const auto& [tableName, tableSpec] : expectedSchema)
    {
        // check if tableName exists in the database already
        bool tableExists = availableTableNames.count(tableName) > 0;
        if (!tableExists)
        {
            // table does not exist, create it
            std::string createSQL = "CREATE TABLE " + tableName + " (";
            for (size_t i = 0; i < tableSpec.columns.size(); ++i)
            {
                createSQL += tableSpec.columns[i].name + " " + tableSpec.columns[i].type;
                if (i < tableSpec.columns.size() - 1)
                    createSQL += ", ";
            }
            createSQL += ")";
            try {
                SQLite::Statement createStmt(dbConnection, createSQL);
                createStmt.exec();
                wxMessageBox("Created missing table: " + wxString(tableName), "Database", wxOK | wxICON_INFORMATION, this);
            } catch (const std::exception& e) {
                wxMessageBox("Failed to create table " + wxString(tableName) + ": " + wxString(e.what()), "Database Error", wxOK | wxICON_ERROR, this);
                success = false;
            }
            continue;
        }

        // table exists, check the columns match the expectedSchema
        std::vector<ColumnSpec> actualColumns;
        // get table info from database
        std::string pragmaSQL = "PRAGMA table_info(" + tableName + ")";
        SQLite::Statement pragmaStmt(dbConnection, pragmaSQL);
        while (pragmaStmt.executeStep())
        {
            std::string colName = pragmaStmt.getColumn("name");
            std::string colType = pragmaStmt.getColumn("type");
            actualColumns.push_back({colName, colType});
        }

        // Compare column count
        if (actualColumns.size() != tableSpec.columns.size())
        {
            wxMessageBox("Table '" + wxString(tableName) + "' exists but column count does not match expected schema.", "Schema Warning", wxOK | wxICON_WARNING, this);
            success = false;
            continue;
        }

        // Compare column names and types
        for (size_t i = 0; i < tableSpec.columns.size(); ++i)
        {
            if (actualColumns[i].name != tableSpec.columns[i].name ||
                actualColumns[i].type != tableSpec.columns[i].type)
            {
                wxMessageBox("Table '" + wxString(tableName) + "' exists but column '" +
                    wxString(actualColumns[i].name) + "' does not match expected schema.", "Schema Warning", wxOK | wxICON_WARNING, this);
                success = false;
                break;
            }
        }
    }
    if (success)
    {
        std::cout << "[*] Database matches expected schema." << std::endl;
    }
}