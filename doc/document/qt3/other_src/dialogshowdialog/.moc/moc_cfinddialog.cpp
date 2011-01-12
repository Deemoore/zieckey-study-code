/****************************************************************************
** CFindDialog meta object code from reading C++ file 'cfinddialog.h'
**
** Created: Mon Sep 24 11:57:53 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../.ui/cfinddialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CFindDialog::className() const
{
    return "CFindDialog";
}

QMetaObject *CFindDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CFindDialog( "CFindDialog", &CFindDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CFindDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CFindDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CFindDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CFindDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CFindDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "str", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setMsg", 1, param_slot_0 };
    static const QUMethod slot_1 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "setMsg(const QString&)", &slot_0, QMetaData::Public },
	{ "languageChange()", &slot_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"CFindDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CFindDialog.setMetaObject( metaObj );
    return metaObj;
}

void* CFindDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CFindDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool CFindDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setMsg((const QString&)static_QUType_QString.get(_o+1)); break;
    case 1: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CFindDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool CFindDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool CFindDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
