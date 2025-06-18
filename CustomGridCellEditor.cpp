#include "CustomGridCellEditor.h"


void CustomGridCellEditor::ApplyEdit(int row, int col, wxGrid* grid)
{
    //std::cout << "Value in Apply Edit: " << m_sanitizedValue.ToStdString() << std::endl;
    grid->SetCellValue(row, col, m_sanitizedValue);
}

bool CustomGridCellEditor::EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval)
{
    m_row = row;
    m_col = col;
    m_grid = const_cast<wxGrid*>(grid);

    wxString value = GetValue();
    if (ValidateValue(value))
    {
        std::cout << "Valid value: " << value.ToStdString() << std::endl;
        *newval = value;
        m_sanitizedValue = value;
    }
    else
    {
        // dev-note: the way the sanitation works, there can never be invalid 
        // input. either it's valid, or the cell is cleared.
        // i don't know how i feel about this.
        std::cout << "Invalid value: " << value.ToStdString() << std::endl;
        return false;
    }

    // schedule a delayed save action with CustomEventScheduler
    // i think we need to change [this] to the parent of grid so that it points to the SteelCalcOptions class instance, 
    // then create a function in SteelCalcOptions that will save the grid's data to database
    CustomEventScheduler::Get().Schedule(
        "Options_BarGradesAndCosts_Save",
        [this]() { SaveBarGradeCostsToDatabase(); },
        1000 // delay in ms
    );

    return true;
}

void CustomGridCellEditor::SetValidationType(CustomGridCellEditor::ValidationType type) 
{
    m_validationType = type;
    std::cout << "CellEditor ValidationType set to " << type << std::endl;
}

bool CustomGridCellEditor::ValidateFloat(wxString& value)
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
    if (wxString(localeThousand) != wxEmptyString)
    {
        sanitizedInput.Replace(wxString(localeThousand), wxEmptyString);
    }

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

bool CustomGridCellEditor::ValidateInteger(wxString& value)
{
    long num;
    wxString sanitizedInput;

    // remove all non-numeric characters
    for (wxChar ch : value)
        if (wxIsdigit(ch))
            sanitizedInput += ch;

    // allow empty cell values
    if (sanitizedInput.IsEmpty())
    {
        value = sanitizedInput;
        return true;
    }

    // convert sanitized string to integer
    bool isValid = sanitizedInput.ToLong(&num);
    if (isValid) { value = sanitizedInput; }
    return isValid;
}

bool CustomGridCellEditor::ValidateString(wxString& value)
{
    //string validation is to just trim whitespace from both ends
    value = value.Trim().Trim(false);
    return true;
}

bool CustomGridCellEditor::ValidateValue(wxString& value)
{
    switch (m_validationType)
    {
        case ValidationType::FLOAT:
            return ValidateFloat(value);
        case ValidationType::INTEGER:
            return ValidateInteger(value);
        case ValidationType::STRING:
            return ValidateString(value);
        default:
            return false;
    }
}