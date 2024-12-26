#include "SteelCalcMain.h"
#include "CustomGridCellEditor.h"
#include <wx/msgdlg.h>

SteelCalcMain::SteelCalcMain(wxWindow* parent)
    : Main(parent)
{
    // Bind the event handler for grid cell value changes
    m_gridLValues->Bind(wxEVT_GRID_CELL_CHANGED, &SteelCalcMain::OnGridCellValueChanged, this);

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

    // Set the custom cell editor for the grid cells
    m_gridLValues->SetDefaultEditor(new CustomGridCellEditor());

    // Fit the frame to its contents
    this->Fit();
}

void SteelCalcMain::OnGridCellValueChanged(wxGridEvent& event)
{
    // Get the row and column of the changed cell
    int row = event.GetRow();
    int col = event.GetCol();

    // Get the new value of the cell
    wxString newValue = m_gridLValues->GetCellValue(row, col);

    // Skip the event to allow further processing
    event.Skip();
}

void SteelCalcMain::UpdateResults()
{
    // Update all the results on the steel calculator main frame
    // This function will be called when the user changes any of the input values

    
}
