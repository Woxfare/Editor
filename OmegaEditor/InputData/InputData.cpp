#include "InputData.h"
#include "QOmgStyle.h"

#include "OmgEntities/OmgEntity.h"

#include <QListWidgetItem>
#include <QListWidget>
#include <QList>

InputData::InputData( QWidget *parent ) : QDialog( parent )
{
  setStyleSheet(QOmgStyle::CurrentStyleSheet());
}

void
InputData::FinishInputData()
{
  hide();
  emit hideInputData();
  deleteLater();
}

QListWidgetItem*
InputData::getListItem(QString aName, QListWidget* listWidget )
{
    QList<QListWidgetItem*> vItems = listWidget->findItems( aName, Qt::MatchCaseSensitive );

    if(vItems.isEmpty())
      return NULL;

    return vItems.first();
}

void
InputData::FillListWidget( Omega::EntityVector vectorEntities, QListWidget* listWidget )
{
  listWidget->clear();
  Omega::EntityIterator it = vectorEntities.begin(), itEnd = vectorEntities.end();
  for(; it != itEnd ; ++it)
  {
    OmgEntity* entity = *it;
    if(entity)
      listWidget->addItem(new QListWidgetItem(QIcon( entity->getPixmap() ), entity->getName()));
  }
}