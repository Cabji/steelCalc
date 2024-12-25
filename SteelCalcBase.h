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
#include <wx/string.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/gbsizer.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/scrolwin.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Main
///////////////////////////////////////////////////////////////////////////////
class Main : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxStatusBar* m_statusBar;
		wxGridBagSizer* m_mainSizer;
		wxScrolledWindow* m_scrolledWindow;
		wxStaticText* m_lblHeaderText;
		wxCheckBox* m_chbCircularInput;
		wxGrid* m_gridLValues;
		wxGrid* m_gridCircularLValues;
		wxStaticText* m_lblInputSizerHeader;
		wxStaticText* m_lblBarGrade;
		wxChoice* m_specsGandD;
		wxStaticText* m_lblCalculatedHeader;
		wxStaticText* m_lblCalculatedTotalBarLength;
		wxStaticText* m_lblCalculatedBarArea;
		wxStaticText* m_lblCalculatedProcessingType;
		wxStaticText* m_lblCalculatedCostPerMg;
		wxStaticText* m_lblWeightPerBar;
		wxStaticLine* m_staticline1;
		wxStaticText* m_lblBarCalculator;
		wxStaticText* m_lblBCArea;
		wxStaticText* m_lblBCBar;
		wxStaticText* m_lblBCLength;
		wxStaticText* m_lblBCWidth;
		wxStaticText* m_lblBCBarCentre;
		wxStaticText* m_lblBCBarSpans;
		wxStaticText* m_lblBCTotalQty;
		wxTextCtrl* m_BCLength;
		wxTextCtrl* m_BCWidth;
		wxTextCtrl* m_BCBarCentre;
		wxChoice* m_BCBarSpans;
		wxStaticText* m_BCTotalQty;
		wxStaticLine* m_staticline2;
		wxStaticText* m_lblTiesCalculator;
		wxStaticText* m_lblTiesArea;
		wxStaticText* m_lblTiesBarLength;
		wxStaticText* m_lblTiesSpanDistance;
		wxStaticText* m_lblTiesBarCentre;
		wxStaticText* m_lblTiesTieCentre;
		wxStaticText* m_lblTiesTotalQtyBars;
		wxStaticText* m_lblTiesTotalLinealBar;
		wxStaticText* m_lblTiesTotalQtyTies;
		wxTextCtrl* m_TiesBarLength;
		wxTextCtrl* m_TiesSpanDistance;
		wxTextCtrl* m_TiesBarCentre;
		wxTextCtrl* m_TiesTieCentre;
		wxStaticText* m_TiesTotalQtyBars;
		wxStaticText* m_TiesTotalLinealBar;
		wxStaticText* m_TiesTotalQtyTies;
		wxStaticLine* m_staticline3;
		wxStaticText* m_lblLabourCalculator;
		wxStaticText* m_lblLabourArea;
		wxStaticText* m_lblLabourBarCentreA;
		wxStaticText* m_lblLabourBarCentreB;
		wxStaticText* m_lblLabourTieCentre;
		wxStaticText* m_lblLabourTotalQtyTies;
		wxTextCtrl* m_LabourArea;
		wxTextCtrl* m_LabourBarCentreA;
		wxTextCtrl* m_LabourBarCentreB;
		wxTextCtrl* m_LabourTieCentre;
		wxStaticText* m_LabourTotalQtyTies;

	public:

		Main( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Steel Calculator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 905,713 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Main();

};

