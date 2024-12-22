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
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar = new wxMenuBar( 0 );
	this->SetMenuBar( m_menubar );

	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	wxGridBagSizer* mainSizer;
	mainSizer = new wxGridBagSizer( 0, 0 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblHeaderText = new wxStaticText( this, wxID_ANY, _("Enter Item's dimensions below, one side for each Ln value. Enter the values in meters. Example: 600mm is 0.6\nA starter bar would be something like: L1: 1.0, L2: 0.2\nIf you want to calculate circular shaped bar fabrication, click the checkbox to switch to circular input mode."), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblHeaderText->Wrap( -1 );
	mainSizer->Add( m_lblHeaderText, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_chbCircularInput = new wxCheckBox( this, wxID_ANY, _("Circular Item Input"), wxDefaultPosition, wxDefaultSize, 0 );
	mainSizer->Add( m_chbCircularInput, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_gridLValues = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

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
	mainSizer->Add( m_gridLValues, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_gridCircularLValues = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

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

	mainSizer->Add( m_gridCircularLValues, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	wxGridBagSizer* m_InputSizer;
	m_InputSizer = new wxGridBagSizer( 0, 0 );
	m_InputSizer->SetFlexibleDirection( wxBOTH );
	m_InputSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblInputSizerHeader = new wxStaticText( this, wxID_ANY, _("Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblInputSizerHeader->Wrap( -1 );
	m_InputSizer->Add( m_lblInputSizerHeader, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblBarGrade = new wxStaticText( this, wxID_ANY, _("Bar Grade && Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBarGrade->Wrap( -1 );
	m_InputSizer->Add( m_lblBarGrade, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_specsGandDChoices[] = { _("N10"), _("N12"), _("N16"), _("N20"), _("N24"), _("N28"), _("N32"), _("N36"), _("N40"), _("R6.5"), _("R10"), _("R12"), _("R16"), _("R20"), _("R24"), _("S12"), _("SS12"), _("SS16") };
	int m_specsGandDNChoices = sizeof( m_specsGandDChoices ) / sizeof( wxString );
	m_specsGandD = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_specsGandDNChoices, m_specsGandDChoices, 0 );
	m_specsGandD->SetSelection( 0 );
	m_InputSizer->Add( m_specsGandD, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_LEFT|wxALL, 5 );


	mainSizer->Add( m_InputSizer, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxGridBagSizer* m_CalculatedSizer;
	m_CalculatedSizer = new wxGridBagSizer( 0, 0 );
	m_CalculatedSizer->SetFlexibleDirection( wxBOTH );
	m_CalculatedSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblCalculatedHeader = new wxStaticText( this, wxID_ANY, _("Auto Calculated Values"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedHeader->SetLabelMarkup( _("Auto Calculated Values") );
	m_lblCalculatedHeader->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedHeader, wxGBPosition( 0, 0 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_lblCalculatedTotalBarLength = new wxStaticText( this, wxID_ANY, _("Total bar length: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedTotalBarLength->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedTotalBarLength, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblCalculatedBarArea = new wxStaticText( this, wxID_ANY, _("Bar area: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedBarArea->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedBarArea, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblCalculatedProcessingType = new wxStaticText( this, wxID_ANY, _("Processing type: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedProcessingType->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedProcessingType, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblCalculatedCostPerMg = new wxStaticText( this, wxID_ANY, _("Cost per Mg: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCalculatedCostPerMg->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblCalculatedCostPerMg, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblWeightPerBar = new wxStaticText( this, wxID_ANY, _("Weight: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblWeightPerBar->Wrap( -1 );
	m_CalculatedSizer->Add( m_lblWeightPerBar, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );


	mainSizer->Add( m_CalculatedSizer, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

Main::~Main()
{
}
