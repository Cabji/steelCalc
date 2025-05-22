#include "SteelCalcDatabaseViewer.h"

SteelCalcDatabaseViewer::SteelCalcDatabaseViewer( wxWindow* parent )
:
DatabaseViewer( parent )
{
	// Try to connect to the database file (use default filename)
    m_dbConnection = std::make_unique<SQLite::Database>(
        DEFAULT_DATABASE_FILENAME, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
}

SteelCalcDatabaseViewer::SteelCalcDatabaseViewer( wxWindow* parent, std::string dbFilename, std::string tableName )
:
DatabaseViewer(parent)
{
	// dev-note: we have delegated the db connection to the default constructor in this overloaded ctr.
	// data acquisition
	m_dbActiveTableName = tableName;

	// override the filename and table name if provided
    if (!dbFilename.empty()) 
	{
        m_dbFilename	= dbFilename;
        m_dbConnection	= std::make_unique<SQLite::Database>(m_dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    }

    // Set up the query for the active table
    if (m_dbConnection)
	{
        m_dbQuery = std::make_unique<SQLite::Statement>(*m_dbConnection, "SELECT * FROM " + m_dbActiveTableName);
    }
}
