#include "FormKorshun.h"
#include "ui_FormKorshun.h"
#include <QRegularExpression>

FormKorshun::FormKorshun(QWidget *parent) :
    Decoder(parent),
    ui(new Ui::FormKorshun),
    m_msgProtocolKorshun{
        R"(^)"
        R"((?:(?:0x|0X)?(?:3A|3a)[[:space:]]))" // "3A " lower- or uppercase with optional 0x or 0X prefix
        R"((?:(?:0x|0X)?(?:[[:xdigit:]]{2})[[:space:]]){1,10})" // 1 to 10 "hex " with optional 0x or 0X prefix
        R"((?:(?:0x|0X)?(?:21)))" // "21" lower- or uppercase with optional 0x or 0X prefix
        R"($)"
                      },
    m_msgKorshun{},  m_intByteStateKorshun{}, m_byteArrayKorshun{}
{
    ui->setupUi(this);
    ui->tableWidgetKorshun ->setStyleSheet("QTableView{border : 1px solid black}");
    connect(ui->pushButtonKorshun, &QPushButton::clicked, this, &FormKorshun::Decode);
}

FormKorshun::~FormKorshun()
{
    delete ui;
}

bool FormKorshun::MatchCodeF()
{        
            if((m_intByteStateKorshun >= 100) && (m_intByteStateKorshun <= 5000) && (m_intByteStateKorshun % 10))
            {
                return true;
            } else
            {
                return false;
            }
}

bool FormKorshun::MatchCodeS()
{
    if((m_intByteStateKorshun >= 1) && (m_intByteStateKorshun <= 3 )) // S|s
        return true;
    else
        return false;
}

bool FormKorshun::MatchCodeC()
{
    if((m_intByteStateKorshun >= 1) && (m_intByteStateKorshun <= 16)) // C|c
        return true;
    else
        return false;
}

void FormKorshun::SetF()
{
    if(m_intByteStateKorshun < 1000)
    {
        ui->tableWidgetKorshun->item(0,0)->setText("0" + QString::number(m_intByteStateKorshun));
    } else
        ui->tableWidgetKorshun->item(0,0)->setText(QString::number(m_intByteStateKorshun));
}

void FormKorshun::SetS()
{
    if(m_intByteStateKorshun == 1)
    ui->tableWidgetKorshun->item(0,1)->setText("1");
    if(m_intByteStateKorshun == 2)
    ui->tableWidgetKorshun->item(0,1)->setText("2");
    if(m_intByteStateKorshun == 3)
    ui->tableWidgetKorshun->item(0,1)->setText("3");
}

void FormKorshun::SetC()
{
    if(m_intByteStateKorshun < 10)
    ui->tableWidgetKorshun->item(0, 2)->setText("0" + QString::number(m_intByteStateKorshun));
    else
    ui->tableWidgetKorshun->item(0, 2)->setText(QString::number(m_intByteStateKorshun));
}

void FormKorshun::Getline()
{
    m_msgKorshun = {ui->lineEditKorshun->text()};
}

void FormKorshun::SetDataForCodes()
{
    bool ok{};
    int pos{};
    // Convert 4 bytes after code F to int
    if( ((pos = m_byteArrayKorshun.indexOf("F")) > 0) && (pos + 4 < m_byteArrayKorshun.size()))
    {
     m_intByteStateKorshun = m_byteArrayKorshun.sliced(pos + 1, 4).toUInt(&ok, 16);
     if(MatchCodeF())
     SetF();
     else InvalidInput(pos);
    } else InvalidFormat();
    // Convert 1 bytes after code S to int
        if( ((pos = m_byteArrayKorshun.indexOf("S")) > 0) && (pos + 1 < m_byteArrayKorshun.size()))
        {
         m_intByteStateKorshun = m_byteArrayKorshun.sliced(pos + 1, 1).toUInt(&ok, 16);
         if(MatchCodeS())
         SetS();
         else InvalidInput(pos);
        }  else InvalidFormat();
        // Convert 2 bytes after code C to int
            if( ((pos = m_byteArrayKorshun.indexOf("C")) > 0) && (pos + 2 < m_byteArrayKorshun.size()))
            {
              m_intByteStateKorshun = m_byteArrayKorshun.sliced(pos + 1, 2).toUInt(&ok, 16);
              if(MatchCodeC())
              SetC();
              else InvalidInput(pos);
            } else InvalidFormat();
}
void FormKorshun::OutputResult()
{
    for(int i = 0; i < 3; ++i) // clear table
    {
        ui->tableWidgetKorshun->item(0,i)->setText("");
    }
    SetDataForCodes();
}

void FormKorshun::Decode()
{
    Getline();
    if(CheckFormat(m_msgKorshun, m_msgProtocolKorshun))
    {
    m_byteArrayKorshun = {FillHexByteArray(m_msgKorshun)};
    OutputResult();
    } else InvalidFormat();
}

