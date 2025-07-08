#ifndef RESULTSETGRID_H
#define RESULTSETGRID_H
#define CLASS_NAME "ResultSetGrid"

#include <wx/grid.h>
#include <iostream>
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

			std::string		ClassName();
			ResultSet*		GetResultSet();
			std::string		GetTableName() { return m_tableName; };
			std::string		GetTablePrimaryKey() { return m_tablePrimaryKey; };
	static	void			GridAdjustStructure(wxGrid& grid, const ResultSet& resultSet);
			void			GridAdjustStructure(const ResultSet& resultSet);
			void			GridAdjustStructure();
	static	void			GridInsertFilterRow(wxGrid& grid);
	static	void			GridSort(wxGridEvent& event);
	static	void			GridUpdateContent(wxGrid& grid, 
											  const ResultSet& resultSet, 
											  const bool& cellsReadOnly = true, 
											  const bool& adjustWidthToCellValues = false);
			void			GridUpdateContent(const ResultSet& resultSet, 
											  const bool& cellsReadOnly = true, 
											  const bool& adjustWidthToCellValues = false);
			void			GridUpdateContent(const bool& cellsReadOnly = true, 
											  const bool& adjustWidthToCellValues = false);
	static	ResultSet		RequestDatabaseData(const std::string& dbFilename, const std::string& query);
// pull data FROM a wxgrid and put it into a ResultSet (you can specify which rows and columns you want, or pass empty vector<int> object to get all value in the grid)			
			ResultSet		RequestGridData(const std::vector<int>& rows, const std::vector<int> cols);
			void			SaveFromGridToDatabase(const std::string& dbFilename, const std::string& tableName, const std::string& primaryKeyName, const std::vector<int>& rows, const std::vector<int>& cols);
			void			SetTableName(const std::string& table) { m_tableName = table; return; }
			void			SetTablePrimaryKey(const std::string& pk) { m_tablePrimaryKey = pk; return; }

	private:
	static	std::vector<int>		CreateVectorFromInt(const int& i);
	void							OutputResultSetInfo();
	ResultSet						m_resultSet;
	std::string						m_tableName;
	std::string						m_tablePrimaryKey;
};

#endif // RESULTSETGRID_H