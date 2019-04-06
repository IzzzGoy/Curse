#ifndef SELECTOR_H
#define SELECTOR_H

#include <QWidget>

namespace Ui {
class selector;
}

class selector : public QWidget
{
    Q_OBJECT

public:
    explicit selector(QWidget *parent = 0);
    ~selector();

private:
    Ui::selector *ui;
};

#endif // SELECTOR_H
