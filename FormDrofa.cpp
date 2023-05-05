#include "FormDrofa.h"
#include "ui_FormDrofa.h"
#include <QRegularExpression>


FormDrofa::FormDrofa(QWidget *parent) :
    Decoder(parent),
    ui(new Ui::FormDrofa),
    m_msgProtocolDrofa{
        R"(^)"
        R"((?:(?:0x|0X)?(?:FF|ff)[[:space:]]){2})" // "FF FF " lower or uppercase with optional 0x or 0X prefix
        R"((?:(?:0x|0X)?(?:[[:xdigit:]]{2})[[:space:]]){1,4})" // 1 to 4 "hex " with optional 0x or 0X prefix
        R"((?:(?:0x|0X)?(?:EF|ef)[[:space:]](?:0x|0X)?(?:EF|ef)))" // "EF EF" lower or uppercase with optional 0x or 0X prefix
        R"($)"
                      },
    m_msgDrofa{},  m_intByteStateDrofa{}, m_byteArrayDrofa{}

{
    ui->setupUi(this);
    ui->tableWidgetDrofa->setStyleSheet("QTableView{border : 1px solid black}");
    connect(ui->pushButtonDrofa, &QPushButton::clicked, this, &FormDrofa::Decode);
}

FormDrofa::~FormDrofa()
{
    delete ui;
}

bool FormDrofa::FirstF()
{
    if(isF(2)) // F is the first, the sequence is: F|FM|FMP
    {
        if(m_byteArrayDrofa.size() == 6)
            SetF();
        else
            if(m_byteArrayDrofa.size() == 7)
            {
                SetF();
                if(isM(4))
                    SetM();
                else InvalidInput(4);
            } else
                if(m_byteArrayDrofa.size() == 8)
                {
                    SetF();
                    if(isM(4))
                        SetM();
                    else InvalidInput(4);
                    if(isP(5))
                        SetP();
                    else InvalidInput(5);
                }
        return true;
    } else return false;
}

bool FormDrofa::FirstM()
{
    if(isM(2)) // M is the first, the sequence is M|MP
    {
        if(m_byteArrayDrofa.size() == 5)
        {
            SetM();
        } else
            if(m_byteArrayDrofa.size() == 6)
            {
                SetM();
                if(isP(3))
                {
                    SetP();
                } else InvalidInput(3);
            }
        return true;
    } else return false;
}

bool FormDrofa::FirstP()
{
        if(isP(2)) // P is the only byte for device state
        {
            SetP();
            return true;
        }
        else
        {
            return false;
        }
}

bool FormDrofa::isF(int pos)
{
    bool ok;
    m_intByteStateDrofa = m_byteArrayDrofa.sliced(pos,2).toHex().toUInt(&ok, 16);
    if(ok)
    {
        if((m_intByteStateDrofa >= 5000) && (m_intByteStateDrofa <= 50000) && (m_byteArrayDrofa.size() != 5))
        {
            return true;
        } else
        {
            return false;
        }
    } else
    {
        ConversionError(pos);
        return false;
    }
}

bool FormDrofa::isM(int pos)
{
    bool ok;
    m_intByteStateDrofa = m_byteArrayDrofa.sliced(pos,1).toHex().toUInt(&ok, 16);
    if(ok)
    {
        if(m_intByteStateDrofa == 1 || m_intByteStateDrofa == 2 || m_intByteStateDrofa ==10)
        {
            return true;
        } else
        {
            return false;
        }
    } else
    {
        ConversionError(pos);
        return false;
    }
}

bool FormDrofa::isP(int pos)
{
    bool ok;
    m_intByteStateDrofa = m_byteArrayDrofa.sliced(pos,1).toHex().toUInt(&ok, 16);
    if(ok)
    {
        if((m_intByteStateDrofa % 10 == 0) && (m_intByteStateDrofa >= 0) && (m_intByteStateDrofa <= 100))
        {
            return true;
        } else
        {
            return false;
        }
    } else
    {
        ConversionError((pos));
        return false;
    }
}

void FormDrofa::SetF()
{
    ui->tableWidgetDrofa->item(0,0)->setText(QString::number(m_intByteStateDrofa));
}

void FormDrofa::SetM()
{
    if(m_intByteStateDrofa == 1)
    ui->tableWidgetDrofa->item(0,1)->setText("A1");
    if(m_intByteStateDrofa == 2)
    ui->tableWidgetDrofa->item(0,1)->setText("A2");
    if(m_intByteStateDrofa == 10)
    ui->tableWidgetDrofa->item(0,1)->setText("F5R");
}

void FormDrofa::SetP()
{
    ui->tableWidgetDrofa->item(0,2)->setText(QString::number(m_intByteStateDrofa));
}

void FormDrofa::Getline()
{
    m_msgDrofa = {ui->lineEditDrofa->text()};
}

void FormDrofa::OutputResult()
{
    for(int i = 0; i < 3; ++i) // clear table
    {
        ui->tableWidgetDrofa->item(0,i)->setText("");
    }
    // Fill table based on the first byte
    // if the first byte in message is malformed - output error
    if(!FirstF())
        if(!FirstM())
            if(!FirstP())
                InvalidInput(2);
}

void FormDrofa::Decode()
{
    Getline();
    if(CheckFormat(m_msgDrofa, m_msgProtocolDrofa))
    {
        m_byteArrayDrofa = {FillHexByteArray(m_msgDrofa)};
        OutputResult();
    } else
        InvalidFormat();
}
