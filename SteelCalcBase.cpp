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
	this->SetSizeHints( wxSize( 920,690 ), wxDefaultSize );

	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	m_menubar->Append( m_menuFile, _("File") );

	this->SetMenuBar( m_menubar );

	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_mainSizer = new wxGridBagSizer( 0, 0 );
	m_mainSizer->SetFlexibleDirection( wxBOTH );
	m_mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow->SetScrollRate( 5, 5 );
	wxGridBagSizer* m_ScrolledWindowSizer;
	m_ScrolledWindowSizer = new wxGridBagSizer( 0, 0 );
	m_ScrolledWindowSizer->SetFlexibleDirection( wxBOTH );
	m_ScrolledWindowSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxGridBagSizer* m_barProcessSizer;
	m_barProcessSizer = new wxGridBagSizer( 0, 0 );
	m_barProcessSizer->SetFlexibleDirection( wxBOTH );
	m_barProcessSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblHeaderText = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Enter Item's dimensions below, one side for each Ln value. Enter the values in meters. Example: 600mm is 0.6\nA starter bar would be something like: L1: 1.0, L2: 0.2\nIf you want to calculate circular shaped bar fabrication, click the checkbox to switch to circular input mode."), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblHeaderText->Wrap( -1 );
	m_barProcessSizer->Add( m_lblHeaderText, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_chbCircularInput = new wxCheckBox( m_scrolledWindow, wxID_ANY, _("Circular Item Input"), wxDefaultPosition, wxDefaultSize, 0 );
	m_barProcessSizer->Add( m_chbCircularInput, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );

	m_gridLValues = new wxGrid( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridLValues->CreateGrid( 1, 10 );
	m_gridLValues->EnableEditing( true );
	m_gridLValues->EnableGridLines( true );
	m_gridLValues->SetGridLineColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTION ) );
	m_gridLValues->EnableDragGridSize( true );
	m_gridLValues->SetMargins( 1, 5 );

	// Columns
	m_gridLValues->EnableDragColMove( false );
	m_gridLValues->EnableDragColSize( true );
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
	m_gridLValues->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridLValues->SetRowSize( 0, 563 );
	m_gridLValues->AutoSizeRows();
	m_gridLValues->EnableDragRowSize( true );
	m_gridLValues->SetRowLabelValue( 0, _("Value") );
	m_gridLValues->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridLValues->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_barProcessSizer->Add( m_gridLValues, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_gridCircularLValues = new wxGrid( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridCircularLValues->CreateGrid( 1, 2 );
	m_gridCircularLValues->EnableEditing( true );
	m_gridCircularLValues->EnableGridLines( true );
	m_gridCircularLValues->EnableDragGridSize( false );
	m_gridCircularLValues->SetMargins( 0, 0 );

	// Columns
	m_gridCircularLValues->EnableDragColMove( false );
	m_gridCircularLValues->EnableDragColSize( true );
	m_gridCircularLValues->SetColLabelValue( 0, _("Diameter") );
	m_gridCircularLValues->SetColLabelValue( 1, _("Lap") );
	m_gridCircularLValues->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridCircularLValues->EnableDragRowSize( true );
	m_gridCircularLValues->SetRowLabelValue( 0, _("Value") );
	m_gridCircularLValues->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridCircularLValues->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_gridCircularLValues->Hide();

	m_barProcessSizer->Add( m_gridCircularLValues, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );

	wxGridBagSizer* m_InputSizer;
	m_InputSizer = new wxGridBagSizer( 0, 0 );
	m_InputSizer->SetFlexibleDirection( wxBOTH );
	m_InputSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblInputSizerHeader = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblInputSizerHeader->Wrap( -1 );
	m_InputSizer->Add( m_lblInputSizerHeader, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBarGrade = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Grade && Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBarGrade->Wrap( -1 );
	m_InputSizer->Add( m_lblBarGrade, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_specsGandDChoices[] = { _("N10"), _("N12"), _("N16"), _("N20"), _("N24"), _("N28"), _("N32"), _("N36"), _("N40"), _("R6.5"), _("R10"), _("R12"), _("R16"), _("R20"), _("R24"), _("S12"), _("SS12"), _("SS16") };
	int m_specsGandDNChoices = sizeof( m_specsGandDChoices ) / sizeof( wxString );
	m_specsGandD = new wxChoice( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_specsGandDNChoices, m_specsGandDChoices, 0 );
	m_specsGandD->SetSelection( 1 );
	m_InputSizer->Add( m_specsGandD, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_LEFT|wxALL, 5 );


	m_InputSizer->AddGrowableCol( 0 );
	m_InputSizer->AddGrowableCol( 1 );

	m_barProcessSizer->Add( m_InputSizer, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	wxGridBagSizer* m_CalculatedSizer;
	m_CalculatedSizer = new wxGridBagSizer( 0, 0 );
	m_CalculatedSizer->SetFlexibleDirection( wxBOTH );
	m_CalculatedSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblCalculatedHeader = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Auto Calculated Values"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedHeader->SetLabelMarkup( _("Auto Calculated Values") );
	m_lblCalculatedHeader->Wrap( -1 );
	m_lblCalculatedHeader->SetBackgroundColour( wxColour( 240, 242, 149 ) );

	m_CalculatedSizer->Add( m_lblCalculatedHeader, wxGBPosition( 0, 0 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblCalculatedTotalBarLength = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total bar length: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedTotalBarLength->Wrap( 200 );
	m_CalculatedSizer->Add( m_lblCalculatedTotalBarLength, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_lblCalculatedBarArea = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar area: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedBarArea->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedBarArea, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_lblCalculatedProcessingType = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Processing type: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedProcessingType->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedProcessingType, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_lblCalculatedCostPerMg = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Cost per Mg: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedCostPerMg->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedCostPerMg, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_lblWeightPerBar = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Weight: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblWeightPerBar->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblWeightPerBar, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );


	m_barProcessSizer->Add( m_CalculatedSizer, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );


	m_barProcessSizer->AddGrowableCol( 0 );
	m_barProcessSizer->AddGrowableCol( 1 );
	m_barProcessSizer->AddGrowableCol( 2 );

	m_ScrolledWindowSizer->Add( m_barProcessSizer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5 );

	m_staticline1 = new wxStaticLine( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_ScrolledWindowSizer->Add( m_staticline1, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );

	wxGridBagSizer* m_barCalculatorSizer;
	m_barCalculatorSizer = new wxGridBagSizer( 0, 0 );
	m_barCalculatorSizer->SetFlexibleDirection( wxBOTH );
	m_barCalculatorSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblBarCalculator = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Quantity Calculator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBarCalculator->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBarCalculator, wxGBPosition( 0, 0 ), wxGBSpan( 1, 5 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCArea = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Area"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCArea->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCArea, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCBar = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCBar->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCBar, wxGBPosition( 1, 3 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCLength = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCLength->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCLength, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCWidth = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCWidth->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCWidth, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCBarCentre = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Centre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCBarCentre->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCBarCentre, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCBarSpans = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Centres span the..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCBarSpans->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCBarSpans, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBCTotalQty = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total Quantity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBCTotalQty->Wrap( -1 );
	m_barCalculatorSizer->Add( m_lblBCTotalQty, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_BCLength = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_barCalculatorSizer->Add( m_BCLength, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_BCWidth = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_barCalculatorSizer->Add( m_BCWidth, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_BCBarCentre = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_barCalculatorSizer->Add( m_BCBarCentre, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	wxString m_BCBarSpansChoices[] = { _("Length"), _("Width") };
	int m_BCBarSpansNChoices = sizeof( m_BCBarSpansChoices ) / sizeof( wxString );
	m_BCBarSpans = new wxChoice( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_BCBarSpansNChoices, m_BCBarSpansChoices, 0 );
	m_BCBarSpans->SetSelection( 0 );
	m_barCalculatorSizer->Add( m_BCBarSpans, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_BCTotalQty = new wxStaticText( m_scrolledWindow, wxID_ANY, _("0 bars"), wxDefaultPosition, wxDefaultSize, 0 );
	m_BCTotalQty->Wrap( -1 );
	m_barCalculatorSizer->Add( m_BCTotalQty, wxGBPosition( 3, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );


	m_barCalculatorSizer->AddGrowableCol( 0 );
	m_barCalculatorSizer->AddGrowableCol( 1 );
	m_barCalculatorSizer->AddGrowableCol( 2 );
	m_barCalculatorSizer->AddGrowableCol( 3 );
	m_barCalculatorSizer->AddGrowableCol( 4 );

	m_ScrolledWindowSizer->Add( m_barCalculatorSizer, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxEXPAND|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5 );

	m_staticline2 = new wxStaticLine( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_ScrolledWindowSizer->Add( m_staticline2, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );

	wxGridBagSizer* m_tieCalculatorSizer;
	m_tieCalculatorSizer = new wxGridBagSizer( 0, 0 );
	m_tieCalculatorSizer->SetFlexibleDirection( wxBOTH );
	m_tieCalculatorSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblTiesCalculator = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Ties Based on Lineal m of Bar"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesCalculator->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesCalculator, wxGBPosition( 0, 0 ), wxGBSpan( 1, 7 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesArea = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Area"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesArea->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesArea, wxGBPosition( 1, 0 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesBarLength = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesBarLength->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesBarLength, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesSpanDistance = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Span Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesSpanDistance->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesSpanDistance, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesBarCentre = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Centre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesBarCentre->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesBarCentre, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesTieCentre = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Ties at every x centre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesTieCentre->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesTieCentre, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesTotalQtyBars = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total Quantity of Bars"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesTotalQtyBars->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesTotalQtyBars, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesTotalLinealBar = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total Lineal of Bar"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesTotalLinealBar->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesTotalLinealBar, wxGBPosition( 2, 5 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblTiesTotalQtyTies = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total Quantity of Ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTiesTotalQtyTies->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_lblTiesTotalQtyTies, wxGBPosition( 2, 6 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_TiesBarLength = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_tieCalculatorSizer->Add( m_TiesBarLength, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_TiesSpanDistance = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_tieCalculatorSizer->Add( m_TiesSpanDistance, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_TiesBarCentre = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_tieCalculatorSizer->Add( m_TiesBarCentre, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_TiesTieCentre = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_tieCalculatorSizer->Add( m_TiesTieCentre, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_TiesTotalQtyBars = new wxStaticText( m_scrolledWindow, wxID_ANY, _("0 bars"), wxDefaultPosition, wxDefaultSize, 0 );
	m_TiesTotalQtyBars->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_TiesTotalQtyBars, wxGBPosition( 3, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_TiesTotalLinealBar = new wxStaticText( m_scrolledWindow, wxID_ANY, _("0 lin. m"), wxDefaultPosition, wxDefaultSize, 0 );
	m_TiesTotalLinealBar->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_TiesTotalLinealBar, wxGBPosition( 3, 5 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_TiesTotalQtyTies = new wxStaticText( m_scrolledWindow, wxID_ANY, _("0 bars"), wxDefaultPosition, wxDefaultSize, 0 );
	m_TiesTotalQtyTies->Wrap( -1 );
	m_tieCalculatorSizer->Add( m_TiesTotalQtyTies, wxGBPosition( 3, 6 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );


	m_tieCalculatorSizer->AddGrowableCol( 0 );
	m_tieCalculatorSizer->AddGrowableCol( 1 );
	m_tieCalculatorSizer->AddGrowableCol( 2 );
	m_tieCalculatorSizer->AddGrowableCol( 3 );
	m_tieCalculatorSizer->AddGrowableCol( 4 );

	m_ScrolledWindowSizer->Add( m_tieCalculatorSizer, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxEXPAND|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5 );

	m_staticline3 = new wxStaticLine( m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_ScrolledWindowSizer->Add( m_staticline3, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );

	wxGridBagSizer* m_labourCalculatorSizer;
	m_labourCalculatorSizer = new wxGridBagSizer( 0, 0 );
	m_labourCalculatorSizer->SetFlexibleDirection( wxBOTH );
	m_labourCalculatorSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_lblLabourCalculator = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Steelfixing Labour Based on Area"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourCalculator->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourCalculator, wxGBPosition( 0, 0 ), wxGBSpan( 1, 5 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourArea = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Area (m2)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourArea->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourArea, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourBarCentreA = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Centre A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourBarCentreA->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourBarCentreA, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourBarCentreB = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Bar Centre B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourBarCentreB->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourBarCentreB, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourTieCentre = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Ties at every x centre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourTieCentre->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourTieCentre, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblLabourTotalQtyTies = new wxStaticText( m_scrolledWindow, wxID_ANY, _("Total Quantity of Ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLabourTotalQtyTies->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_lblLabourTotalQtyTies, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_LabourArea = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourArea, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_LabourBarCentreA = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourBarCentreA, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_LabourBarCentreB = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourBarCentreB, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_LabourTieCentre = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_labourCalculatorSizer->Add( m_LabourTieCentre, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_LabourTotalQtyTies = new wxStaticText( m_scrolledWindow, wxID_ANY, _("0 ties"), wxDefaultPosition, wxDefaultSize, 0 );
	m_LabourTotalQtyTies->Wrap( -1 );
	m_labourCalculatorSizer->Add( m_LabourTotalQtyTies, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );


	m_labourCalculatorSizer->AddGrowableCol( 0 );
	m_labourCalculatorSizer->AddGrowableCol( 1 );
	m_labourCalculatorSizer->AddGrowableCol( 2 );
	m_labourCalculatorSizer->AddGrowableCol( 3 );
	m_labourCalculatorSizer->AddGrowableCol( 4 );

	m_ScrolledWindowSizer->Add( m_labourCalculatorSizer, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxEXPAND|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5 );


	m_scrolledWindow->SetSizer( m_ScrolledWindowSizer );
	m_scrolledWindow->Layout();
	m_ScrolledWindowSizer->Fit( m_scrolledWindow );
	m_mainSizer->Add( m_scrolledWindow, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );


	m_mainSizer->AddGrowableCol( 0 );
	m_mainSizer->AddGrowableRow( 0 );

	this->SetSizer( m_mainSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

Main::~Main()
{
}
