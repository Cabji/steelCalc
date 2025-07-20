#ifndef RESULTSETGRID_H
#define RESULTSETGRID_H
#define CLASS_NAME "ResultSetGrid"

#include <wx/grid.h>
#include <iostream>
#include <print>
#include <unordered_map>
#include <string>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>

struct Column
{
	std::string			colLabel;	// user-seen column Label
	std::string			colName;	// column name as found in database table
	std::string			value;
};

struct Row
{
	std::vector<Column>	columns;
};

struct ResultSet
{
	std::vector<Row>	rows;
	// sm_columnLabelMap is a mapping of user-seen column Label Names => field names in database table, specifically for the current ResultSet's values
	std::unordered_map<std::string, std::string>	sm_columnLabelMap;
	void OutputColumnMap()
	{
		std::cout << CLASS_NAME << "::" << __func__ << "(): " << std::endl;
		std::cout << "	User-seen Label				DB Field Name" << std::endl;
		for (const auto& pair : sm_columnLabelMap)
		{
			std::cout << "	" << pair.first << "			" << pair.second << std::endl;
		}
	}
	
	void OutputResultSetInfo()
	{
		std::cout << CLASS_NAME << "::" << __func__ << "(): " << std::endl;
		std::cout << "  Number of Rows: " << rows.size() << std::endl;
		if (rows.size() > 0)
		{
			std::cout << "  Number of Columns: " << rows[0].columns.size() << std::endl;
			// output the data of the first row in the ResultSet
			std::cout << "	Sample of data: " << std::endl;
			for (const Column col : rows[0].columns)
			{
				std::cout << "		Grid Label:	" << col.colLabel 
						  << "		Field Name:	" << col.colName 
						  << "		Value:	" << col.value 
						  << std::endl;
			}
		}
	}
};

// this class is a customised wxGrid object that will make 
//		displaying result sets 
//		interacting with grid <-> database
// easier
class ResultSetGrid : public wxGrid
{
	public:
	// default ctr
	ResultSetGrid() : wxGrid() { };
	// 4 param ctr (required by base class)
	ResultSetGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const int i)
        : wxGrid(parent, id, pos, size, i) { }

			int					BuildQueryPopulate(const std::string& findTableToken = "#TABLENAME#", const std::string& findWhereToken = "#WHERECLAUSE#");
			std::string			BuildQueryInsert(const std::string& findTableToken = "#TABLENAME#");

			std::string			ClassName();
			ResultSet*			GetResultSet();
			std::string			GetTableName() { return m_tableName; };
			std::string			GetTablePrimaryKey() { return m_tablePrimaryKey; };

	static	void				GridAdjustStructure(wxGrid& grid, const ResultSet& resultSet);
			void				GridAdjustStructure(const ResultSet& resultSet);
			void				GridAdjustStructure();
	static	void				GridInsertFilterRow(wxGrid& grid);
	static	void				GridSort(wxGridEvent& event);
	static	void				GridUpdateContent(wxGrid& grid, 
											  const ResultSet& resultSet, 
											  const bool& cellsReadOnly = true, 
											  const bool& adjustWidthToCellValues = false);
			void				GridUpdateContent(const ResultSet& resultSet, 
											  const bool& cellsReadOnly = true, 
											  const bool& adjustWidthToCellValues = false);
			void				GridUpdateContent(const bool& cellsReadOnly = true, 
											  const bool& adjustWidthToCellValues = false);

	static	ResultSet			RequestDatabaseData(const std::string& dbFilename, const std::string& query);
			ResultSet			RequestDatabaseData(const std::string& dbFilename);
			ResultSet			RequestGridData(const std::vector<int>& rows, const std::vector<int> cols); // pull data FROM a wxgrid and put it into a ResultSet (you can specify which rows and columns you want, or pass empty vector<int> object to get all value in the grid)
			void				SaveFromGridToDatabase(const std::string& dbFilename, const std::string& tableName, const std::string& primaryKeyName, const std::vector<int>& rows, const std::vector<int>& cols);

			void				SetPopulateQuery(const std::string& query) { m_queryPopulate = query; return; }
			void				SetTableName(const std::string& table) { m_tableName = table; return; }
			void				SetTablePrimaryKey(const std::string& pk) { m_tablePrimaryKey = pk; return; }
			void				SetWhereClauseConditions(const std::unordered_map<std::string, std::string>& theConditions) { m_whereConditions = theConditions; return; }

			bool				UpdateGridDataCurrentState(); // updates the grid's current "data state" ready to use to send to a database
			bool				UpdateGridDataModifiedRows();	// detects and updates state of any grid data that has been modified by the end user
			bool				UpdateGridDataNewRows();		// detects and updates state of any grid data that has been added by the end user
			bool				UpdateGridDataRemovedRows();	// detects and updates state of any grid data that has been removed by the end user

	private:
	static	std::vector<int>	CreateVectorFromInt(const int& i);
			void				StringReplaceAll(std::string& str, const std::string& from, const std::string& to);
	
	// private members

	std::vector<wxString>				m_gridDataOriginalRowKeys;				// the *original* state of the grid's data (Primary Key values from each row)
	std::vector<std::vector<wxString>>	m_gridDataOriginalRows;					// the *original* state of the grid's data (all row data)
	std::vector<wxString>				m_gridDataCurrentRowKeys;				// the *current* state of the grid's data (Primary Key values from each row)
	std::vector<std::vector<wxString>>	m_gridDataCurrentRows;					// the *current* state of the grid's data (all row data)
	std::vector<int>					m_gridDataModifiedRowIndices;			// holds row index values that have been modified in the grid data since it was created in the UI
	std::vector<int>					m_gridDataNewRowIndices;				// holds row index values that have been added to the grid data since it was created in the UI
	std::vector<wxString>				m_gridDataRemovedRowPKs;				// holds PK values that have been removed from the grid data since it was created in the UI
	std::vector<int>					m_gridDataRemovedRowsIndices;			// holds the indices of any removed rows removed from the grid since it was created in the UI

	ResultSet							m_resultSet;							// the latest ResultSet associated with this grid
	std::string							m_tableName;							// the tableName associated with this grid
	std::string							m_tablePrimaryKey;						// the Primary Key's column name associated with the current table
	int									m_tablePrimaryKeyIndex			= 0;	// the Primary Key's column index
	
	// the SQL query that is used to populate the ResultSetGrid [this]
	// this query allows a custom WHERE clause by using a token (default is #WHERECLAUSE#)
	// the WHERE clause is built using values from m_whereConditions
	std::string							m_queryPopulate;
	std::string							m_querySave;							// SQL query that is used to save data from the ResultSetGrid [this]
	std::unordered_map<std::string, std::string> m_whereConditions;				// WHERE clause conditions; key => value pairs for use in m_queryPopulate WHERE clause
};

#endif // RESULTSETGRID_H