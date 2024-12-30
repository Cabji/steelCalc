#include "SteelCalcMain.h"
#include "CustomGridCellEditor.h"
#include <wx/msgdlg.h>
#include <wx/regex.h>

SteelCalcMain::SteelCalcMain(wxWindow* parent)
    : Main(parent)
{
    // initialize common construction code
    Init();
}

SteelCalcMain::SteelCalcMain(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : Main(parent, id, title, pos, size, style)
{
    // initialize common construction code
    Init();

    // Set the title of the frame
    SetTitle(title);
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

void SteelCalcMain::Init()
{
    // Bind the event handler for grid cell value changes
    m_gridLValues->Bind(wxEVT_GRID_CELL_CHANGED, &SteelCalcMain::OnGridCellValueChanged, this);
    m_gridCircularLValues->Bind(wxEVT_GRID_CELL_CHANGED, &SteelCalcMain::OnGridCellValueChanged, this);
    m_specsGandD->Bind(wxEVT_CHOICE, &SteelCalcMain::OnBarSpecChoiceChanged, this);
    m_chbCircularInput->Bind(wxEVT_CHECKBOX, &SteelCalcMain::OnCircularInputToggled, this);

    // Set the custom cell editor for the grid cells
    m_gridLValues->SetDefaultEditor(new CustomGridCellEditor());
    
    // detach the circular grid object from its sizer
    m_barProcessSizer->Detach(m_gridCircularLValues);

    wxString output(this->GetClassInfo()->GetClassName());
    std::cout << "Class Name of this: " << output << std::endl;
    
    // Fit the frame to its contents
    this->Fit();
    UpdateResults();
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
    wxGrid* grid;

    // choose which grid is being used
    if (m_gridCircularLValues->IsShown()) 
    {
        grid = m_gridCircularLValues;
    }
    else
    {
        grid = m_gridLValues;
    }
    // Get the new value of the cell
    wxString newValue = grid->GetCellValue(row, col);

    // Skip the event to allow further processing
    event.Skip();
    UpdateResults();
}

void SteelCalcMain::OnCircularInputToggled(wxCommandEvent &event)
{
    std::cout << "Circular input checkbox toggled!" << std::endl;
    // Perform actions based on the checkbox state
    if (event.IsChecked())
    {
        // swap user input grid to circular input grid - m_circularGridLValues
        m_barProcessSizer->Detach(m_gridLValues);
        m_gridLValues->Hide();
        m_barProcessSizer->Add(m_gridCircularLValues, wxGBPosition(2, 0), wxGBSpan(1, 2), wxALL, 5);
        m_gridCircularLValues->Show();
    }
    else
    {
        // swap user input grid to linear input grid - m_gridLValues
        m_barProcessSizer->Detach(m_gridCircularLValues);
        m_gridCircularLValues->Hide();
        m_barProcessSizer->Add(m_gridLValues, wxGBPosition(2, 0), wxGBSpan(1, 2), wxALL, 5);
        m_gridLValues->Show();
    }
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
    double itemDiameter = 0.0;
    double itemLapLength = 0.0;

    int numCols = m_gridLValues->GetNumberCols();

    if (m_gridCircularLValues->IsShown())
    {
        std::cout << "Circular input grid is shown!" << std::endl;
        // get values from input grid cells
        m_gridCircularLValues->GetCellValue(0, 0).ToDouble(&itemDiameter);
        m_gridCircularLValues->GetCellValue(0, 1).ToDouble(&itemLapLength);
    }

    if (m_gridLValues->IsShown())
    {
        // get values from input grid cells
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
    }
    // std::cout << "Total cells with value: " << totalCellsWithValue << std::endl;
    // std::cout << "Total value of cells: " << totalValue << std::endl;

    if (m_gridLValues->IsShown())
    {
        m_lblCalculatedTotalBarLength->SetLabel(wxString::Format("Total bar length: %.2f", totalValue));
        m_processingCurrentBarSize = m_specsGandD->GetStringSelection();
        double barArea = GetBarArea(m_processingCurrentBarSize);
        m_lblCalculatedProcessingType->SetLabel("Processing Type: " + GetBarProcessingType(totalCellsWithValue));
        m_lblCalculatedBarArea->SetLabel(wxString::Format("Bar area: %.8f", barArea));
        double barWeight = barArea * totalValue * MASS_N_GRADE_STEEL;
        m_lblWeightPerBar->SetLabel(wxString::Format("Weight per bar: %.8f Mg (%.2f Kg)", barWeight, barWeight * 1000));
        double barCost = barWeight * m_costPerMg;
        m_lblCalculatedCostPerMg->SetLabel(wxString::Format("Cost per bar: %.2f", barCost));
    }
    if (m_gridCircularLValues->IsShown())
    {
        std::cout << "Item diameter: " << itemDiameter << ", Item lap length: " << itemLapLength << std::endl;
        std::cout << "Total bar length: " << itemLapLength + M_PI * itemDiameter << std::endl;
        m_lblCalculatedTotalBarLength->SetLabel(wxString::Format("Total bar length: %.2f", itemLapLength + M_PI * itemDiameter));
    }

    // Update the layout of the sizer
    m_mainSizer->Layout();
    //SetStatusText(wxString::Format("Total cells with value: %d, Total value: %.2f", totalCellsWithValue, totalValue));
}
