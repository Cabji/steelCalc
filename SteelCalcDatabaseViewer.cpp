#include "SteelCalcDatabaseViewer.h"
#include <set>
#include <string>

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

	std::cout << "we reckon we got here with a successful connection to db. filename used was: " << m_dbFilename << std::endl;
	// data acquisition
	m_dbAvailableTableNames = DatabaseFetchTableNames(*m_dbConnection);

	// update UI
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
	// handle when user chooses which datbase table to view
	// get tablename from m_uiChoicesDBTables
	// clear out db viewer grid
	// select data from active table to display in grid
	
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

    bool columnsSet = false;
    int row = 0;
    while (m_dbQuery->executeStep()) 
	{
        // Set column headers only once
        if (!columnsSet)
        {
            for (int col = 0; col < colCount; ++col)
            {
                wxString colName = m_dbQuery->getColumn(col).getName();
                m_uiTableGrid->SetColLabelValue(col, colName);
            }
            columnsSet = true;
        }

        // Ensure the grid has enough rows
        if (row >= m_uiTableGrid->GetNumberRows())
            m_uiTableGrid->AppendRows(1);

        for (int col = 0; col < colCount; ++col)
        {
            wxString value = m_dbQuery->getColumn(col).getText();
            m_uiTableGrid->SetCellValue(row, col, value);
        }
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
