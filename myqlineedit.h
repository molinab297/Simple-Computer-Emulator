#ifndef MYQLINEEDIT
#define MYQLINEEDIT

#include <QLineEdit>

// Modified version of QSpinBox to allow display of leading zeros
class myqlineedit : public QLineEdit
{
    Q_OBJECT

public:
    myqlineedit( QWidget * parent ) : QLineEdit( parent ) {}

protected:
    virtual QString textFromValue(int value) const
    {
           return QString("%1").arg(value, 3, 10, QLatin1Char('0'));
    }

};

#endif // MYQLINEEDIT

