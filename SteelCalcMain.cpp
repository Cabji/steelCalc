#include "CustomGridCellEditor.h"
#include "SteelCalcMain.h"
#include <algorithm>
#include <cmath>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>
#include <wx/regex.h>

SteelCalcMain::SteelCalcMain(wxWindow *parent)
    : Main(parent)
{
    // initialize common construction code
    Init();
}

SteelCalcMain::SteelCalcMain(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : Main(parent, id, title, pos, size, style)
{
    // initialize common construction code
    Init();

    // Set the title of the frame
    SetTitle(title);
}

void SteelCalcMain::Init()
{
    std::cout << "We are in SteelCalcMain ctr (OnInit)" << std::endl;
    // point to the Helper frame instances
    m_optionsFrame = new SteelCalcOptions(this);
    m_dbViewerFrame = new SteelCalcDatabaseViewer(this, "", "inventory");

    std::cout << "Default config file is: "     << DEFAULT_CONFIG_FILENAME      << std::endl
              << "Default database file is: "   << DEFAULT_DATABASE_FILENAME    << std::endl;
   
    // class data acquisition

    // dev-note: database object will be handled in the SteelCalcDatabaseViewer class
	// m_dbMain		= std::make_unique<SQLite::Database>    (DEFAULT_DATABASE_FILENAME, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    // m_dbQuery		= std::make_unique<SQLite::Statement>   (*m_dbMain, "SELECT * FROM inventory");

    // local data acquisition
    auto specNames	= m_specsGandD->GetStrings();
    // Set the custom cell editor for grid cells and set their validation type
    m_gridLValues->SetDefaultEditor(new CustomGridCellEditor());
    CustomGridCellEditor* lValuesEditor = dynamic_cast<CustomGridCellEditor*>(m_gridLValues->GetCellEditor(0,0));
    if (lValuesEditor != nullptr)
    {
        lValuesEditor->SetValidationType(CustomGridCellEditor::ValidationType::FLOAT);
    }
    else {std::cerr << "lValues grid editor object was found to be nullptr" << std::endl;}
    
    // load settings from config file 
    SettingsLoadAllFromDisk();

    // temoporary database testing code
    // while (m_dbQuery->executeStep())
    // {
    //     auto output = m_dbQuery->getColumn("itemName").getString() + " from: " + m_dbQuery->getColumn("supplierName").getString();
    //     std::cout << output << std::endl;
    // }
    
    // Bind event handlers
    Bind(wxEVT_CLOSE_WINDOW, &SteelCalcMain::OnClose, this);
    Bind(wxEVT_MENU, &SteelCalcMain::OnMenuFileAbout, this, id_MENU_FILE_ABOUT);
    Bind(wxEVT_MENU, &SteelCalcMain::OnMenuFileDatabaseViewer, this, id_MENU_FILE_DATABASEVIEWER);
    Bind(wxEVT_MENU, &SteelCalcMain::OnMenuFileOptions, this, id_MENU_FILE_OPTIONS);
    Bind(wxEVT_MENU, &SteelCalcMain::OnMenuFileExit, this, id_MENU_FILE_EXIT);
    m_BCBarCentre->Bind(wxEVT_KILL_FOCUS, &SteelCalcMain::OnTextCtrlValueChanged, this);
    m_BCSpan->Bind(wxEVT_KILL_FOCUS, &SteelCalcMain::OnTextCtrlValueChanged, this);
    m_btnClearAll->Bind(wxEVT_BUTTON, &SteelCalcMain::OnBtnClearAllInputEntries, this);
    m_chbCircularInput->Bind(wxEVT_CHECKBOX, &SteelCalcMain::OnCircularInputToggled, this);
    m_gridLValues->Bind(wxEVT_GRID_CELL_CHANGED, &SteelCalcMain::OnGridCellValueChanged, this);
    m_gridCircularLValues->Bind(wxEVT_GRID_CELL_CHANGED, &SteelCalcMain::OnGridCellValueChanged, this);
    m_LabourBarCentreA->Bind(wxEVT_KILL_FOCUS, &SteelCalcMain::OnTextCtrlValueChanged, this);
    m_LabourBarCentreB->Bind(wxEVT_KILL_FOCUS, &SteelCalcMain::OnTextCtrlValueChanged, this);
    m_LabourLength->Bind(wxEVT_KILL_FOCUS, &SteelCalcMain::OnTextCtrlValueChanged, this);
    m_LabourTieCentre->Bind(wxEVT_KILL_FOCUS, &SteelCalcMain::OnTextCtrlValueChanged, this);
    m_LabourWidth->Bind(wxEVT_KILL_FOCUS, &SteelCalcMain::OnTextCtrlValueChanged, this);
    m_specsGandD->Bind(wxEVT_CHOICE, &SteelCalcMain::OnBarSpecChoiceChanged, this);

    m_gridLValues->Layout();

    // detach the circular grid object from its sizer
    m_barProcessSizer->Detach(m_gridCircularLValues);

    wxString output(this->GetClassInfo()->GetClassName());
    std::cout << "Class Name of this: " << output << std::endl;

    // Fit the frame to its contents
    this->Fit();
    UpdateResults();
}

double SteelCalcMain::GetBarArea(const wxString &barSpec)
{
    double radius = GetBarRadius(barSpec);
    std::cout << "Bar radius: " << radius << std::endl;
    return M_PI * radius * radius;
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

void SteelCalcMain::OnBtnClearAllInputEntries(wxCommandEvent& event)
{
    // Display a confirmation dialog
    int response = wxMessageBox("Are you sure you want to clear all input fields?", "Confirm Clear All", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION, this);

    if (response == wxYES)
    {
        // Clear all input fields
        m_BCBarCentre->SetValue("");
        m_BCSpan->SetValue("");
        m_LabourBarCentreA->SetValue("");
        m_LabourBarCentreB->SetValue("");
        m_LabourLength->SetValue("");
        m_LabourTieCentre->SetValue("");
        m_LabourWidth->SetValue("");
        m_gridLValues->ClearGrid();
        m_gridCircularLValues->ClearGrid();

        // Update results after clearing
        UpdateResults();
    }

    event.Skip();
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
        m_barProcessSizer->Add(m_gridCircularLValues, wxGBPosition(3, 0), wxGBSpan(1, 2), wxALL, 5);
        m_gridCircularLValues->Show();
    }
    else
    {
        // swap user input grid to linear input grid - m_gridLValues
        m_barProcessSizer->Detach(m_gridCircularLValues);
        m_gridCircularLValues->Hide();
        m_barProcessSizer->Add(m_gridLValues, wxGBPosition(3, 0), wxGBSpan(1, 2), wxALL, 5);
        m_gridLValues->Show();
    }
    UpdateResults();
    event.Skip();
}

void SteelCalcMain::OnClose(wxCloseEvent &event)
{
    SettingsSaveAllToDisk();
    event.Skip();
}

void SteelCalcMain::OnGridCellValueChanged(wxGridEvent &event)
{
    // Get the row and column of the changed cell
    int row = event.GetRow();
    int col = event.GetCol();
    wxGrid *grid;

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

void SteelCalcMain::OnMenuFileAbout(wxCommandEvent &event)
{
    wxMessageBox(wxString::Format("Steel Calculator v%.1f\n\nCalculate information about steel reinforcement.\n\ngithub.com/cabji/steelcalc", APP_VERSION), "About Steel Calculator", wxOK | wxICON_INFORMATION, this);
}

void SteelCalcMain::OnMenuFileOptions(wxCommandEvent &event)
{
    if (!m_optionsFrame)
    {
        std::cout << "Options frame does not exist!" << std::endl;
        m_optionsFrame = new SteelCalcOptions(this);
    }
    else
    {
        std::cout << "Options frame exists!" << std::endl;
        m_optionsFrame->Show(true);
    }
    event.Skip();
}

void SteelCalcMain::OnMenuFileDatabaseViewer(wxCommandEvent &event)
{
    if (!m_dbViewerFrame)
    {
        std::cerr << "Database Viewer frame does not exist!" << std::endl;
    }
    {
        std::cout << "Showing Database Viewer..." << std::endl;
        m_dbViewerFrame->Show(true);
    }
    event.Skip();
}

void SteelCalcMain::OnMenuFileExit(wxCommandEvent &event)
{
    if (wxMessageBox("Confirm...", "Are you sure?", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION, this) == wxYES)
    {
        Close(true);
    }
}

void SteelCalcMain::OnTextCtrlValueChanged(wxFocusEvent &event)
{
    wxTextCtrl *textCtrl = dynamic_cast<wxTextCtrl *>(event.GetEventObject());
    std::cout << "Text Ctrl value changed!" << std::endl;
    wxString value = textCtrl->GetValue();
    ValidateValue(value);
    textCtrl->SetValue(value);
    UpdateResults();
    event.Skip();
}

void SteelCalcMain::SettingsLoadAllFromDisk()
{
    // check for conf file existence
    if (!wxFileName::FileExists(DEFAULT_CONFIG_FILENAME))
    {
        std::cout << "Config file does not exist. Using default settings." << std::endl;
        return;
    }

    // local data acquisition
    wxFileConfig    configObj("SteelCalc", wxEmptyString, DEFAULT_CONFIG_FILENAME);
    bool            tempValue;
    int             counter = 0;

    // read values from config file
    configObj.SetPath("/");
    configObj.Read("LabourAddLapTies", &tempValue);
    m_optionsFrame->SetAddLapTies(tempValue);
    configObj.Read("LabourAddPerimeterTies", &tempValue);
    m_optionsFrame->SetAddPerimeterTies(tempValue);
    configObj.Read("LabourAddSetupTies", &tempValue);
    m_optionsFrame->SetAddSetupTies(tempValue);
    
    if (configObj.HasGroup("BarGradeCosts"))
    {
        wxVector<std::pair<wxString, wxString>> barData;
        wxString                                barGrade, costPerMg;
        long                                    index = 0;
        counter = configObj.GetNumberOfEntries();
        configObj.SetPath("/BarGradeCosts");
        
        if (configObj.GetFirstEntry(barGrade, index))
        {
            do
            {
                configObj.Read(barGrade, &costPerMg);
                // std::cout << "Bar grade: " << barGrade << ", Cost per Mg: " << costPerMg << std::endl;
                barData.push_back(std::make_pair(barGrade, costPerMg));
            }
            while(configObj.GetNextEntry(barGrade, index));
        }
        std::cout << "Processed " << counter << " bar grades from config file." << std::endl;
        m_optionsFrame->SetBarClassificationData(barData);
    }
    std::cout << "Settings loaded from config file '" << DEFAULT_CONFIG_FILENAME << "'" << std::endl;
}

void SteelCalcMain::SettingsSaveAllToDisk()
{

    wxFileConfig configObj("SteelCalc", wxEmptyString, DEFAULT_CONFIG_FILENAME);
    // add the values that you want to save below here
    configObj.Write("LabourAddLapTies", m_optionsFrame->GetAddLapTies());
    configObj.Write("LabourAddPerimeterTies", m_optionsFrame->GetAddPerimeterTies());
    configObj.Write("LabourAddSetupTies", m_optionsFrame->GetAddSetupTies());
    SettingsSaveBarGradeCostsToDisk(configObj);
    configObj.Flush();
    if (configObj.Flush())
    {
        std::cout << "Settings saved to config file '" << DEFAULT_CONFIG_FILENAME << "'" << std::endl;
    }
    else
    {
        std::cerr << "!!! Settings failed to save to file '" << DEFAULT_CONFIG_FILENAME << "'" << std::endl;
    }
}

void SteelCalcMain::SettingsSaveBarGradeCostsToDisk(wxFileConfig &configObj)
{
    configObj.DeleteGroup("BarGradeCosts");
    configObj.SetPath("BarGradeCosts");
    wxVector<std::pair<wxString, wxString>> barData = m_optionsFrame->GetBarClassificationData();
    for (std::pair<wxString, wxString> barCost : barData)
    {
        configObj.Write(barCost.first, barCost.second);
    }
}

void SteelCalcMain::UpdateResults()
{
    // Update all the results on the steel calculator main frame
    std::cout << "Updating results..." << std::endl;

    int totalCellsWithValue = 0;
    double itemTotalLength = 0.0;
    double itemDiameter = 0.0;
    double itemLapLength = 0.0;
    double l_barArea = 0.0;
    double l_barWeight = 0.0;
    double l_barCost = 0.0;
    double l_bcTotalMg = 0.0;
    double l_bcTotalCost = 0.0;

    int numCols = m_gridLValues->GetNumberCols();

    // fetch text control values as appropriate to UI (circular or standard UI input)
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
                itemTotalLength += value;
            }
            else
            {
                // Handle the case where the cell value is not a valid number
                std::cerr << "Invalid number in cell (0, " << col << "): " << cellValue.ToStdString() << std::endl;
            }
        }
    }
    // std::cout << "Total cells with value: " << totalCellsWithValue << std::endl;
    // std::cout << "Total value of cells: " << itemTotalLength << std::endl;

    // output updated values for bar attributes: total length, bar area, processing type, bar weight, bar cost etc.
    if (m_gridLValues->IsShown())
    {
        m_lblCalculatedTotalBarLength->SetLabel(wxString::Format("Total bar length: %.2f", itemTotalLength));
        m_processingCurrentBarSize = m_specsGandD->GetStringSelection();
        l_barArea = GetBarArea(m_processingCurrentBarSize);
        m_lblCalculatedProcessingType->SetLabel("Processing Type: " + GetBarProcessingType(totalCellsWithValue));
        m_lblCalculatedBarArea->SetLabel(wxString::Format("Bar area: %.8f", l_barArea));
        l_barWeight = l_barArea * itemTotalLength * MASS_N_GRADE_STEEL;
        m_lblWeightPerBar->SetLabel(wxString::Format("Weight per bar: %.8f Mg (%.2f Kg)", l_barWeight, l_barWeight * 1000));
        l_barCost = l_barWeight * m_costPerMg;
        m_lblCalculatedCostPerBar->SetLabel(wxString::Format("Bar Cost: %.2f", l_barCost));
    }
    if (m_gridCircularLValues->IsShown())
    {
        std::cout << "Item diameter: " << itemDiameter << ", Item lap length: " << itemLapLength << std::endl;
        std::cout << "Total bar length: " << itemLapLength + M_PI * itemDiameter << std::endl;
        m_lblCalculatedTotalBarLength->SetLabel(wxString::Format("Total bar length: %.2f", itemLapLength + M_PI * itemDiameter));
    }

    // Calculate the total number of bars required & total tonnage
    double l_bcSpan = 0.0;
    double l_bcBarCentre = 0.0;
    if (m_BCSpan->GetValue().ToDouble(&l_bcSpan) && 
        m_BCBarCentre->GetValue().ToDouble(&l_bcBarCentre) && 
        (l_bcBarCentre != 0.0))
    {
        int l_bcTotalBars = static_cast<int>(l_bcSpan / l_bcBarCentre + 1);
        l_bcTotalMg = l_bcTotalBars * l_barWeight;
        l_bcTotalCost = l_bcTotalMg * m_costPerMg;
        m_BCTotalQty->SetLabel(wxString::Format("%d bars", l_bcTotalBars));
        m_lblWeightTotalMg->SetLabel(wxString::Format("Tonnage: %.8f Mg (%.2f Kg)", l_bcTotalMg, l_bcTotalMg * 1000));
        m_lblCalculatedCostPerMg->SetLabel(wxString::Format("Mg Cost: %.2f ", l_bcTotalCost));
    }
    else
    {
        // required factors are not available so set result to 0
        m_BCTotalQty->SetLabel("0 bars");
        m_lblWeightTotalMg->SetLabel("Tonnage: 0.0000000 Mg (0.00 Kg)");
        m_lblCalculatedCostPerMg->SetLabel("Mg Cost: 0.00 ");
    }

    // Calculate the steelfixing labour unit 'SFU' amount (number of ties in an Area)
    
    // local data acquisition
    double l_labourLength = 0.0;
    double l_labourWidth = 0.0;
    double l_labourBarCentreA = 0.0;
    double l_labourBarCentreB = 0.0;
    double l_labourTieCentre = 0.0;

    // check we got everything we need and in the right format
    if (m_LabourLength->GetValue().ToDouble(&l_labourLength) && 
        m_LabourWidth->GetValue().ToDouble(&l_labourWidth) && 
        m_LabourBarCentreA->GetValue().ToDouble(&l_labourBarCentreA) && 
        m_LabourBarCentreB->GetValue().ToDouble(&l_labourBarCentreB) && 
        m_LabourTieCentre->GetValue().ToDouble(&l_labourTieCentre))
    {
        // calculation formulas
        double l_labourAspectRatio = std::max(l_labourLength, l_labourWidth) / std::min(l_labourLength, l_labourWidth);
        double l_labourArea = l_labourLength * l_labourWidth;
        double l_labourAvgSide = sqrt(l_labourArea);
        double l_labourAvgPerimeter = 2 * (sqrt(l_labourArea / l_labourAspectRatio) + sqrt(l_labourArea * l_labourAspectRatio));
        double l_labourActualPerimeter = 2 * (l_labourLength + l_labourWidth);
        double l_labourTotalBars = std::ceil(l_labourLength / l_labourBarCentreA + 1) + std::ceil(l_labourWidth / l_labourBarCentreB + 1);
        double l_labourTiesPerBar = std::ceil(l_labourLength / l_labourTieCentre);
        double l_labourTotalQtyTies = std::ceil(l_labourTiesPerBar * (l_labourWidth / l_labourBarCentreB + 1));
        if (m_optionsFrame->GetAddPerimeterTies())
        {
            l_labourTotalQtyTies += (std::ceil(l_labourLength / l_labourBarCentreA) + std::ceil(l_labourWidth / l_labourBarCentreB)) * 2;
        }
        if (m_optionsFrame->GetAddSetupTies())
        {
            l_labourTotalQtyTies += (l_labourLength / 3.0) * (l_labourWidth / l_labourBarCentreB);
        }
        if (m_optionsFrame->GetAddLapTies())
        {
            l_labourTotalQtyTies += (l_labourWidth / l_labourBarCentreA);
        }
        m_LabourTotalQtyTies->SetLabel(wxString::Format("%d ties", static_cast<int>(l_labourTotalQtyTies)));
    
    }
    else
    {
        // required factors are not available so set result to 0
        m_LabourTotalQtyTies->SetLabel("0 ties");
    }
    // Update the layout of the sizer
    m_mainSizer->Layout();
    // SetStatusText(wxString::Format("Total cells with value: %d, Total value: %.2f", totalCellsWithValue, itemTotalLength));
}

bool SteelCalcMain::ValidateValue(wxString &value)
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