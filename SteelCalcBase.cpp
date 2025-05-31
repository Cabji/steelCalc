///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SteelCalcBase.h"

///////////////////////////////////////////////////////////////////////////

Main::Main( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 925,600 ), wxDefaultSize );

	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuFileAbout;
	m_menuFileAbout = new wxMenuItem( m_menuFile, id_MENU_FILE_ABOUT, wxString( _("&About") ) , _("Show information about the program"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuFileAbout );

	wxMenuItem* m_menuFileOptions;
	m_menuFileOptions = new wxMenuItem( m_menuFile, id_MENU_FILE_OPTIONS, wxString( _("&Options") ) , _("Open program Options"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuFileOptions );

	wxMenuItem* m_menuFileDatabaseViewer;
	m_menuFileDatabaseViewer = new wxMenuItem( m_menuFile, id_MENU_FILE_DATABASEVIEWER, wxString( _("&Database Viewer") ) , _("Opens the Database Viewer"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuFileDatabaseViewer );

	wxMenuItem* m_menuFileExit;
	m_menuFileExit = new wxMenuItem( m_menuFile, id_MENU_FILE_EXIT, wxString( _("E&xit") ) , _("Exit the program"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuFileExit );

	m_menubar->Append( m_menuFile, _("File") );

	this->SetMenuBar( m_menubar );

	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_mainSizer = new wxGridBagSizer( 0, 0 );
	m_mainSizer->SetFlexibleDirection( wxBOTH );
	m_mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxSize( 900,470 ), wxHSCROLL|wxVSCROLL );
	m_scrolledWindow->SetScrollRate( 5, 5 );
	m_scrolledWindow->SetMinSize( wxSize( 900,470 ) );

	m_ScrolledWindowSizer = new wxGridBagSizer( 0, 0 );
	m_ScrolledWindowSizer->SetFlexibleDirection( wxBOTH );
	m_ScrolledWindowSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_barProcessSizer = new wxGridBagSizer( 0, 0 );
	m_barProcessSizer->SetFlexibleDirection( wxBOTH );
	m_barProcessSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblHeaderText = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Enter Item's dimensions below, one side for each Ln value. Enter the values in meters. Example: 600mm is 0.6\nA starter bar would be something like: L1: 1.0, L2: 0.2\nIf you want to calculate circular shaped bar fabrication, click the checkbox to switch to circular input mode."), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblHeaderText->Wrap( -1 );
	m_barProcessSizer->Add( m_lblHeaderText, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_chbCircularInput = new wxCheckBox( m_scrolledWindow, wxID_ANY, _("Circular Item Input"), wxDefaultPosition, wxDefaultSize, 0 );
	m_barProcessSizer->Add( m_chbCircularInput, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_lblBarGrade = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Grade && Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBarGrade->Wrap( -1 );
	m_barProcessSizer->Add( m_lblBarGrade, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	wxString m_specsGandDChoices[] = { _("N10"), _("N12"), _("N16"), _("N20"), _("N24"), _("N28"), _("N32"), _("N36"), _("N40"), _("R6.5"), _("R10"), _("R12"), _("R16"), _("R20"), _("R24"), _("S12"), _("SS12"), _("SS16") };
	int m_specsGandDNChoices = sizeof( m_specsGandDChoices ) / sizeof( wxString );
	m_specsGandD = new wxChoice( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_specsGandDNChoices, m_specsGandDChoices, 0 );
	m_specsGandD->SetSelection( 1 );
	m_barProcessSizer->Add( m_specsGandD, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_gridLValues = new wxGrid( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridLValues->CreateGrid( 1, 10 );
	m_gridLValues->EnableEditing( true );
	m_gridLValues->EnableGridLines( true );
	m_gridLValues->SetGridLineColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_gridLValues->EnableDragGridSize( false );
	m_gridLValues->SetMargins( 0, 0 );

	// Columns
	m_gridLValues->EnableDragColMove( false );
	m_gridLValues->EnableDragColSize( false );
	m_gridLValues->SetColLabelValue( 0, _("L1") );
	m_gridLValues->SetColLabelValue( 1, _("L2") );
	m_gridLValues->SetColLabelValue( 2, _("L3") );
	m_gridLValues->SetColLabelValue( 3, _("L4") );
	m_gridLValues->SetColLabelValue( 4, _("L5") );
	m_gridLValues->SetColLabelValue( 5, _("L6") );
	m_gridLValues->SetColLabelValue( 6, _("L7") );
	m_gridLValues->SetColLabelValue( 7, _("L8") );
	m_gridLValues->SetColLabelValue( 8, _("L9") );
	m_gridLValues->SetColLabelValue( 9, _("L10") );
	m_gridLValues->SetColLabelSize( wxGRID_AUTOSIZE );
	m_gridLValues->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridLValues->AutoSizeRows();
	m_gridLValues->EnableDragRowSize( false );
	m_gridLValues->SetRowLabelValue( 0, _("Value") );
	m_gridLValues->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridLValues->SetDefaultCellAlignment( wxALIGN_CENTER, wxALIGN_CENTER );
	m_barProcessSizer->Add( m_gridLValues, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_gridCircularLValues = new wxGrid( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridCircularLValues->CreateGrid( 1, 2 );
	m_gridCircularLValues->EnableEditing( true );
	m_gridCircularLValues->EnableGridLines( true );
	m_gridCircularLValues->EnableDragGridSize( false );
	m_gridCircularLValues->SetMargins( 0, 0 );

	// Columns
	m_gridCircularLValues->EnableDragColMove( false );
	m_gridCircularLValues->EnableDragColSize( false );
	m_gridCircularLValues->SetColLabelValue( 0, _("Diameter") );
	m_gridCircularLValues->SetColLabelValue( 1, _("Lap") );
	m_gridCircularLValues->SetColLabelSize( wxGRID_AUTOSIZE );
	m_gridCircularLValues->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridCircularLValues->SetRowSize( 0, 563 );
	m_gridCircularLValues->AutoSizeRows();
	m_gridCircularLValues->EnableDragRowSize( true );
	m_gridCircularLValues->SetRowLabelValue( 0, _("Value") );
	m_gridCircularLValues->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridCircularLValues->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_gridCircularLValues->Hide();

	m_barProcessSizer->Add( m_gridCircularLValues, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxALL, 5 );


	m_barProcessSizer->AddGrowableCol( 1 );
	m_barProcessSizer->AddGrowableRow( 0 );
	m_barProcessSizer->AddGrowableRow( 1 );
	m_barProcessSizer->AddGrowableRow( 2 );
	m_barProcessSizer->AddGrowableRow( 3 );
	m_barProcessSizer->AddGrowableRow( 4 );

	m_ScrolledWindowSizer->Add( m_barProcessSizer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	m_barCalculatorSizer = new wxGridBagSizer( 0, 0 );
	m_barCalculatorSizer->SetFlexibleDirection( wxBOTH );
	m_barCalculatorSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblBarCalculator = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Quantity Calculator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBarCalculator->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBarCalculator, wxGBPosition( 0, 0 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCSpan = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Span"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCSpan->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCSpan, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCBarCentre = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Centre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCBarCentre->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCBarCentre, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCTotalQty = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total Quantity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCTotalQty->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCTotalQty, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_BCSpan = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_barCalculatorSizer->Add( m_BCSpan, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_BCBarCentre = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_barCalculatorSizer->Add( m_BCBarCentre, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_BCTotalQty = new wxStaticText( m_scrolledWindow, wxID_ANY, _("0 bars"), wxDefaultPosition, wxDefaultSize, 0 );
	m_BCTotalQty->Wrap( -1 );
	m_barCalculatorSizer->Add( m_BCTotalQty, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );


	m_barCalculatorSizer->AddGrowableCol( 0 );
	m_barCalculatorSizer->AddGrowableCol( 1 );
	m_barCalculatorSizer->AddGrowableCol( 2 );

	m_ScrolledWindowSizer->Add( m_barCalculatorSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	m_labourCalculatorSizer = new wxGridBagSizer( 0, 0 );
	m_labourCalculatorSizer->SetFlexibleDirection( wxHORIZONTAL );
	m_labourCalculatorSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );

	m_lblLabourCalculator = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Steelfixing Labour Based on Area"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourCalculator->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourCalculator, wxGBPosition( 0, 0 ), wxGBSpan( 1, 6 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourLength = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourLength->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourLength, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourWidth = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourWidth->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourWidth, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourBarCentreA = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Centre A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourBarCentreA->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourBarCentreA, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourBarCentreB = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Centre B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourBarCentreB->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourBarCentreB, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourTieCentre = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Ties at every x centre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourTieCentre->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourTieCentre, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourTotalQtyTies = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total Quantity of Ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourTotalQtyTies->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourTotalQtyTies, wxGBPosition( 1, 5 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_LabourLength = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourLength, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_LabourWidth = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourWidth, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_LabourBarCentreA = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourBarCentreA, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_LabourBarCentreB = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourBarCentreB, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_LabourTieCentre = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourTieCentre, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_LabourTotalQtyTies = new wxStaticText( m_scrolledWindow, wxID_ANY, _("0 ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_LabourTotalQtyTies->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_LabourTotalQtyTies, wxGBPosition( 2, 5 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );


	m_labourCalculatorSizer->AddGrowableCol( 0 );
	m_labourCalculatorSizer->AddGrowableCol( 1 );
	m_labourCalculatorSizer->AddGrowableCol( 2 );
	m_labourCalculatorSizer->AddGrowableCol( 3 );
	m_labourCalculatorSizer->AddGrowableCol( 4 );
	m_labourCalculatorSizer->AddGrowableCol( 5 );
	m_labourCalculatorSizer->AddGrowableRow( 0 );
	m_labourCalculatorSizer->AddGrowableRow( 1 );
	m_labourCalculatorSizer->AddGrowableRow( 2 );

	m_ScrolledWindowSizer->Add( m_labourCalculatorSizer, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	m_CalculatedSizer = new wxGridBagSizer( 0, 0 );
	m_CalculatedSizer->SetFlexibleDirection( wxBOTH );
	m_CalculatedSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblCalculatedHeader = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Auto Calculated Values"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedHeader->SetLabelMarkup( _("Auto Calculated Values") );
	m_lblCalculatedHeader->Wrap( -1 );
	m_lblCalculatedHeader->SetBackgroundColour( wxColour( 240, 242, 149 ) );

	m_CalculatedSizer->Add( m_lblCalculatedHeader, wxGBPosition( 0, 0 ), wxGBSpan( 1, 4 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblCalculatedProcessingType = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Processing type: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedProcessingType->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedProcessingType, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_lblCalculatedTotalBarLength = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar length: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedTotalBarLength->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedTotalBarLength, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_lblCalculatedBarArea = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar area: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedBarArea->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedBarArea, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_lblCalculatedCostPerBar = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Cost: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedCostPerBar->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedCostPerBar, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_lblWeightPerBar = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Weight: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblWeightPerBar->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblWeightPerBar, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_lblWeightTotalMg = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Tonnage: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblWeightTotalMg->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblWeightTotalMg, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	m_lblCalculatedCostPerMg = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Mg Cost: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedCostPerMg->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedCostPerMg, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_btnClearAll = new wxButton( m_scrolledWindow, wxID_ANY, _("Clear All Input Entries"), wxDefaultPosition, wxDefaultSize, 0 );
	m_CalculatedSizer->Add( m_btnClearAll, wxGBPosition( 0, 5 ), wxGBSpan( 5, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	m_CalculatedSizer->AddGrowableCol( 0 );
	m_CalculatedSizer->AddGrowableCol( 1 );
	m_CalculatedSizer->AddGrowableCol( 2 );
	m_CalculatedSizer->AddGrowableCol( 3 );
	m_CalculatedSizer->AddGrowableRow( 0 );
	m_CalculatedSizer->AddGrowableRow( 1 );
	m_CalculatedSizer->AddGrowableRow( 2 );

	m_ScrolledWindowSizer->Add( m_CalculatedSizer, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );


	m_ScrolledWindowSizer->AddGrowableCol( 0 );
	m_ScrolledWindowSizer->AddGrowableRow( 0 );
	m_ScrolledWindowSizer->AddGrowableRow( 1 );
	m_ScrolledWindowSizer->AddGrowableRow( 2 );

	m_scrolledWindow->SetSizer( m_ScrolledWindowSizer );
	m_scrolledWindow->Layout();
	m_mainSizer->Add( m_scrolledWindow, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );


	m_mainSizer->AddGrowableCol( 0 );
	m_mainSizer->AddGrowableRow( 0 );

	this->SetSizer( m_mainSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

Main::~Main()
{
}

Options::Options( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 266,155 ), wxSize( -1,-1 ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	wxGridBagSizer* m_optionsSizer;
	m_optionsSizer = new wxGridBagSizer( 0, 0 );
	m_optionsSizer->SetFlexibleDirection( wxBOTH );
	m_optionsSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblOptionsLabour = new wxStaticText( this, wxID_ANY, _("<b>Labour</b>"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblOptionsLabour->SetLabelMarkup( _("<b>Labour</b>") );
	m_lblOptionsLabour->Wrap( -1 );
	m_optionsSizer->Add( m_lblOptionsLabour, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_TOP|wxALL, 5 );

	m_optionsLabourAddPerimeterTies = new wxCheckBox( this, wxID_ANY, _("Automatically add perimeter ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_optionsSizer->Add( m_optionsLabourAddPerimeterTies, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_optionsLabourAddSetupTies = new wxCheckBox( this, wxID_ANY, _("Automatically add setup ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_optionsSizer->Add( m_optionsLabourAddSetupTies, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_optionsLabourAddLapTies = new wxCheckBox( this, wxID_ANY, _("Automatically add estimated lap ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_optionsSizer->Add( m_optionsLabourAddLapTies, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblOptionsCalculationFactors = new wxStaticText( this, wxID_ANY, _("Calculation Factors"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblOptionsCalculationFactors->Wrap( -1 );
	m_optionsSizer->Add( m_lblOptionsCalculationFactors, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_lblOptionsCFBarGradeCosts = new wxStaticText( this, wxID_ANY, _("Bar Grade Costs"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblOptionsCFBarGradeCosts->Wrap( -1 );
	m_optionsSizer->Add( m_lblOptionsCFBarGradeCosts, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_optionsCalculationFactorsBarGradeCosts = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_optionsCalculationFactorsBarGradeCosts->CreateGrid( 3, 2 );
	m_optionsCalculationFactorsBarGradeCosts->EnableEditing( true );
	m_optionsCalculationFactorsBarGradeCosts->EnableGridLines( true );
	m_optionsCalculationFactorsBarGradeCosts->EnableDragGridSize( false );
	m_optionsCalculationFactorsBarGradeCosts->SetMargins( 0, 0 );

	// Columns
	m_optionsCalculationFactorsBarGradeCosts->SetColSize( 0, 73 );
	m_optionsCalculationFactorsBarGradeCosts->SetColSize( 1, 133 );
	m_optionsCalculationFactorsBarGradeCosts->EnableDragColMove( false );
	m_optionsCalculationFactorsBarGradeCosts->EnableDragColSize( true );
	m_optionsCalculationFactorsBarGradeCosts->SetColLabelValue( 0, _("Bar Name") );
	m_optionsCalculationFactorsBarGradeCosts->SetColLabelValue( 1, _("Cost per Mg") );
	m_optionsCalculationFactorsBarGradeCosts->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_optionsCalculationFactorsBarGradeCosts->AutoSizeRows();
	m_optionsCalculationFactorsBarGradeCosts->EnableDragRowSize( true );
	m_optionsCalculationFactorsBarGradeCosts->SetRowLabelSize( 0 );
	m_optionsCalculationFactorsBarGradeCosts->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_optionsCalculationFactorsBarGradeCosts->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_optionsCalculationFactorsBarGradeCosts->SetToolTip( _("Click column headings to sort by that column's values.") );

	m_optionsSizer->Add( m_optionsCalculationFactorsBarGradeCosts, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );


	m_optionsSizer->AddGrowableCol( 0 );
	m_optionsSizer->AddGrowableRow( 6 );

	this->SetSizer( m_optionsSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

Options::~Options()
{
}

DatabaseViewer::DatabaseViewer( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuFileAbout;
	m_menuFileAbout = new wxMenuItem( m_menuFile, id_MENU_FILE_ABOUT, wxString( _("&About") ) , _("Information about tis program"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuFileAbout );

	wxMenuItem* m_menuFileOptions;
	m_menuFileOptions = new wxMenuItem( m_menuFile, id_MENU_FILE_OPTIONS, wxString( _("&Load") ) , _("Load a SQLite datbase file"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuFileOptions );

	wxMenuItem* m_menuFileExit;
	m_menuFileExit = new wxMenuItem( m_menuFile, id_MENU_FILE_EXIT, wxString( _("E&xit") ) , _("Close the window"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuFileExit );

	m_menubar->Append( m_menuFile, _("File") );

	this->SetMenuBar( m_menubar );

	wxBoxSizer* m_sizer0;
	m_sizer0 = new wxBoxSizer( wxVERTICAL );

	wxGridBagSizer* m_uiGBSizer;
	m_uiGBSizer = new wxGridBagSizer( 0, 0 );
	m_uiGBSizer->SetFlexibleDirection( wxBOTH );
	m_uiGBSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_uiChoiceDBTablesLabel = new wxStaticText( this, wxID_ANY, _("Table:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_uiChoiceDBTablesLabel->Wrap( -1 );
	m_uiGBSizer->Add( m_uiChoiceDBTablesLabel, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxArrayString m_uiChoicesDBTablesChoices;
	m_uiChoicesDBTables = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_uiChoicesDBTablesChoices, 0 );
	m_uiChoicesDBTables->SetSelection( 0 );
	m_uiGBSizer->Add( m_uiChoicesDBTables, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_uiTableGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_uiTableGrid->CreateGrid( 5, 5 );
	m_uiTableGrid->EnableEditing( true );
	m_uiTableGrid->EnableGridLines( true );
	m_uiTableGrid->EnableDragGridSize( false );
	m_uiTableGrid->SetMargins( 0, 0 );

	// Columns
	m_uiTableGrid->EnableDragColMove( false );
	m_uiTableGrid->EnableDragColSize( true );
	m_uiTableGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_uiTableGrid->EnableDragRowSize( true );
	m_uiTableGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_uiTableGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_uiGBSizer->Add( m_uiTableGrid, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );


	m_uiGBSizer->AddGrowableCol( 1 );
	m_uiGBSizer->AddGrowableRow( 1 );

	m_sizer0->Add( m_uiGBSizer, 1, wxEXPAND, 5 );


	this->SetSizer( m_sizer0 );
	this->Layout();

	this->Centre( wxBOTH );
}

DatabaseViewer::~DatabaseViewer()
{
}
