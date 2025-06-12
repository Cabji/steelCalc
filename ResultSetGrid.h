#ifndef RESULTSETGRID_H
#define RESULTSETGRID_H
#define CLASS_NAME "ResultSetGrid"

#include <wx/grid.h>
#include <iostream>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>

struct Column
{
	std::string			colName;
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

// this class is a customised wxGrid object that will make displaying result sets easier
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
	

	private: 
};

#endif // RESULTSETGRID_H