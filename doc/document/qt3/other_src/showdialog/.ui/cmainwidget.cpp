/****************************************************************************
** Form implementation generated from reading ui file 'cmainwidget.ui'
**
** Created by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "cmainwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "../cmainwidget.ui.h"
/*
 *  Constructs a CMainWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMainWidget::CMainWidget( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "CMainWidget" );

    showPushButton = new QPushButton( this, "showPushButton" );
    showPushButton->setGeometry( QRect( 140, 150, 85, 30 ) );
    languageChange();
    resize( QSize(600, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( showPushButton, SIGNAL( clicked() ), this, SLOT( showFindDialogSlot() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMainWidget::~CMainWidget()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CMainWidget::languageChange()
{
    setCaption( tr( "Form1" ) );
    showPushButton->setText( tr( "show" ) );
}

