/****************************************************************************
** CMainDialog meta object code from reading C++ file 'cmaindialog.h'
**
** Created: Mon Sep 24 11:57:53 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../.ui/cmaindialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CMainDialog::className() const
{
    return "CMainDialog";
}

QMetaObject *CMainDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CMainDialog( "CMainDialog", &CMainDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CMainDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CMainDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CMainDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CMainDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CMainDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"showFindDialogSlot", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_ptr, "QObject", QUParameter::In }
    };
    static const QUMethod slot_1 = {"CMainDialog_destroyed", 1, param_slot_1 };
    static const QUMethod slot_2 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "showFindDialogSlot()", &slot_0, QMetaData::Public },
	{ "CMainDialog_destroyed(QObject*)", &slot_1, QMetaData::Public },
	{ "languageChange()", &slot_2, QMetaData::Protected }
    };
    static const QUParameter param_signal_0[] = {
	{ "s", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"sendText", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "sendText(const QString&)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"CMainDialog", parentObject,
	slot_tbl, 3,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CMainDialog.setMetaObject( metaObj );
    return metaObj;
}

void* CMainDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CMainDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

// SIGNAL sendText
void CMainDialog::sendText( const QString& t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool CMainDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: showFindDialogSlot(); break;
    case 1: CMainDialog_destroyed((QObject*)static_QUType_ptr.get(_o+1)); break;
    case 2: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CMainDialog::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: sendText((const QString&)static_QUType_QString.get(_o+1)); break;
    default:
	return QDialog::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CMainDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool CMainDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
