#include "SteelCalcDatabaseViewer.h"

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
    std::cout << "	m_dbFilename: " << m_dbFilename << std::endl << "	m_dbActiveTableName: " << m_dbActiveTableName << std::endl;

	// override the filename and table name if provided
    if (dbFilename.empty()) 
	{
		// no database filename to open so quit
		std::cerr << "No database filename was passed to SteelCalcDatabaseViewer constructor so returning with no database connection." << std::endl;
		return;
    }

    m_dbFilename	= dbFilename;
    m_dbConnection	= std::make_unique<SQLite::Database>(m_dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // Set up the query for the active table
    if (!m_dbConnection)
	{
		// database connection failed
		std::cerr << "Connection to database file '" << m_dbFilename << "' failed." << std::endl;
		return;		
	}

	m_dbQuery = std::make_unique<SQLite::Statement>(*m_dbConnection, "SELECT * FROM " + m_dbActiveTableName);

	// Loop through the results and print each row
	while (m_dbQuery->executeStep())
	{
		int columnCount = m_dbQuery->getColumnCount();
		for (int i = 0; i < columnCount; ++i)
		{
			std::cout << m_dbQuery->getColumn(i).getName() << ": " << m_dbQuery->getColumn(i).getText() << "  ";
		}
		std::cout << std::endl;
	}    
}
