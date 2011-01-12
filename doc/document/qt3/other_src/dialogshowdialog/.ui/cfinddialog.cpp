/****************************************************************************
** Form implementation generated from reading ui file 'cfinddialog.ui'
**
** Created by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "cfinddialog.h"

#include <qvariant.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "../cfinddialog.ui.h"
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

    checkBox1 = new QCheckBox( this, "checkBox1" );
    checkBox1->setGeometry( QRect( 30, 50, 87, 20 ) );

    getMsgPushButton = new QPushButton( this, "getMsgPushButton" );
    getMsgPushButton->setGeometry( QRect( 10, 100, 120, 30 ) );

    msgTextLabel = new QLabel( this, "msgTextLabel" );
    msgTextLabel->setGeometry( QRect( 150, 100, 120, 30 ) );
    languageChange();
    resize( QSize(314, 168).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
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
    checkBox1->setText( tr( "checkBox1" ) );
    getMsgPushButton->setText( tr( "Get Message" ) );
    msgTextLabel->setText( tr( "textLabel1" ) );
}

