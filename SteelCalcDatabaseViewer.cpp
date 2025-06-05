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

	// default DV to view only mode
	m_uiTableGrid->EnableEditing(false);
	UpdateUI("databaseViewerTables");

	// bind event handlers
	m_uiChoicesDBTables->Bind(wxEVT_CHOICE, &SteelCalcDatabaseViewer::OnDatabaseActiveTableChoiceChanged, this);
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

void SteelCalcDatabaseViewer::OnDatabaseActiveTableChoiceChanged(wxEvent &event)
{
	// handle when user chooses which database table to view

	// 1. Get the selected table name from the wxChoice widget
    int selectionIndex = m_uiChoicesDBTables->GetSelection();
    if (selectionIndex == wxNOT_FOUND) {
        std::cerr << "No table selected." << std::endl;
        return;
    }
    wxString selectedTable = m_uiChoicesDBTables->GetString(selectionIndex);
    m_dbActiveTableName = selectedTable.ToStdString();

    // 2. Clear out m_uiTableGrid
    m_uiTableGrid->ClearGrid();

    // 3. Query the selected table and display its contents
    std::string query = "SELECT * FROM " + m_dbActiveTableName;
    m_dbQuery = std::make_unique<SQLite::Statement>(*m_dbConnection, query);

	// 3.5 Set the Column Title Names
	int colCount = m_dbQuery->getColumnCount();
    if (m_uiTableGrid->GetNumberCols() != colCount)
    {
        m_uiTableGrid->ClearGrid();
        if (m_uiTableGrid->GetNumberCols() < colCount)
            m_uiTableGrid->AppendCols(colCount - m_uiTableGrid->GetNumberCols());
        else if (m_uiTableGrid->GetNumberCols() > colCount)
            m_uiTableGrid->DeleteCols(0, m_uiTableGrid->GetNumberCols() - colCount);
    }

    // create the filter row at the top
    if (m_uiTableGrid->GetNumberRows() == 0) { m_uiTableGrid->AppendRows(1); }
    m_uiTableGrid->SetRowLabelValue(0, "Filter");
    // the filter row's background colour
    wxColour filterBg(220, 240, 255);

    // make the filter row editable & set background colour
    for (int col = 0; col < m_uiTableGrid->GetNumberCols(); ++col) 
    {
        m_uiTableGrid->SetCellBackgroundColour(0, col, filterBg);
        m_uiTableGrid->SetReadOnly(0, col, false);
        m_uiTableGrid->SetCellValue(0, col, "test");
    }

    bool columnHeadersSet = false;
    // dev-note: we set row to 1 here to prevent the filter row at the top from having table data written into it
    int row = 1;

    // populate the grid with the data from the result set
    while (m_dbQuery->executeStep()) 
	{
        // Set column headers only once
        if (!columnHeadersSet)
        {
            for (int col = 0; col < colCount; ++col)
            {
                wxString colName = m_dbQuery->getColumn(col).getName();
                m_uiTableGrid->SetColLabelValue(col, colName);
                m_uiTableGrid->AutoSizeColLabelSize(col);
            }
            columnHeadersSet = true;
        }

        // Ensure the grid has enough rows
        if (row >= m_uiTableGrid->GetNumberRows())
            m_uiTableGrid->AppendRows(1);

        for (int col = 0; col < colCount; ++col)
        {
            wxString value = m_dbQuery->getColumn(col).getText();
            m_uiTableGrid->SetCellValue(row, col, value);
            m_uiTableGrid->SetReadOnly(row, col, true);
        }
        m_uiTableGrid->SetRowLabelValue(row, wxString::Format("%d", row));
        std::cout << "row: " << row << std::endl;
        ++row;
    }
    // Remove any extra rows if the new result set is smaller than the previous
    int extraRows = m_uiTableGrid->GetNumberRows() - row;
    if (extraRows > 0)
        m_uiTableGrid->DeleteRows(row, extraRows);
	
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

std::vector<std::vector<std::pair<std::string, std::string>>> SteelCalcDatabaseViewer::RequestDatabaseData(std::string query)
{
	std::vector<
		std::vector<
			std::pair<
				std::string, 
				std::string
			>
		>
	>						l_result;
	std::vector<
		std::pair<
			std::string, 
			std::string
		>
	>						l_row;
							m_dbQuery	= std::make_unique<SQLite::Statement>(*m_dbConnection, query);
	
	// convert the result into std vector<vector<pair<string, string>>> data type and return
	 while (m_dbQuery->executeStep()) 
	{
        for (int col = 0; col < m_dbQuery->getColumnCount(); ++col)
        {
			std::string colName	= m_dbQuery->getColumnName(col);
            std::string value = m_dbQuery->getColumn(col).getText();
			l_row.emplace_back(colName, value);
        }
		l_result.push_back(std::move(l_row));
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