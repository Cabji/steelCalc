#define SQLITE_ENABLE_COLUMN_METADATA
#include "ResultSetGrid.h"
#include <SQLiteCpp/Column.h>

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
	int                         resultSetColCount = 0;
    int                         resultSetRowCount = static_cast<int>(resultSet.rows.size());
    std::vector<std::string>    colLabels;

	resultSetColCount = static_cast<int>(resultSet.rows[0].columns.size());

	// create vector of user-seen column labels (colLabels)
	for (int col = 0; col < resultSetColCount; ++col) 
	{
		colLabels.push_back(resultSet.rows[0].columns[col].colLabel);
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
        grid.SetColLabelValue(col, wxString(colLabels[col]));
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

// overload to use [this] as the grid
void ResultSetGrid::GridAdjustStructure(const ResultSet &resultSet)
{
    GridAdjustStructure(*this, resultSet);
}

void ResultSetGrid::GridAdjustStructure()
{
    GridAdjustStructure(m_resultSet);
}

void ResultSetGrid::GridSort(wxGridEvent &event)
{
    // dev-note: we are sorting based on col 0 atm but if user clicks on col 1
    // it is breaking the data. implement support for sort by any col.
    
    wxGrid* triggerGrid = dynamic_cast<wxGrid*>(event.GetEventObject());
    if (!triggerGrid)
    {
        std::cerr << CLASS_NAME << "::" << __func__ << "(): Grid sort event triggered, but wxGrid object was not the trigger object." << std::endl;
        event.Skip();
        return;
    }

    // local data acquisition
    int colToSort   = event.GetCol();
    int rowCount    = triggerGrid->GetNumberRows();
    int colCount    = triggerGrid->GetNumberCols();
    
    if (rowCount <= 1)
    {
        // only 1 row, no sorting needed.
        return;
    }

    // extract data from grid into vector of pairs
    std::vector<std::vector<wxString>> gridData;
    for (int i = 0; i < rowCount; ++i)
    {
        std::vector<wxString> rowData;
        for (int j = 0; j < colCount; ++j)
        {
            rowData.push_back(triggerGrid->GetCellValue(i,j));
        }
        gridData.push_back(rowData);
    }

    // sort the data in ascending order (alphanumerical) based on the key
    std::sort(gridData.begin(), gridData.end(), [colToSort](const std::vector<wxString>& a, const std::vector<wxString>& b) {
        return a[colToSort].Cmp(b[colToSort]) < 0; // using wxString::Cmp for comparison
    });

    // repopulate the grid with sorted data
    for (int i = 0; i < rowCount; ++i)
    {
        for (int j = 0; j < colCount; ++j)
        {
            triggerGrid->SetCellValue(i, j, gridData[i][j]);
        }
    }

    std::cout << CLASS_NAME << "::" << __func__ << "(): Grid sorted by column " << colToSort << std::endl;
    triggerGrid->DeselectCol(colToSort);
}

void ResultSetGrid::GridUpdateContent(wxGrid &grid, const ResultSet &resultSet, const bool& cellsReadOnly, const bool& adjustWidthToCellValues)
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
            // debug
            if (row == 0) { std::cout << "  " << CLASS_NAME << "::" << __func__ << "():\n       ColLabel = " << resultSet.rows[row].columns[col].colLabel << "\n       ColName = " << resultSet.rows[row].columns[col].colName << std::endl; }
        }
    }
    grid.AutoSizeColumns(adjustWidthToCellValues);
}

void ResultSetGrid::GridUpdateContent(const ResultSet &resultSet, const bool &cellsReadOnly, const bool &adjustWidthToCellValues)
{
    GridUpdateContent(*this, resultSet, cellsReadOnly, adjustWidthToCellValues);
}

void ResultSetGrid::GridUpdateContent(const bool &cellsReadOnly, const bool &adjustWidthToCellValues)
{
    GridUpdateContent(m_resultSet, cellsReadOnly, adjustWidthToCellValues);
}

// send a std::string query to the current database connection and retrieve the result set in a std::vector format
ResultSet ResultSetGrid::RequestDatabaseData(const std::string& dbFilename, const std::string& query)
{
	ResultSet   l_result;
    try
    {
		SQLite::Database	dbConnection(dbFilename);
		SQLite::Statement	dbQuery(dbConnection, query);

        // convert the result into std vector<vector<pair<string, string, string>>> data type and return
        while (dbQuery.executeStep()) 
        {
            Row    l_row;
            for (int col = 0; col < dbQuery.getColumnCount(); ++col)
            {
                // dev-note: remember - colLabel = user-seen column Label, colName = name of field (column) in the database table

                // origin column name (as it is in the database table)
                std::string colName = dbQuery.getColumn(col).getOriginName();
                // grid column name (as shown to the end-user)
                std::string colLabel = dbQuery.getColumnName(col);
                // column value (aka field value in database table) unique to this row, displayed in grid's cell at (row,col)
                std::string value = dbQuery.getColumn(col).getText();
                if (colLabel.empty()) { colLabel = colName; }
                l_row.columns.emplace_back(colLabel, colName, value);
                // set colLabel => colName association in ResultSet struct's sm_columnLabelMap
                l_result.sm_columnLabelMap[colLabel] = colName;
            }
            l_result.rows.push_back(std::move(l_row));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << CLASS_NAME << "::" << __func__ << "(): SQL Query failed, error: " << e.what() << '\n';
    }

    return l_result;
}

// use this function to pull data FROM a wxgrid and put it into a ResultSet (you can specify which rows and columns you want)
ResultSet ResultSetGrid::RequestGridData(const wxGrid &grid, const std::vector<int> &rowIndices, const std::vector<int> colIndices)
{
    // determine which rows and columns to use
    std::vector<int> rows = rowIndices.empty() ? CreateVectorFromInt(grid.GetNumberRows()) : rowIndices;
    std::vector<int> cols = colIndices.empty() ? CreateVectorFromInt(grid.GetNumberCols()) : colIndices;

	return ResultSet();
}

// use this function to send data FROM a wxgrid to a SQLite database table
void ResultSetGrid::SaveFromGridToDatabase(const wxGrid &grid, const std::string& tableName, const std::vector<int> &rowIndices, const std::vector<int> &colIndices)
{
    // determine which rows and columns to use
    std::vector<int>    rows = rowIndices.empty() ? CreateVectorFromInt(grid.GetNumberRows()) : rowIndices;
    std::vector<int>    cols = colIndices.empty() ? CreateVectorFromInt(grid.GetNumberCols()) : colIndices;

    // create a ResultSet from the grid's data

    for (int row : rows) {
        // Build SQL: UPDATE table SET col1=?, col2=? WHERE id=?
        std::string                 query       = "UPDATE " + tableName + " SET ";
        std::vector<std::string>    setClauses;
        std::vector<wxString>       values;
        ResultSet                   saveValues;
        for (int col : cols) 
        {
            std::string colLabel = grid.GetColLabelValue(col).ToStdString();
            setClauses.push_back(colLabel + "=?");
            values.push_back(grid.GetCellValue(row, col));
        }
        // build query string from values vector
        for (size_t i = 0; i < setClauses.size(); ++i) {
            if (i != 0) query += ", ";
            query += setClauses[i];
        }
        query += " WHERE itemName=?"; // assuming 'id' is your PK
        //values.push_back(GetCellValue(row, idColIndex));

        // Prepare and execute statement with values...
    }
}

// creates a vector with int values in it from 0 to i
std::vector<int> ResultSetGrid::CreateVectorFromInt(const int &i)
{
    std::vector<int>    result;
    for (int j = 0; j < i; j++)
    {
        result.push_back(j);
    }
	return result;
}
