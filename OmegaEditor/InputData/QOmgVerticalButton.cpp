#include "QOmgVerticalButton.h"
#include <QStylePainter>
#include <QMenu>

QOmgVerticalButton::QOmgVerticalButton(QWidget* parent)
: QPushButton(parent)
{
    Init();
}

QOmgVerticalButton::QOmgVerticalButton(const QString& text, QWidget* parent)
: QPushButton(text, parent)
{
    Init();
}

QOmgVerticalButton::QOmgVerticalButton(const QIcon& icon, const QString& text, QWidget* parent)
: QPushButton(icon, text, parent)
{
    Init();
}

QOmgVerticalButton::~QOmgVerticalButton()
{
}

void QOmgVerticalButton::Init()
{
    _orientation = Qt::Horizontal;
    _mirrored = false;
}

Qt::Orientation QOmgVerticalButton::GetOrientation() const
{
    return _orientation;
}

void QOmgVerticalButton::SetOrientation(Qt::Orientation a_orientation)
{
    _orientation = a_orientation;
    switch (_orientation)
    {
    case Qt::Horizontal:
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        break;

    case Qt::Vertical:
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        break;
    }
}

bool QOmgVerticalButton::IsMirrored() const
{
    return _mirrored;
}

void QOmgVerticalButton::SetMirrored(bool a_mirrored)
{
    _mirrored = a_mirrored;
}

QSize QOmgVerticalButton::sizeHint() const
{
    QSize size = QPushButton::sizeHint();
    if (_orientation == Qt::Vertical)
        size.transpose();
    return size;
}

void QOmgVerticalButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStylePainter p(this);

    switch (_orientation)
    {
    case Qt::Horizontal:
        if (_mirrored)
        {
            p.rotate(180);
            p.translate(-width(), -height());
        }
        break;

    case Qt::Vertical:
        if (_mirrored)
        {
            p.rotate(-90);
            p.translate(-height(), 0);
        }
        else
        {
            p.rotate(90);
            p.translate(0, -width());
        }
        break;
    }

    p.drawControl(QStyle::CE_PushButton, GetStyleOption());
}

QStyleOptionButton QOmgVerticalButton::GetStyleOption() const
{
    QStyleOptionButton opt;
    opt.initFrom(this);
    if (_orientation == Qt::Vertical)
    {
        QSize size = opt.rect.size();
        size.transpose();
        opt.rect.setSize(size);
    }
    opt.features = QStyleOptionButton::None;
    if (isFlat())
        opt.features |= QStyleOptionButton::Flat;
    if (menu())
        opt.features |= QStyleOptionButton::HasMenu;
    if (autoDefault() || isDefault())
        opt.features |= QStyleOptionButton::AutoDefaultButton;
    if (isDefault())
        opt.features |= QStyleOptionButton::DefaultButton;
    if (isDown() || (menu() && menu()->isVisible()))
        opt.state |= QStyle::State_Sunken;
    if (isChecked())
        opt.state |= QStyle::State_On;
    if (!isFlat() && !isDown())
        opt.state |= QStyle::State_Raised;
    opt.text = text();
    opt.icon = icon();
    opt.iconSize = iconSize();
    return opt;
}
