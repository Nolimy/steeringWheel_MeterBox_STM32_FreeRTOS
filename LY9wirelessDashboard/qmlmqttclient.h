#ifndef QMLMQTTCLIENT_H
#define QMLMQTTCLIENT_H

#include <QObject>
#include <QtCore/QMap>
#include <QtMqtt/qmqttclient.h>
#include <QtMqtt/qmqttsubscription.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class QmlMqttClient;

class QmlMqttSubscription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMqttTopicFilter topic MEMBER m_topic NOTIFY topicChanged)
public:
    QmlMqttSubscription(QMqttSubscription *s, QmlMqttClient *c);
    ~QmlMqttSubscription();

Q_SIGNALS:
    void topicChanged(QString);
    void messageReceived(const QString &msg);



private:
    Q_DISABLE_COPY(QmlMqttSubscription)
    QMqttSubscription *sub;
    QmlMqttClient *client;
    QMqttTopicFilter m_topic;
};

class QmlMqttClient : public QMqttClient
{
    Q_OBJECT
    Q_PROPERTY(unsigned int carSpeed READ carSpeed WRITE setCarSpeed NOTIFY carSpeedChanged)
    Q_PROPERTY(unsigned int motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)
    Q_PROPERTY(unsigned int batLevel READ batLevel WRITE setBatLevel NOTIFY batLevelChanged)
    Q_PROPERTY(unsigned int batTemp READ batTemp WRITE setBatTemp NOTIFY batTempChanged)
    Q_PROPERTY(unsigned int lmotorTemp READ lmotorTemp WRITE setLmotorTemp NOTIFY lmotorTempChanged)
    Q_PROPERTY(unsigned int rmotorTemp READ rmotorTemp WRITE setRmotorTemp NOTIFY rmotorTempChanged)
    Q_PROPERTY(unsigned int lmotorSpeed READ lmotorSpeed WRITE setLmotorSpeed NOTIFY lmotorSpeedChanged)
    Q_PROPERTY(unsigned int rmotorSpeed READ rmotorSpeed WRITE setRmotorSpeed NOTIFY rmotorSpeedChanged)
    Q_PROPERTY(unsigned int throPos READ throPos WRITE setThroPos NOTIFY throPosChanged)
    Q_PROPERTY(unsigned int gearMode READ gearMode WRITE setGearMode NOTIFY gearModeChanged)
    Q_PROPERTY(unsigned int carMode READ carMode WRITE setCarMode NOTIFY carModeChanged)
    Q_PROPERTY(unsigned int carDistance READ carDistance WRITE setCarDistance NOTIFY carDistanceChanged)
    Q_PROPERTY(unsigned int brakeTravel READ brakeTravel WRITE setBrakeTravel NOTIFY brakeTravelChanged)
    Q_PROPERTY(unsigned int mcu1Temp READ mcu1Temp WRITE setMcu1Temp NOTIFY mcu1TempChanged)
    Q_PROPERTY(unsigned int mcu2Temp READ mcu2Temp WRITE setMcu2Temp NOTIFY mcu2TempChanged)
    Q_PROPERTY(unsigned int batVol READ batVol WRITE setBatVol NOTIFY batVolChanged)
    Q_PROPERTY(int timeCount READ timeCount WRITE setTimeCount NOTIFY timeCountChanged)
    Q_PROPERTY(bool batAlarm READ batAlarm WRITE setBatAlarm NOTIFY batAlarmChanged)
public:
    QmlMqttClient(QObject *parent = nullptr);

    Q_INVOKABLE QmlMqttSubscription *subscribe(const QString &topic);

    unsigned int carSpeed(){
        return m_carSpeed;
    }
    unsigned int motorSpeed(){
        return m_motorSpeed;
    }

    unsigned int batLevel(){
        return m_batLevel;
    }
    unsigned int batTemp(){
        return m_batTemp;
    }
    unsigned int lmotorTemp(){
        return m_lmotorTemp;
    }
    unsigned int rmotorTemp(){
        return m_rmotorTemp;
    }
    unsigned int lmotorSpeed(){
        return m_lmotorSpeed;
    }
    unsigned int rmotorSpeed(){
        return m_rmotorSpeed;
    }
    unsigned int mcu1Temp(){
        return m_mcu1Temp;
    }
    unsigned int mcu2Temp(){
        return m_mcu2Temp;
    }
    unsigned int throPos(){
        return m_throttlePos;
    }
    unsigned int gearMode(){
        return m_gearMode;
    }
    unsigned int carMode(){
        return m_carMode;
    }
    unsigned int carDistance(){
        return m_carDistance;
    }
    unsigned int brakeTravel(){
        return m_brakeTravel;
    }
    unsigned int batVol(){
        return m_batVol;
    }
    int timeCount(){
        return m_timeCount;
    }
    bool batAlarm(){
        return m_batAlarm;
    }
    void setCarSpeed(const unsigned int &carSpeed) {
        if(carSpeed != m_carSpeed) {
            m_carSpeed = carSpeed;
            emit carSpeedChanged();
        }
    }
    void setCarDistance(const unsigned int &carDistance) {
        if(carDistance != m_carDistance) {
            m_carDistance = carDistance;
            emit carDistanceChanged();
        }
    }


    void setMotorSpeed(const unsigned int &motorSpeed) {
        if(motorSpeed != m_motorSpeed) {
            m_motorSpeed = motorSpeed;
            emit motorSpeedChanged();
        }
    }
    void setBatLevel(const unsigned int &batLevel) {
        if(batLevel != m_batLevel) {
            m_batLevel = batLevel;
            emit batLevelChanged();//电量变化 触发信号
        }
    }
    void setBatTemp(const unsigned int &batTemp) {
        if(batTemp != m_batTemp) {
            m_batTemp = batTemp;
            emit batTempChanged();//电池温度变化 触发信号
        }
    }
    void setLmotorTemp(const unsigned int &lmotorTemp) {
        if(lmotorTemp != m_lmotorTemp) {
            m_lmotorTemp = lmotorTemp;
            emit lmotorTempChanged();//左电机温度变化 触发信号
        }
    }
    void setRmotorTemp(const unsigned int &rmotorTemp) {
        if(rmotorTemp != m_rmotorTemp) {
            m_rmotorTemp = rmotorTemp;
            emit rmotorTempChanged();//右电机温度变化 触发信号
        }
    }
    void setLmotorSpeed(const unsigned int &lmotorSpeed) {
        if(lmotorSpeed != m_lmotorSpeed) {
            m_lmotorSpeed = lmotorSpeed;
            emit lmotorSpeedChanged();//左电机温度变化 触发信号
        }
    }
    void setRmotorSpeed(const unsigned int &rmotorSpeed) {
        if(rmotorSpeed != m_rmotorSpeed) {
            m_rmotorSpeed = rmotorSpeed;
            emit rmotorSpeedChanged();//右电机温度变化 触发信号
        }
    }
    void setMcu1Temp(const unsigned int &mcu1Temp) {
        if(mcu1Temp != m_mcu1Temp) {
            m_mcu1Temp = mcu1Temp;
            emit mcu1TempChanged();//电机控制器1温度变化 触发信号
        }
    }
    void setMcu2Temp(const unsigned int &mcu2Temp) {
        if(mcu2Temp != m_mcu2Temp) {
            m_mcu2Temp = mcu2Temp;
            emit mcu2TempChanged();//电机控制器2温度变化 触发信号
        }
    }
    void setThroPos(const unsigned int &throPos) {
        if(throPos != m_throttlePos) {
            m_throttlePos = throPos;
            emit throPosChanged();//踏板开度变化，触发信号
        }
    }
    void setGearMode(const unsigned int &gearMode) {
        if(gearMode != m_gearMode) {
            m_gearMode = gearMode;
            emit gearModeChanged();//挡位变化，触发信号
        }
    }
    void setCarMode(const unsigned int &carMode) {
        if(carMode != m_carMode) {
            m_carMode = carMode;
            emit carModeChanged();//车辆模式变化，触发信号
        }
    }
    void setBatAlarm(const bool &batAlarm) {
        if(batAlarm != m_batAlarm) {
            m_batAlarm = batAlarm;
            emit batAlarmChanged();//电池低压报警，触发信号
        }
    }
    void setTimeCount(const int &timeCount) {
        if(timeCount != m_timeCount) {
            m_timeCount = timeCount;
            emit timeCountChanged();//运行时间，单位0.5s。触发信号
        }
    }
    void setBatVol(const unsigned int &batVol) {
        if(batVol != m_batVol) {
            m_batVol = batVol;
            emit batVolChanged();//电池电压，触发信号
        }
    }
    void setBrakeTravel(const unsigned int &braketravel) {
        if(braketravel != m_brakeTravel) {
            m_brakeTravel = braketravel;
            emit brakeTravelChanged();//刹车踏板开度，触发信号
        }
    }


    void parse(QByteArray package);

signals:
    void carSpeedChanged();
    void motorSpeedChanged();
    void batLevelChanged();
    void batTempChanged();
    void throPosChanged();
    void gearModeChanged();
    void carModeChanged();
    void batAlarmChanged();
    void timeCountChanged();
    void batVolChanged();
    void mcu2TempChanged();
    void mcu1TempChanged();
    void carDistanceChanged();
    void brakeTravelChanged();
    void rmotorTempChanged();
    void lmotorTempChanged();
    void rmotorSpeedChanged();
    void lmotorSpeedChanged();
public slots:
    void onDataRec(const QMqttMessage &qmsg);


private:
    Q_DISABLE_COPY(QmlMqttClient)
    unsigned int m_carSpeed;
    unsigned int m_motorSpeed;
    unsigned int m_batLevel;
    unsigned int m_batTemp;
    unsigned int m_throttlePos;
    unsigned int m_gearMode;// 0 R  1 N   2 D
    unsigned int m_carMode;
    unsigned int m_batVol;
    unsigned int m_lmotorTemp;
    unsigned int m_rmotorTemp;
    unsigned int m_lmotorSpeed;
    unsigned int m_rmotorSpeed;
    unsigned int m_mcu1Temp;
    unsigned int m_mcu2Temp;
    unsigned int m_carDistance;
    unsigned int m_brakeTravel;
    int m_timeCount;
    bool m_batAlarm;


};



#endif // QMLMQTTCLIENT_H
