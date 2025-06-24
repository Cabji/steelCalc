#ifndef CUSTOMGRIDCELLEDITOR_H
#define CUSTOMGRIDCELLEDITOR_H

#include <wx/grid.h>
#include <wx/numformatter.h>
#include <iostream>
#include "CustomEventScheduler.h"

class CustomGridCellEditor : public wxGridCellTextEditor
{
public:
    // define each data type for input sanitization/validation here
    enum class ValidationType
    {
        FLOAT,
        INTEGER,
        STRING
    };

    CustomGridCellEditor() : wxGridCellTextEditor() {};
    virtual void    ApplyEdit(int row, int col, wxGrid* grid) override;
    virtual bool    EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
    void            SetValidationType(CustomGridCellEditor::ValidationType type);

private:
    // create a function for each data type to validate the input value
    bool ValidateFloat(wxString& value);
	bool ValidateInteger(wxString& value);
	bool ValidateString(wxString& value);
    bool ValidateValue(wxString& value);

    wxString								m_sanitizedValue; 
    int										m_row, m_col; 
    CustomGridCellEditor::ValidationType	m_validationType;
    wxGrid*									m_grid;
};

inline std::ostream& operator<<(std::ostream& os, CustomGridCellEditor::ValidationType type) {
    switch (type) {
        case CustomGridCellEditor::ValidationType::FLOAT:   os << "FLOAT"; break;
        case CustomGridCellEditor::ValidationType::INTEGER: os << "INTEGER"; break;
        case CustomGridCellEditor::ValidationType::STRING:  os << "STRING"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}

#endif // CUSTOMGRIDCELLEDITOR_H