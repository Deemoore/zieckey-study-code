/****************************************************************************
** Form implementation generated from reading ui file 'cfinddialog.ui'
**
** Created by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "cfinddialog.h"

#include <qvariant.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a CFindDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CFindDialog::CFindDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "CFindDialog" );

    lineEdit1 = new QLineEdit( this, "lineEdit1" );
    lineEdit1->setGeometry( QRect( 120, 60, 121, 21 ) );

    okPpushButton = new QPushButton( this, "okPpushButton" );
    okPpushButton->setGeometry( QRect( 180, 210, 85, 30 ) );

    findPushButton = new QPushButton( this, "findPushButton" );
    findPushButton->setGeometry( QRect( 280, 60, 85, 30 ) );
    languageChange();
    resize( QSize(499, 323).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
CFindDialog::~CFindDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CFindDialog::languageChange()
{
    setCaption( tr( "Form2" ) );
    okPpushButton->setText( tr( "OK" ) );
    findPushButton->setText( tr( "Find" ) );
}

