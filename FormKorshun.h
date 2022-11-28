#ifndef FORMKORSHUN_H
#define FORMKORSHUN_H

#include "Decoder.h"

namespace Ui {
class FormKorshun;
}

class FormKorshun : public Decoder
{
    Q_OBJECT

public:
    explicit FormKorshun(QWidget *parent = nullptr);
    ~FormKorshun();

    bool MatchCodeF();

    bool MatchCodeS();

    bool MatchCodeC();

    void SetF();

    void SetS();

    void SetC();

    void Getline() override ;

    void SetDataForCodes();

    void OutputResult() override;

    void Decode() override;

private:
    Ui::FormKorshun *ui;
    uint m_intByteStateKorshun;
    QRegularExpression m_msgProtocolKorshun;
    QString m_msgKorshun;
    QByteArray m_byteArrayKorshun;
};

#endif // FORMKORSHUN_H
