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
//"{\"cSpeed\": %d,
//\"Pos\": %d,
//\"bAlarm\": %d,"
//"\"lmSpeed\": %d,"
//"\"rmSpeed\": %d,"
//"\"bTemp\": %d,"
//"\"bLevel\": %d,"
//"\"gMode\": %d,"
//"\"cMode\": %d,"
//"\"lmTorque\":%d,"
//"\"rmTorque\":%d,"
//"\"batVol\": %d,"
//"\"carDistce\": %d,"
//"\"mcu1Temp\": %d,"
//"\"mcu2Temp\": %d,"
//"\"brakeTravel\": %d,"
//"\"lmoTemp\": %d,"
//"\"rmoTemp\": %d}";
//{"cSpeed": 122,"Pos": 0,"bAlarm": 0,"lmSpeed": 5700,"rmSpeed": 5700,"bTemp": 40,"bLevel": 100,"gMode": 17,"cMode": 148}
//{"lmTorque":1000,"rmTorque":1000,"batVol": 51,"carDistce": 199,"mcu1Temp": 40,"mcu2Temp": 40,"brakeTravel": 0,"lmoTemp": 40,"rmoTemp": 40}
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

        setCarSpeed(root_Obj.value("cSpeed").toInt());  //地速
        setThroPos(root_Obj.value("Pos").toInt());  //油门开度
        setLmotorTemp(root_Obj.value("lmoTemp").toInt()); //机油压力
        setRmotorTemp(root_Obj.value("rmoTemp").toInt()); //氧传感器
        setLmotorSpeed(root_Obj.value("lmSpeed").toInt());//发动机转速
        setRmotorSpeed(root_Obj.value("rmSpeed").toInt());
        setMcu1Temp(root_Obj.value("mcu1Temp").toInt()); //机油温度
        setMcu2Temp(root_Obj.value("mcu2Temp").toInt()); //发动机温度
        setBatTemp(root_Obj.value("bTemp").toInt());   //ECU温度
        setBatLevel(root_Obj.value("bLevel").toInt());
        setGearMode(root_Obj.value("gMode").toInt()); //挡位 Gear
        setCarMode(root_Obj.value("cMode").toInt());
        setBatAlarm(root_Obj.value("bAlarm").toInt());  //低压电池电量报警
        setMotorSpeed(root_Obj.value("lmSpeed").toInt());
        setTimeCount(root_Obj.value("timeCount").toInt());
        setBatVol(root_Obj.value("batVol").toInt());   //低压电池电量
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
