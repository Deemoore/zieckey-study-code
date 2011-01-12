/****************************************************************************
** Form interface generated from reading ui file 'cmainwidget.ui'
**
** Created by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CMAINWIDGET_H
#define CMAINWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include "cfinddialog.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;

class CMainWidget : public QWidget
{
    Q_OBJECT

public:
    CMainWidget( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~CMainWidget();

    QPushButton* showPushButton;

public slots:
    virtual void showFindDialogSlot();

protected:
    CFindDialog *cfd;


protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // CMAINWIDGET_H
