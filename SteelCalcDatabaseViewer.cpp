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
    std::cout << "We are in the overloaded ctr" << std::endl;
	// dev-note: we have delegated the db connection to the default constructor in this overloaded ctr.
	// data acquisition
	m_dbActiveTableName = tableName;

	// override the filename and table name if provided
    if (dbFilename.empty()) 
	{
		m_dbFilename	= DEFAULT_DATABASE_FILENAME;
		// no database filename to open so quit
		std::cerr << "	!! - No database filename was passed to SteelCalcDatabaseViewer constructor so using default value instead." << std::endl;
    }

    m_dbConnection	= std::make_unique<SQLite::Database>(m_dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // Set up the query for the active table
    if (!m_dbConnection)
	{
		// database connection failed
		std::cerr << "	Connection to database file '" << m_dbFilename << "' failed." << std::endl;
		return;		
	}

	std::cout << "	Active Table Name: " << m_dbActiveTableName << std::endl;
	m_dbQuery = std::make_unique<SQLite::Statement>(*m_dbConnection, "SELECT name FROM sqlite_master WHERE type='table';");

	// Loop through the results and print each row
	while (m_dbQuery->executeStep())
	{
		int columnCount = m_dbQuery->getColumnCount();
		for (int i = 0; i < columnCount; ++i)
		{
			std::cout << "	" << m_dbQuery->getColumn(i).getName() << ":			" << m_dbQuery->getColumn(i).getText() << std::endl;
		}
		std::cout << std::endl;
	}    
}

std::set<std::string> SteelCalcDatabaseViewer::DatabaseFetchTableNames(const SQLite::Database& dbConnection)
{
	// get table names from a SQLite database connection
	std::set<std::string> l_setTableNames;
	m_dbQuery = std::make_unique<SQLite::Statement>(dbConnection, "SELECT name FROM sqlite_master WHERE type='table';");
	while (m_dbQuery->executeStep())
	{
		for (int i = 0; i < m_dbQuery->getColumnCount(); ++i)
		{
			if (m_dbQuery->getColumn(i).getName() == "name")
			{
				l_setTableNames.insert(m_dbQuery->getColumn(i).getText());
			}
		}
	}
	return l_setTableNames;
}