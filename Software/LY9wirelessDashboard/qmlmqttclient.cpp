#include "qmlmqttclient.h"
#include "QtMqtt/qmqtttopicfilter.h"
#include "QDebug"
QString hostName = "\"82.156.207.102\"";
QString userName = "lingyun";
QString passWord = "lingyun666";
QString ly_topic = "hello";
QmlMqttClient::QmlMqttClient(QObject *parent)
    : QMqttClient(parent)
{

}
void QmlMqttClient::parse(QByteArray package)
{
    qDebug()<<package;
    QJsonParseError err_rpt;
    QJsonDocument  root_Doc = QJsonDocument::fromJson(package, &err_rpt);//字符串格式化为JSON
    if(err_rpt.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON格式错误";
    }
    //{"cSpeed":10,"Pos":"20"}
    else
    {
        QJsonObject root_Obj = root_Doc.object();

        setCarSpeed(root_Obj.value("cSpeed").toInt());
        setThroPos(root_Obj.value("Pos").toInt());
        setLmotorTemp(root_Obj.value("lmoTemp").toInt());
        setRmotorTemp(root_Obj.value("rmoTemp").toInt());
        setLmotorSpeed(root_Obj.value("lmoSpeed").toInt());
        setRmotorSpeed(root_Obj.value("rmoSpeed").toInt());
        setMcu1Temp(root_Obj.value("mcu1Temp").toInt());
        setMcu2Temp(root_Obj.value("mcu2Temp").toInt());
        setBatTemp(root_Obj.value("bTemp").toInt());
        setBatLevel(root_Obj.value("bLevel").toInt());
        setGearMode(root_Obj.value("gMode").toInt());
        setCarMode(root_Obj.value("cMode").toInt());
        setBatAlarm(root_Obj.value("bAlarm").toInt());
        setMotorSpeed(root_Obj.value("mSpeed").toInt());
        setTimeCount(root_Obj.value("timeCount").toInt());
        setBatVol(root_Obj.value("batVol").toInt());
        setCarDistance(root_Obj.value("carDistce").toInt());
        setBrakeTravel(root_Obj.value("brakeTravel").toInt());

    }

}

QmlMqttSubscription* QmlMqttClient::subscribe(const QString &topic)
{
    auto sub = QMqttClient::subscribe(topic, 0);
    auto result = new QmlMqttSubscription(sub, this);
    return result;
}

QmlMqttSubscription::QmlMqttSubscription(QMqttSubscription *s, QmlMqttClient *c)
    : sub(s)
    , client(c)
{
    connect(sub, &QMqttSubscription::messageReceived, client,&QmlMqttClient::onDataRec);
    m_topic = sub->topic();
}

QmlMqttSubscription::~QmlMqttSubscription()
{
}

void QmlMqttClient::onDataRec(const QMqttMessage &qmsg)
{
   // qDebug()<<"message is "<<qmsg.payload();
    parse(qmsg.payload());

    //emit messageReceived(qmsg.payload());
}
