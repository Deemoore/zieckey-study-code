/****************************************************************************
** Form interface generated from reading ui file 'cfinddialog.ui'
**
** Created by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CFINDDIALOG_H
#define CFINDDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QPushButton;

class CFindDialog : public QDialog
{
    Q_OBJECT

public:
    CFindDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~CFindDialog();

    QLineEdit* lineEdit1;
    QPushButton* okPpushButton;
    QPushButton* findPushButton;

protected:

protected slots:
    virtual void languageChange();

};

#endif // CFINDDIALOG_H
