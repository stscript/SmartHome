#include "httpControl.h"
#include <QDebug>

HttpControl::HttpControl(QObject *parent):QObject(parent),
    m_airMode(1),
    m_airPower(false),
    m_airTemp(25),
    m_tvChangle(0),
    m_tvVoice(0),
    m_tvPower(false)
{
    sock = new QTcpSocket;
    sock->bind(4589);
    sock->connectToHost("localhost",4589);
//    sock->write("hello,I am Qt");

    timer = new QTimer;
    timer->setInterval(300);
    timer->start();
    connect(sock,SIGNAL(readyRead()),this,SLOT(dataCome()));
    connect(timer,SIGNAL(timeout()),this,SLOT(dataQuery()));
 //   connect(timer,SIGNAL(timeout()),this,SLOT(dataQueryTv()));
//    connect(timer,SIGNAL(timeout()),this,SLOT(dataQueryLight()));
}
void HttpControl::dataQuery(){
    static int count = 1;
    if(sock->ConnectedState == QAbstractSocket::ConnectedState)
    {
        count ++;
        if(count > 3)
            count = 1;
        switch(count)
        {
        case 1:
            sock->write("q1");
            break;
        case 2:
            sock->write("q2");
            break;
        case 3:
            sock->write("q3");
            break;
        }
    }
}

void HttpControl::dataCome(){
    char data[1024];
    QString ss;
    sock->readLine(data,1024);
    ss = QString(data);
    translate(ss);
    qDebug(data);
}
void HttpControl::dataGoAir(){
    QString ss;
    QString s1;
    QString s2;
    QString s3;
    if(sock->ConnectedState == QAbstractSocket::ConnectedState){
        m_airPower?s1="1":s1="0";
        s2.setNum(m_airTemp);
        s3.setNum(m_airMode);
        ss = "t"+s2+"m"+s3+"p"+s1+"\n";
        qDebug()<<ss;
        sock->write(ss.toLocal8Bit());
    }
}
void HttpControl::dataGoTv(){
    QString ss;
    QString s1;
    QString s2;
    QString s3;
    if(sock->ConnectedState == QAbstractSocket::ConnectedState){
        m_tvPower?s1="1":s1="0";
        s3.setNum(m_tvChangle);
        m_tvVoice>9?s2.setNum(m_tvVoice):s2="0"+s2.setNum(m_tvVoice);

        ss = "c"+s3+"v"+s2+"p"+s1+"\n";

        sock->write(ss.toLatin1());
    }
}
void HttpControl::dataGoLight(){
    QString ss;
    QString s1;
    QString s2;
    QString s3;
    QString s4;
    QString s5;
    QString s6;
    if(sock->ConnectedState == QAbstractSocket::ConnectedState){
        m_light1?s1="1":s1="0";
        m_light2?s2="1":s2="0";
        m_light3?s3="1":s3="0";
        m_light4?s4="1":s4="0";
        m_light5?s5="1":s5="0";
        m_light6?s6="1":s6="0";
        ss = "l"+s1+"l"+s2+"l"+s3+"l"+s4+"l"+s5+"l"+s6+"\n";
        sock->write(ss.toLatin1());
    }
}
bool HttpControl::strBool(const QChar i){
    if(i == '1')
    {
        return true;
    }else
        return false;
}
void HttpControl::translate(const QString d)
{
    QString t;
    QString m;
    QString p;

    if((d[0] == 't')&&(d[3] == 'm')&&(d[5] == 'p'))
    {
        t =QString(d[1])+QString(d[2]);
        m =QString(d[4]);
        p = QString(d[6]);
        setAirTemp(t);
        setAirMode(m);
        setAirPower(p);
    }else if((d[0] == 'l')&&(d[2] == 'l')&&(d[4] == 'l')&&(d[6] == 'l')&&(d[8] == 'l')&&(d[10] == 'l'))
    {
        setLight1(strBool(d[1]));
        setLight2(strBool(d[3]));
        setLight3(strBool(d[5]));
        setLight4(strBool(d[7]));
        setLight5(strBool(d[9]));
        setLight6(strBool(d[11]));
    }else if((d[0] == 'c')&&(d[2] == 'v')&&(d[5]=='p')){
        setTvPower(strBool(d[6]));
        t = QString(d[1]);
        m = QString(d[3])+QString(d[4]);

        setTvChangle(t.toInt());
        setTvVoice(m.toInt());
    }

}
int HttpControl::tvChangle(){
    return m_tvChangle;
}
void HttpControl::setTvChangle(const int i){
    m_tvChangle = i;
    emit tvHaveChange();
}
int HttpControl::tvVoice(){
    return m_tvVoice;
}
void HttpControl::setTvVoice(const int i){
    m_tvVoice = i;
    emit tvHaveChange();
}
bool HttpControl::tvPower(){
    return m_tvPower;
}
void HttpControl::setTvPower(const bool b){
    m_tvPower = b;
    emit tvHaveChange();
}
bool HttpControl::light1()
{
    return m_light1;
}
void HttpControl::setLight1(const bool b){
    m_light1 = b;
    emit lightHaveChange();
}
bool HttpControl::light2()
{
    return m_light2;
}
void HttpControl::setLight2(const bool b){
    m_light2 = b;
    emit lightHaveChange();
}
bool HttpControl::light3()
{
    return m_light3;
}
void HttpControl::setLight3(const bool b){
    m_light3 = b;
    emit lightHaveChange();
}
bool HttpControl::light4()
{
    return m_light4;
}
void HttpControl::setLight4(const bool b){
    m_light4 = b;
    emit lightHaveChange();
}
bool HttpControl::light5()
{
    return m_light5;
}
void HttpControl::setLight5(const bool b){
    m_light5 = b;
    emit lightHaveChange();
}
bool HttpControl::light6()
{
    return m_light6;
}
void HttpControl::setLight6(const bool b){
    m_light6 = b;
    emit lightHaveChange();
}
QString HttpControl::airPower(){
    if(m_airPower)
    {
        return "1";
    }else{
        return "0";
    }

}
QString HttpControl::airMode(){
    switch(m_airMode)
    {
    case 1:
        return "1";// "制冷";
    case 2:
        return "2";//"除湿";
    case 3:
        return "3";// "铺热";
    case 4:
        return "4";//"睡眠";
    }

    return "";
}
QString HttpControl::airTemp(){

 //   qDebug()<<QString(m_airTemp);
    return QString::number(m_airTemp,10);
}

HttpControl::~HttpControl(){
    delete this;
}
void HttpControl::setAirMode(const QString& b){
    int i = b.toInt();
    qDebug()<<i<<b;
    if(i<5)
    {
        m_airMode = i;
        emit airHaveChange();
    }
}
void HttpControl::setAirTemp(const QString& b){
    int i = b.toInt();


    if((i<=31)&&(i>=16))
    {
        m_airTemp = i;
        emit airHaveChange();
    }
}
void HttpControl::setAirPower(const QString& b){
    bool i = b.toInt();
    if(i == 1)
        m_airPower = true;
    else
        m_airPower = false;

    emit airHaveChange();
}
QString HttpControl::getAirPower(){
    if(m_airPower)
    {
        return "1";
    }else{
        return "0";
    }
}
QString HttpControl::getAirMode(){
    return airMode();
}
QString HttpControl::getAirTemp(){
    return QString::number(m_airTemp,10);
}
