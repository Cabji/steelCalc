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
        wxString value = GetValue();
        if (ValidateValue(value))
        {
            std::cout << "Valid value: " << value.ToStdString() << std::endl;
            *newval = value;
            // dev-note: we have to store the sanitized value in a member variable 
            // because ApplyEdit() will use the unsanitized value if we use GetValue()
            m_sanitizedValue = value;
            return true;
        }
        else
        {
            std::cout << "Invalid value: " << value.ToStdString() << std::endl;
            return false;
        }
    }

    virtual void ApplyEdit(int row, int col, wxGrid* grid) override
    {
        wxString value = m_sanitizedValue;
        grid->SetCellValue(row, col, value);
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
        
        // if the user empties the cell, set it to 0
        if (sanitizedInput.IsEmpty())
        {
            sanitizedInput = "0";
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

    // class members
    wxString m_sanitizedValue; 
};

#endif // CUSTOMGRIDCELLEDITOR_H