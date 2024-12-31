#ifndef CUSTOMGRIDCELLEDITOR_H
#define CUSTOMGRIDCELLEDITOR_H

#include <wx/grid.h>
#include <wx/numformatter.h>
#include <iostream>

class CustomGridCellEditor : public wxGridCellTextEditor
{
public:
    CustomGridCellEditor() : wxGridCellTextEditor() {}

    virtual bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override
    {
        m_row = row;
        m_col = col;
        m_grid = const_cast<wxGrid*>(grid);

        wxString value = GetValue();
        if (ValidateValue(value))
        {
            std::cout << "Valid value: " << value.ToStdString() << std::endl;
            *newval = value;
            m_sanitizedValue = value; // Store the sanitized value
            return true;
        }
        else
        {
            // dev-note: the way the sanitation works, there can never be invalid 
            // input. either it's valid, or the cell is cleared.
            // i don't know how i feel about this.
            std::cout << "Invalid value: " << value.ToStdString() << std::endl;
            return false;
        }
    }

    virtual void ApplyEdit(int row, int col, wxGrid* grid) override
    {
        //std::cout << "Value in Apply Edit: " << m_sanitizedValue.ToStdString() << std::endl;
        grid->SetCellValue(row, col, m_sanitizedValue); // Use the sanitized value
    }

private:
    bool ValidateValue(wxString& value)
    {
        // In here we need to sanitize the cell input value to ensure it can be converted to double type
        // We need to deal with the locale-specific decimal separator and thousands separator so use wxNumberFormatter for that
        double num;
        wxString sanitizedInput;

        // Get the locale-specific decimal and thousand separators
        wxChar localeDecimal = wxNumberFormatter::GetDecimalSeparator();
        wxChar *localeThousand;
        wxNumberFormatter::GetThousandsSeparatorIfUsed(localeThousand);

        // Remove all non-numeric characters except the decimal separator
        for (wxChar ch : value)
        {
            if (wxIsdigit(ch) || ch == localeDecimal)
            {
                sanitizedInput += ch;
            }
        }

        // Remove the locale-specific thousand separator
        sanitizedInput.Replace(wxString(localeThousand), wxEmptyString);

        // Allow empty cell values
        if (sanitizedInput.IsEmpty())
        {
            value = sanitizedInput; // Assign the empty value back to the reference
            return true;
        }

        // Convert the sanitized string to double
        bool isValid = sanitizedInput.ToDouble(&num);
        if (isValid)
        {
            value = sanitizedInput; // Assign the sanitized value back to the reference
        }
        std::cout << "Sanitized value: " << sanitizedInput.ToStdString() << ", isValid: " << isValid << std::endl;
        return isValid;
    }

    wxString m_sanitizedValue; // Member variable to store the sanitized value
    int m_row, m_col; // Row and column of the cell being edited
    wxGrid* m_grid; // Pointer to the grid
};

#endif // CUSTOMGRIDCELLEDITOR_H