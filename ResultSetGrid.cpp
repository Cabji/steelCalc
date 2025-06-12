#include "ResultSetGrid.h"


std::string ResultSetGrid::ClassName()
{
	return CLASS_NAME;
}

void ResultSetGrid::GridAdjustStructure(wxGrid &grid, const ResultSet &resultSet)
{
	// zero-check
    if (resultSet.rows.empty()) 
    {
		std::cout << CLASS_NAME << "::" << __func__ << "(): ResultSet was empty, no grid structure adjustment performed." << std::endl;
		return;
	}

	// local data acquisition
	int resultSetColCount = 0;
    int resultSetRowCount = static_cast<int>(resultSet.rows.size());
    std::vector<std::string> colNames;
	resultSetColCount = static_cast<int>(resultSet.rows[0].columns.size());

	// create vector of column names (colNames)
	for (int col = 0; col < resultSetColCount; ++col) 
	{
		colNames.push_back(resultSet.rows[0].columns[col].colName);
	}

	// dev-note: if the result set is empty, we cannot fallback to showing the column names in the grid because that responsibility 
	// is the calling code's. the calling code would have to detect the resultSet is empty, then do a PRAGMA SQL call to get the table 
	// schema data and pass THAT in as the resultSet (perhaps?)

    // ensure the grid has the correct number of columns
    if (grid.GetNumberCols() != resultSetColCount) 
    {
        if (grid.GetNumberCols() < resultSetColCount)
            grid.AppendCols(resultSetColCount - grid.GetNumberCols());
        else
            grid.DeleteCols(0, grid.GetNumberCols() - resultSetColCount);
    }

    // set column labels
    for (int col = 0; col < resultSetColCount; ++col) 
    {
        grid.SetColLabelValue(col, wxString(colNames[col]));
        grid.AutoSizeColLabelSize(col);
    }

    // ensure the grid has the correct number of rows
    if (grid.GetNumberRows() != resultSetRowCount) 
    {
        if (grid.GetNumberRows() < resultSetRowCount)
            grid.AppendRows(resultSetRowCount - grid.GetNumberRows());
        else
            grid.DeleteRows(0, grid.GetNumberRows() - resultSetRowCount);
    }
	return;
}

void ResultSetGrid::GridUpdateContent(wxGrid &grid, const ResultSet &resultSet, const bool cellsReadOnly)
{
	grid.ClearGrid();
    if (resultSet.rows.empty())
    {
        std::cout << CLASS_NAME << "::" << __func__ << "(): There were no results returned for this table." << std::endl;
        return;    
    }
 
    int resultSetColCount = static_cast<int>(resultSet.rows[0].columns.size());
    int resultSetRowCount = static_cast<int>(resultSet.rows.size());

    // fill grid with data, set the cells to read-only/editable depending on cellsReadOnly argument
    for (int row = 0; row < resultSetRowCount; ++row) 
    {
        for (int col = 0; col < resultSetColCount; ++col) 
        {
            grid.SetCellValue(row, col, wxString(resultSet.rows[row].columns[col].value));
            grid.SetReadOnly(row, col, cellsReadOnly);
        }
    }
}

// send a std::string query to the current database connection and retrieve the result set in a std::vector format
ResultSet ResultSetGrid::RequestDatabaseData(const std::string& dbFilename, const std::string& query)
{
	ResultSet   l_result;
    try
    {
		SQLite::Database	dbConnection(dbFilename);
		SQLite::Statement	dbQuery(dbConnection, query);
        // convert the result into std vector<vector<pair<string, string>>> data type and return
        while (dbQuery.executeStep()) 
        {
            Row    l_row;
            for (int col = 0; col < dbQuery.getColumnCount(); ++col)
            {
                std::string colName	= dbQuery.getColumnName(col);
                std::string value = dbQuery.getColumn(col).getText();
                l_row.columns.emplace_back(colName, value);
            }
            l_result.rows.push_back(std::move(l_row));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "SQL Query failed, error: " << e.what() << '\n';
    }

    return l_result;
}