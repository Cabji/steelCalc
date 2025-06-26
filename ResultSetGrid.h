#ifndef RESULTSETGRID_H
#define RESULTSETGRID_H
#define CLASS_NAME "ResultSetGrid"

#include <wx/grid.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>

// this is a test commit

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
			std::string		ClassName();
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
			ResultSet		RequestGridData(const wxGrid&, const std::vector<int>& rows, const std::vector<int> cols);
	static	void			SaveFromGridToDatabase(const wxGrid& grid, const std::string& tableName, const std::vector<int>& rows, const std::vector<int>& cols);

	private:
	static	std::vector<int>		CreateVectorFromInt(const int& i);
	void							OutputResultSetInfo();
	ResultSet										m_resultSet;
};

#endif // RESULTSETGRID_H