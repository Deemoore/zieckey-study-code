/****************************************************************************
** Form interface generated from reading ui file 'cmaindialog.ui'
**
** Created by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CMAINDIALOG_H
#define CMAINDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "cfinddialog.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLineEdit;

class CMainDialog : public QDialog
{
    Q_OBJECT

public:
    CMainDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~CMainDialog();

    QPushButton* showPushButton;
    QLineEdit* msgLineEdit;

    CFindDialog *cfd;

public slots:
    virtual void showFindDialogSlot();
    virtual void setCFDMsgSlot( const QString & s );

signals:
    void sendText(const QString &s);

protected:

protected slots:
    virtual void languageChange();

private:
    int newa;

    void init();

};

#endif // CMAINDIALOG_H
