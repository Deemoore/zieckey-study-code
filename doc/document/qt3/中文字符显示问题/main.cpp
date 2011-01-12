#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtextcodec.h>
#include <qapplication.h>
#include <qpushbutton.h>

int main( int argc, char **argv )
{   
 /*
	QFile file("test.txt");
 	if (file.open(IO_ReadOnly|IO_Raw))
 	{
  		QTextStream floStream(&file);
  		QString line;
  		QTextCodec *codec=QTextCodec::codecForName("GBK");
  		floStream.setCodec(codec); 
  		while ( floStream.atEnd()==0 )
  		{
   			line = codec->fromUnicode(floStream.readLine());
   			qWarning(line);
  		}
  		file.close();     
 	} 
 */

	
 	QApplication a( argc, argv );

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
   	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
   	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

	char* ch = "你好！北京！";
	QString str = str.fromUtf8(ch);
	
   	QPushButton hello( str, 0 );
   	hello.resize( 100, 30 );

	
   	a.setMainWidget( &hello );
   	hello.show();
   	return a.exec();
}
