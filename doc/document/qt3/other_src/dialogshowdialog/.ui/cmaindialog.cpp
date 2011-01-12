/****************************************************************************
** Form implementation generated from reading ui file 'cmaindialog.ui'
**
** Created by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "cmaindialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "../cmaindialog.ui.h"
/*
 *  Constructs a CMainDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CMainDialog::CMainDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "CMainDialog" );

    showPushButton = new QPushButton( this, "showPushButton" );
    showPushButton->setGeometry( QRect( 160, 130, 85, 30 ) );

    msgLineEdit = new QLineEdit( this, "msgLineEdit" );
    msgLineEdit->setGeometry( QRect( 280, 131, 121, 30 ) );
    languageChange();
    resize( QSize(600, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( showPushButton, SIGNAL( clicked() ), this, SLOT( showFindDialogSlot() ) );
    connect( msgLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( setCFDMsgSlot(const QString&) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMainDialog::~CMainDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CMainDialog::languageChange()
{
    setCaption( tr( "Form1" ) );
    showPushButton->setText( tr( "show" ) );
}

