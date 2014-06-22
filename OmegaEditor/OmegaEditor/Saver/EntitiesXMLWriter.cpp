#include "EntitiesXMLWriter.h"
#include <QXmlStreamWriter>
#include "OmgEntities/OmgEntity.h"
#include <QFile>
#include <QString>
#include <QTextStream>

EntitiesXMLWriter::EntitiesXMLWriter( const std::vector< OmgEntity* >& arv_entities, const QString a_fileName )
{
  if( a_fileName == "" )
    return;

  QFile file(a_fileName);
  if (!file.open( QIODevice::WriteOnly | QIODevice::Text ))
    return;

  QXmlStreamWriter *stream = new QXmlStreamWriter(); // The stream to save the xml file
  stream->setDevice(&file);

  stream->setAutoFormatting(true);
  stream->writeStartDocument();
  stream->writeStartElement("omega");

  int nEntities = arv_entities.size();
  for( int i = 0 ; i < nEntities ; ++i )
  {
    OmgEntity* pEntity = arv_entities[i];

    if(pEntity)
      pEntity->writeInfo( stream );
  }

  stream->writeEndElement();
  stream->writeEndDocument(); // Writes the end of the xml document
  file.close();
}