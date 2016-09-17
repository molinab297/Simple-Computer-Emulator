#ifndef SPINBOX_H
#define SPINBOX_H
#include <QSpinBox>

// Modified version of QSpinBox to allow display of leading zeros
class SpinBox : public QSpinBox
{
    Q_OBJECT

public:
    SpinBox( QWidget * parent ) : QSpinBox( parent ) {}

protected:
    virtual QString textFromValue(int value) const
    {
           return QString("%1").arg(value, 3, 10, QLatin1Char('0'));
    }

};
#endif // SPINBOX_H

