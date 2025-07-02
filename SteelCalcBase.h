///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class ResultSetGrid;

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/grid.h>
#include <wx/gbsizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/scrolwin.h>
#include <wx/frame.h>
#include <wx/sizer.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Main
///////////////////////////////////////////////////////////////////////////////
class Main : public wxFrame
{
	private:

	protected:
		enum
		{
			id_MENU_FILE_ABOUT = 6000,
			id_MENU_FILE_OPTIONS,
			id_MENU_FILE_DATABASEVIEWER,
			id_MENU_FILE_EXIT,
		};

		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxStatusBar* m_statusBar;
		wxGridBagSizer* m_mainSizer;
		wxScrolledWindow* m_scrolledWindow;
		wxGridBagSizer* m_ScrolledWindowSizer;
		wxGridBagSizer* m_barProcessSizer;
		wxStaticText* m_lblHeaderText;
		wxCheckBox* m_chbCircularInput;
		wxStaticText* m_lblBarGrade;
		wxChoice* m_specsGandD;
		wxGrid* m_gridLValues;
		wxGrid* m_gridCircularLValues;
		wxGridBagSizer* m_barCalculatorSizer;
		wxStaticText* m_lblBarCalculator;
		wxStaticText* m_lblBCSpan;
		wxStaticText* m_lblBCBarCentre;
		wxStaticText* m_lblBCTotalQty;
		wxTextCtrl* m_BCSpan;
		wxTextCtrl* m_BCBarCentre;
		wxStaticText* m_BCTotalQty;
		wxGridBagSizer* m_labourCalculatorSizer;
		wxStaticText* m_lblLabourCalculator;
		wxStaticText* m_lblLabourLength;
		wxStaticText* m_lblLabourWidth;
		wxStaticText* m_lblLabourBarCentreA;
		wxStaticText* m_lblLabourBarCentreB;
		wxStaticText* m_lblLabourTieCentre;
		wxStaticText* m_lblLabourTotalQtyTies;
		wxTextCtrl* m_LabourLength;
		wxTextCtrl* m_LabourWidth;
		wxTextCtrl* m_LabourBarCentreA;
		wxTextCtrl* m_LabourBarCentreB;
		wxTextCtrl* m_LabourTieCentre;
		wxStaticText* m_LabourTotalQtyTies;
		wxGridBagSizer* m_CalculatedSizer;
		wxStaticText* m_lblCalculatedHeader;
		wxStaticText* m_lblCalculatedProcessingType;
		wxStaticText* m_lblCalculatedTotalBarLength;
		wxStaticText* m_lblCalculatedBarArea;
		wxStaticText* m_lblCalculatedCostPerBar;
		wxStaticText* m_lblWeightPerBar;
		wxStaticText* m_lblWeightTotalMg;
		wxStaticText* m_lblCalculatedCostPerMg;
		wxButton* m_btnClearAll;

	public:

		Main( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Steel Calculator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 925,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Main();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Options
///////////////////////////////////////////////////////////////////////////////
class Options : public wxFrame
{
	private:

	protected:
		wxStaticText* m_lblOptionsLabour;
		wxCheckBox* m_optionsLabourAddPerimeterTies;
		wxCheckBox* m_optionsLabourAddSetupTies;
		wxCheckBox* m_optionsLabourAddLapTies;
		wxStaticText* m_lblOptionsCalculationFactors;
		wxStaticText* m_lblOptionsCFBarGradeCosts;
		ResultSetGrid* m_optionsCalculationFactorsBarGradeCosts;

	public:

		Options( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 266,414 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Options();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DatabaseViewer
///////////////////////////////////////////////////////////////////////////////
class DatabaseViewer : public wxFrame
{
	private:

	protected:
		enum
		{
			id_MENU_FILE_ABOUT = 6000,
			id_MENU_FILE_OPTIONS,
			id_MENU_FILE_EXIT,
		};

		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxStaticText* m_uiChoiceDBTablesLabel;
		wxChoice* m_uiChoicesDBTables;
		wxGrid* m_uiTableGrid;
		wxStatusBar* m_statusBar;

	public:

		DatabaseViewer( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Database Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 582,412 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~DatabaseViewer();

};

