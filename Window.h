#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class FormDrofa;
class FormKorshun;

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;
    FormDrofa *m_firstForm;
    FormKorshun *m_secondForm;
};

#endif // WINDOW_H
