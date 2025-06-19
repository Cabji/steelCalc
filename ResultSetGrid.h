#ifndef RESULTSETGRID_H
#define RESULTSETGRID_H
#define CLASS_NAME "ResultSetGrid"

#include <wx/grid.h>
#include <iostream>
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
	std::vector<Row> 	rows;
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
	static	void			GridInsertFilterRow(wxGrid& grid);
	static	void			GridSort(wxGridEvent& event);
	static	void			GridUpdateContent(wxGrid& grid, 
											  const ResultSet& resultSet, 
											  const bool& cellsReadOnly = true, 
											  const bool& adjustWidthToCellValues = false);
	static	ResultSet		RequestDatabaseData(const std::string& dbFilename, const std::string& query);
	static	void			SaveFromGridToDatabase(const wxGrid& grid, const std::string& tableName, const std::vector<int>& rows, const std::vector<int>& cols);

	private:
};

#endif // RESULTSETGRID_H