#ifndef RESULTSETGRID_H
#define RESULTSETGRID_H
#define CLASS_NAME "ResultSetGrid"

#include <wx/grid.h>
#include <iostream>

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
	void			GridAdjustStructure(wxGrid& grid, const ResultSet& resultSet);
	void			GridInsertFilterRow(wxGrid& grid);
	void			GridUpdateContent(wxGrid& grid, const ResultSet& resultSet, const bool cellsReadOnly = true);

	private: 
};

#endif // RESULTSETGRID_H