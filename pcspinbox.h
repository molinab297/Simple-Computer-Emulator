#ifndef PCSPINBOX_H
#define PCSPINBOX_H

#include <QSpinBox>

// Modified version of QSpinBox to allow display of leading zeros
class pcspinbox : public QSpinBox
{
    Q_OBJECT

public:
    pcspinbox( QWidget * parent ) : QSpinBox( parent ) {}

protected:
    virtual QString textFromValue(int value) const
    {
        return QString("%1").arg(value, 2, 10, QLatin1Char('0'));
    }
};

#endif // PCSPINBOX_H

