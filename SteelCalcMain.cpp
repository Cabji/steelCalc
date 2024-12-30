#include "SteelCalcMain.h"
#include "CustomGridCellEditor.h"
#include <wx/msgdlg.h>
#include <wx/regex.h>

SteelCalcMain::SteelCalcMain(wxWindow* parent)
    : Main(parent)
{
    // Bind the event handler for grid cell value changes
    m_gridLValues->Bind(wxEVT_GRID_CELL_CHANGED, &SteelCalcMain::OnGridCellValueChanged, this);
    m_specsGandD->Bind(wxEVT_CHOICE, &SteelCalcMain::OnBarSpecChoiceChanged, this);

    // Set the custom cell editor for the grid cells
    m_gridLValues->SetDefaultEditor(new CustomGridCellEditor());

    // Fit the frame to its contents
    this->Fit();
}

SteelCalcMain::SteelCalcMain(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : Main(parent, id, title, pos, size, style)
{
    // Set the title of the frame
    SetTitle(title);

    // Hide a specific widget from the base class
    m_chbCircularInput->Hide();

    // Bind the event handler for grid cell value changes
    m_gridLValues->Bind(wxEVT_GRID_CELL_CHANGED, &SteelCalcMain::OnGridCellValueChanged, this);
    m_specsGandD->Bind(wxEVT_CHOICE, &SteelCalcMain::OnBarSpecChoiceChanged, this);

    // Set the custom cell editor for the grid cells
    m_gridLValues->SetDefaultEditor(new CustomGridCellEditor());

    wxString output(this->GetClassInfo()->GetClassName());
    std::cout << "Class Name of this: " << output << std::endl;
}

double SteelCalcMain::GetBarArea(const wxString &barSpec)
{
    double radius = GetBarRadius(barSpec);
    std::cout << "Bar radius: " << radius << std::endl;
    return M_PI * radius * radius;
}

double SteelCalcMain::GetBarRadius(const wxString &barSpec)
{
    // Extract the numeric value from the bar specification value (eg: N12, R6.5, SS16)
    wxRegEx re("[0-9.]+");
    wxString numericValue;
    if (re.Matches(m_processingCurrentBarSize))
    {
        numericValue = re.GetMatch(m_processingCurrentBarSize);
    }
    std::cout << "Numeric value: " << numericValue << std::endl;
    return wxAtof(numericValue) / 2 / 1000;
}

void SteelCalcMain::OnBarSpecChoiceChanged(wxCommandEvent &event)
{
    // Get the selected bar specification
    wxString selectedBarSpec = m_specsGandD->GetStringSelection();
    std::cout << "Selected bar spec: " << selectedBarSpec << std::endl;

    event.Skip();
    // Update the results
    UpdateResults();
}

void SteelCalcMain::OnGridCellValueChanged(wxGridEvent &event)
{
    // Get the row and column of the changed cell
    int row = event.GetRow();
    int col = event.GetCol();

    // Get the new value of the cell
    wxString newValue = m_gridLValues->GetCellValue(row, col);

    // Skip the event to allow further processing
    event.Skip();
    UpdateResults();
}

wxString SteelCalcMain::GetBarProcessingType(const int &numOfValues)
{
    // dev-note: this method sanitizes the input and returns appropriate type string for output
    wxString result = wxEmptyString;
    if (numOfValues < 0)
    {
        return result;
    }
    if (numOfValues > 3)
    {
        result = m_processingTypes[3];
    }
    else
    {
        result = m_processingTypes[numOfValues];
    }
    return result;
}

void SteelCalcMain::UpdateResults()
{
    // Update all the results on the steel calculator main frame
    std::cout << "Updating results..." << std::endl;

    int totalCellsWithValue = 0;
    double totalValue = 0.0;

    int numCols = m_gridLValues->GetNumberCols();

    for (int col = 0; col < numCols; ++col)
    {
        wxString cellValue = m_gridLValues->GetCellValue(0, col); // Assuming only 1 row
        if (cellValue.IsEmpty())
        {
            break; // Break the loop if a cell does not have a value
        }

        double value;
        if (cellValue.ToDouble(&value))
        {
            totalCellsWithValue++;
            totalValue += value;
        }
        else
        {
            // Handle the case where the cell value is not a valid number
            std::cerr << "Invalid number in cell (0, " << col << "): " << cellValue.ToStdString() << std::endl;
        }
    }

    // std::cout << "Total cells with value: " << totalCellsWithValue << std::endl;
    // std::cout << "Total value of cells: " << totalValue << std::endl;

    m_lblCalculatedTotalBarLength->SetLabel(wxString::Format("Total bar length: %.2f", totalValue));
    m_processingCurrentBarSize = m_specsGandD->GetStringSelection();
    double barArea = GetBarArea(m_processingCurrentBarSize);
    m_lblCalculatedProcessingType->SetLabel(GetBarProcessingType(totalCellsWithValue));
    m_lblCalculatedBarArea->SetLabel(wxString::Format("Bar area: %.8f", barArea));
    
    // Update the layout of the sizer
    m_containingSizer->Fit(this);
    //SetStatusText(wxString::Format("Total cells with value: %d, Total value: %.2f", totalCellsWithValue, totalValue));
}
