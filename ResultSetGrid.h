#ifndef RESULTSETGRID_H
#define RESULTSETGRID_H

#include <wx/grid.h>
#include <iostream>

struct Column
{
	std::int		index;
	std::string		colName;
	std::string		value;
}

struct Row
{
	std::vector<Column>		
}

class ResultSetGrid : public wxGrid
{
	public:
	// default ctr
	ResultSetGrid() : wxGrid() { };

};

#endif // RESULTSETGRID_H