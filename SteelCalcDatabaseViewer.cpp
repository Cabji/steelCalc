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
	// use default filename if none given
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
	UpdateUI("databaseViewerTables");
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

void SteelCalcDatabaseViewer::UpdateUI(const std::string &sectionName)
{
	// dev-note: you can refresh UI elements by specific section name
	// or all UI elements by using section name "all" (or empty sectionName)
	if (sectionName == "databaseViewerTables" || sectionName == "dbvt" || sectionName == "all" || sectionName.empty())
	{
		std::cout << "Number of tables availalbe: " << m_dbAvailableTableNames.size() << std::endl;
		// dev-note: std::set should automatically sort the table names for us
		for (const std::string tableName : m_dbAvailableTableNames)
		{
			m_uiChoicesDBTables->Append(wxString(tableName));
		}
		std::cout << "We made it to here" << std::endl;
	}
	Layout();
	Refresh();
}
