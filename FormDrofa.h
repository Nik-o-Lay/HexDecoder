#ifndef FORMDROFA_H
#define FORMDROFA_H

#include "Decoder.h"

namespace Ui {
class FormDrofa;
}

class FormDrofa : public Decoder
{
    Q_OBJECT

public:
    explicit FormDrofa(QWidget *parent = nullptr);
    ~FormDrofa();

    void MakeTable();

    bool FirstF();

    bool FirstM();

    bool FirstP();

    bool isF(int pos);

    bool isM(int pos);

    bool isP(int pos);

    void SetF();

    void SetM();

    void SetP();

    void Getline() override ;

    void OutputResult() override;

    void Decode() override;



private:
    Ui::FormDrofa *ui;
    uint m_intByteStateDrofa;
    QRegularExpression m_msgProtocolDrofa;
    QString m_msgDrofa;
    QByteArray m_byteArrayDrofa;

};

#endif // FORMDROFA_H
