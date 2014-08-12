#ifndef HTTPCONTROL_H
#define HTTPCONTROL_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
class HttpControl:public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString airPower READ getAirPower WRITE setAirPower);
    Q_PROPERTY(QString airTemp READ getAirTemp WRITE setAirTemp);
    Q_PROPERTY(QString airMode READ getAirMode WRITE setAirMode);
    Q_PROPERTY(bool light1 READ light1 WRITE setLight1);
    Q_PROPERTY(bool light2 READ light2 WRITE setLight2);
    Q_PROPERTY(bool light3 READ light3 WRITE setLight3);
    Q_PROPERTY(bool light4 READ light4 WRITE setLight4);
    Q_PROPERTY(bool light5 READ light5 WRITE setLight5);
    Q_PROPERTY(bool light6 READ light6 WRITE setLight6);
    Q_PROPERTY(bool tvPower READ tvPower WRITE setTvPower);
    Q_PROPERTY(int tvVoice READ tvVoice WRITE setTvVoice);
    Q_PROPERTY(int tvChangle READ tvChangle WRITE setTvChangle);
public:
    HttpControl(QObject * parent = 0);
    virtual ~HttpControl();
    bool light1();
    void setLight1(const bool b);
    bool light2();
    void setLight2(const bool b);
    bool light3();
    void setLight3(const bool b);
    bool light4();
    void setLight4(const bool b);
    bool light5();
    void setLight5(const bool b);
    bool light6();
    void setLight6(const bool b);

    int tvVoice();
    int tvChangle();
    bool tvPower();
    void setTvVoice(const int i);
    void setTvChangle(const int i);
    void setTvPower(const bool b);

    QString airPower();
    QString airTemp();
    QString airMode();
    QString getAirPower();
    QString getAirTemp();
    QString getAirMode();
    void setAirPower(const QString& b);
    void setAirTemp(const QString& b);
    void setAirMode(const QString& b);

    void translate(const QString d);

public slots:
   void dataCome(void);
   void dataGoAir(void);
   void dataGoLight(void);
   void dataGoTv(void);
   void dataQuery(void);

signals:
    void airHaveChange();
    void lightHaveChange();
    void tvHaveChange();
private:
    bool strBool(const QChar i);
    QTcpSocket *sock;
    QTimer *timer;
    int m_tvVoice;
    int m_tvChangle;
    bool m_airPower;
    int m_airTemp;
    bool m_tvPower;
    int m_airMode;
    bool m_light1 = false;
    bool m_light2 = false;
    bool m_light3 = false;
    bool m_light4 = false;
    bool m_light5 = false;
    bool m_light6 = false;
};
#endif // HTTPCONTROL_H
