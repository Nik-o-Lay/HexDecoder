#include "Window.h"
#include "ui_Window.h"

#include "FormDrofa.h"
#include "FormKorshun.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    m_firstForm = new FormDrofa(this);
    m_secondForm = new FormKorshun(this);

    ui->gridLayout->addWidget(m_firstForm);
    ui->gridLayout->addWidget(m_secondForm);
}

Window::~Window()
{
    delete ui;
}
