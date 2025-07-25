#define SQLITE_ENABLE_COLUMN_METADATA
#include "ResultSetGrid.h"
#include <SQLiteCpp/Column.h>

// 
int ResultSetGrid::BuildQueryPopulate(const std::string& findTableToken, const std::string& findWhereToken)
{
    if (m_queryPopulate.empty())
    {
        std::cerr << CLASS_NAME << "::" << __func__ << "(): m_queryPopulate is empty, nothing to do so returning." << std::endl;;
        return -1;
    }

    std::string	whereClause = " WHERE ";
    bool 		firstCondition = true;
	int 		totalAdded = 0;

    for (const auto& pair : m_whereConditions)
    {
        // zero check, skip if either value is empty
        if (pair.first.empty() && pair.second.empty()) { continue; }

		if (!firstCondition)
		{
			whereClause += " AND ";
			firstCondition = false;
		}
        whereClause += pair.first + " LIKE '%" + pair.second + "%' ";
        totalAdded++;
    }

	// clear the whereClause if nothing was found in the conditions map
	if (totalAdded == 0) { whereClause.clear(); }
	// replace tokens - where clause, tableName
	StringReplaceAll(m_queryPopulate, findWhereToken, whereClause);
	StringReplaceAll(m_queryPopulate, findTableToken, m_tableName);
    // debug
    std::cout << CLASS_NAME << "::" << __func__ << "(): m_queryPopulate = " << m_queryPopulate << std::endl;;
	return totalAdded;
}

// builds SQL query for INSERTing grid data to a database table
std::string ResultSetGrid::BuildQueryInsert(const std::string &findTableToken)
{
    int rowCount = this->GetNumberRows();
    int colCount = this->GetNumberCols();

    // get columnLabelMap from [this] to know what the column names are in the database
	ResultSet* l_resultSet = this->GetResultSet();
	std::string insertSQL = "INSERT INTO " + this->GetTableName() + " (";
    for (int c = 0; c < colCount; ++c) 
    {
        std::string fieldName = l_resultSet->sm_columnLabelMap[this->GetColLabelValue(c).ToStdString()];
        insertSQL += fieldName;
        if (c < colCount - 1) insertSQL += ", ";
    }
    insertSQL += ") VALUES (";
    for (int c = 0; c < colCount; ++c) {
        insertSQL += "?";
        if (c < colCount - 1) insertSQL += ", ";
    }
    insertSQL += ")";
	return insertSQL;
}

std::string ResultSetGrid::ClassName()
{
	return CLASS_NAME;
}

ResultSet* ResultSetGrid::GetResultSet()
{
	return &this->m_resultSet;
}

void ResultSetGrid::GridAdjustStructure(wxGrid &grid, const ResultSet &resultSet)
{
	// zero-check
    if (resultSet.rows.empty()) 
    {
		std::cout << CLASS_NAME << "::" << __func__ << "(): ResultSet was empty, no this-> structure adjustment performed." << std::endl;
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

	// dev-note: if the result set is empty, we cannot fallback to showing the column names in the this-> because that responsibility 
	// is the calling code's. the calling code would have to detect the resultSet is empty, then do a PRAGMA SQL call to get the table 
	// schema data and pass THAT in as the resultSet (perhaps?)

    // ensure the this-> has the correct number of columns
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

    // ensure the this-> has the correct number of rows
    if (grid.GetNumberRows() != resultSetRowCount) 
    {
        if (grid.GetNumberRows() < resultSetRowCount)
            grid.AppendRows(resultSetRowCount - grid.GetNumberRows());
        else
            grid.DeleteRows(0, grid.GetNumberRows() - resultSetRowCount);
    }
	return;
}

// overload to use [this] as the this->
void ResultSetGrid::GridAdjustStructure(const ResultSet &resultSet)
{
    // copy the resultSet to the this->m_resultSet
    this->m_resultSet = resultSet;
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

    // extract data from this-> into vector of pairs
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

    // repopulate the this-> with sorted data
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
            // if (row == 0) { std::cout << "  " << CLASS_NAME << "::" << __func__ << "():\n       ColLabel = " << resultSet.rows[row].columns[col].colLabel << "\n       ColName = " << resultSet.rows[row].columns[col].colName << std::endl; }
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
                // this-> column name (as shown to the end-user)
                std::string colLabel = dbQuery.getColumnName(col);
                // column value (aka field value in database table) unique to this row, displayed in this->'s cell at (row,col)
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

ResultSet ResultSetGrid::RequestDatabaseData(const std::string &dbFilename)
{
    return RequestDatabaseData(dbFilename, this->m_queryPopulate);
}

// pull data FROM a ResutSetGrid and put it into a ResultSet (you can specify which rows and columns you want, or pass empty vector<int> object to get all value in the this->)
ResultSet ResultSetGrid::RequestGridData(const std::vector<int> &rowIndices, const std::vector<int> colIndices)
{
    ResultSet l_result;
    // determine which rows and columns to use
    std::vector<int> rows = rowIndices.empty() ? CreateVectorFromInt(this->GetNumberRows()) : rowIndices;
    std::vector<int> cols = colIndices.empty() ? CreateVectorFromInt(this->GetNumberCols()) : colIndices;

    for (int row : rows)
    {
        Row l_row;
        for (int col : cols)
        {
            // get each cell value and put it into the ResultSet
            // ensure we use this->resultSet->sm_columnLabelMap to get the origin name for columns in the this->
            // get the user-visible column label
            std::string colLabel = this->GetColLabelValue(col).ToStdString();
            std::string colName;

            // get the origin column name from the label map, or fallback to label if not found
            auto it = this->m_resultSet.sm_columnLabelMap.find(colLabel);
            if (it != this->m_resultSet.sm_columnLabelMap.end()) 
            {
                colName = it->second;
            } 
            else 
            {
                colName = colLabel;
                l_result.sm_columnLabelMap[colLabel] = colName;
            }

            std::string value = this->GetCellValue(row, col).ToStdString();
            l_row.columns.emplace_back(colLabel, colName, value);
        }
        l_result.rows.push_back(std::move(l_row));
    }
    return l_result;
}

// use this function to send data FROM a ResultSetGrid to a SQLite database table [this] = ResultSetGrid calling object
void ResultSetGrid::SaveFromGridToDatabase(const std::string& dbFilename, const std::string& tableName,  const std::string& primaryKeyName, const std::vector<int> &rowIndices, const std::vector<int> &colIndices)
{
	try 
	{
		SQLite::Database db(dbFilename, SQLite::OPEN_READWRITE);
		// pointer to this->m_resultSet.sm_columnLabelMap
		std::unordered_map<std::string, std::string>*	columnMap	= &this->m_resultSet.sm_columnLabelMap;
		int												pkColIndex	= -1;

		// determine which rows and columns to use from [this]
		std::vector<int>    rows = rowIndices.empty() ? CreateVectorFromInt(this->GetNumberRows()) : rowIndices;
		std::vector<int>    cols = colIndices.empty() ? CreateVectorFromInt(this->GetNumberCols()) : colIndices;

		// create a ResultSet from the requested locations in the this->
		for (int row : rows) 
		{
			// Build SQL: UPDATE table SET col1=?, col2=? WHERE id=?
			// the SQL UPDATE query we are building in this function
			std::string					query       = "UPDATE " + tableName + " SET ";
			std::vector<std::string>	setClauses;
			std::vector<wxString>		values;
			ResultSet					saveValues;

			// loop the columns in the current row
			for (int col : cols) 
			{
				// get the column Label (user-seen at top of grid column in the UI)
				std::string colLabel = this->GetColLabelValue(col).ToStdString();
				// try to find the position of this colLabel in the columnMap
				auto it = columnMap->find(colLabel);
				if (it != columnMap->end())
				{
					// get the colName (field name in the database that corressponds to the colLabel)
					std::string colName = it->second;
					// set the pkColIndex value, skip out and don't set the PK column value
					if (colName == primaryKeyName) { pkColIndex = col; continue; }
					// use the colName in the SQL UPDATE query
					setClauses.push_back(colName + "=?");
					// push the field value for this field name/colName into the values vector
					values.push_back(this->GetCellValue(row, col));
				}
			}
			// push the primary key's value to the end of the values vector
			values.push_back(GetCellValue(row, pkColIndex));

			// build query string from setClauses vector
			for (size_t i = 0; i < setClauses.size(); ++i) {
				if (i != 0) query += ", ";
				query += setClauses[i];
			}
			// use the primary key name in the UPDATE query for row identification
			query += " WHERE " + primaryKeyName + "=?";

            if (pkColIndex == -1) 
			{
                std::cerr << "Primary key column not found in grid columns." << std::endl;
                continue;
            }

			// prepare and execute statement with values
			SQLite::Statement dbQuery(db,query);
			for (size_t i = 0; i < values.size(); ++i)
			{
				dbQuery.bind(static_cast<int>(i + 1), values[i].ToStdString());
			}
			std::cout << dbQuery.getExpandedSQL() << std::endl;
			dbQuery.exec();
		}	
	}
	catch (const std::exception& e)
	{
		std::cerr << "Database update failed: " << e.what() << std::endl;
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

// helper function that will find & replace a std::string within another std::string (because the STL doesn't have this!)
void ResultSetGrid::StringReplaceAll(std::string &str, const std::string &from, const std::string &to)
	{
		size_t start_pos = 0;
		while((start_pos = str.find(from, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Move past the replacement
		}
	}

bool ResultSetGrid::UpdateGridDataCurrentState()
{
    // obtain the current state of the grid data
    // store the state in private members: 
    //  m_gridDataCurrentRows
    //  m_gridDataCurrentRowKeys

    int didSomething = 0;
    for (int i = 0; i < this->GetNumberRows(); ++i) 
    {
        // 
        m_gridDataCurrentRowKeys.push_back(this->GetCellValue(i, m_tablePrimaryKeyIndex));
        std::vector<wxString> rowData;
        for (int j = 0; j < this->GetNumberCols(); ++j) 
        {
            rowData.push_back(this->GetCellValue(i, j));
        }
        m_gridDataCurrentRows.push_back(rowData);
        didSomething++;
    }

    return didSomething;
}

bool ResultSetGrid::UpdateGridDataModifiedRows()
{
    // check for rows with modified data (in both grids but something in the row's data has been modified)
    // builds a vector of int values (m_gridDataModifiedRowIndices) that tells us the row indices that should be updated in the database table to make it match the grid in the UI
    int didSomething = 0;
    m_gridDataModifiedRowIndices.clear();
    
    for (size_t i = 0; i < m_gridDataCurrentRowKeys.size(); ++i) 
    {
        const wxString& currKey = m_gridDataCurrentRowKeys[i];
        // it = pointer to the row in the current data vector with the altered row data
        auto it = std::find(m_gridDataOriginalRowKeys.begin(), m_gridDataOriginalRowKeys.end(), currKey);
        if (it != m_gridDataOriginalRowKeys.end()) 
        {
            size_t origIdx = std::distance(m_gridDataOriginalRowKeys.begin(), it);
            if (m_gridDataCurrentRows[i] != m_gridDataOriginalRows[origIdx]) 
            {
                // Row changed
                m_gridDataModifiedRowIndices.push_back(static_cast<int>(i));
                didSomething++;
            }
        }
    }
    return didSomething;
}

bool ResultSetGrid::UpdateGridDataNewRows()
{
    // check for new added rows (in current grid data but not in original grid data)
    // builds a vector of int values (m_gridDataNewRowIndices) that tells us the row indices that should be added to the database table to make it match the grid in the UI
    int didSomething = 0;
    m_gridDataNewRowIndices.clear();

    for (size_t i = 0; i < m_gridDataCurrentRowKeys.size(); ++i) 
    {
        const wxString& currKey = m_gridDataCurrentRowKeys[i];
        // if we DO FIND the index value from data in the current vector and it is not found in the original vector data, INSERT the row data to the database
        if (std::find(m_gridDataOriginalRowKeys.begin(), m_gridDataOriginalRowKeys.end(), currKey) == m_gridDataOriginalRowKeys.end()) 
        {
            // push the new row's index ito the m_griDataNewRowIndices vector
            m_gridDataNewRowIndices.push_back(static_cast<int>(i));	
            didSomething++;		
        }
    }
    return didSomething;
}

bool ResultSetGrid::UpdateGridDataRemovedRows()
{
    // check for removed rows (in original grid data but not in current grid data)
    // builds a vector of wxStrings (m_gridDataRemovedRowPKs) that tells us the PK values of rows to remove from the database table data to that it matches the grid in the UI
    int didSomething = 0;
    m_gridDataRemovedRowPKs.clear();

    for (size_t i = 0; i < m_gridDataOriginalRowKeys.size(); ++i) 
    {
        const wxString& origKey = m_gridDataOriginalRowKeys[i];
        // if we DON'T find the Primary Key value from the original data in the current data vector, then add the PK value to the m_gridDataRemovedRowPKs vector to mark the row for deletion from the database
        if (std::find(m_gridDataCurrentRowKeys.begin(), m_gridDataCurrentRowKeys.end(), origKey) == m_gridDataCurrentRowKeys.end()) 
        {
            // push the removed row's PK value into m_gridDataRemovedRowPKs vector
            m_gridDataRemovedRowPKs.push_back(origKey);
            didSomething++;
        }
    }
    return didSomething;
}
