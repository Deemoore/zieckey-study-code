/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
void CMainDialog::init()
{	
    cfd = new CFindDialog(0,0,true);
    //connect(this,SIGNAL(clicked()),this,SIGNAL(myclick(teather))))
    //connect( msgLineEdit, SIGNAL(textChanged( const QSting &)), cfd, SLOT(setMsg(const QString &) ) );
}

void CMainDialog::showFindDialogSlot()
{
    
    //emit sendText(msgLineEdit->text());
    cfd->show();
}


void CMainDialog::setCFDMsgSlot( const QString &s )
{
    cfd->msgTextLabel->setText(s);
}
