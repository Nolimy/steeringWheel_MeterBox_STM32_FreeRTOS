import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Extras.Private 1.0
import QtCharts 2.3
import MqttClient 1.0


Window {
    visible: true
    width: 1920
    height: 1080
    color: "#333333"
    property alias rectangleX: rectangle.x
    title: qsTr("LY9-WirelessDashboard")

    //加载字体
    FontLoader {
        id: localFont
        source: "big-numbers.ttf"
    } //仪表数字显示使用字体

    //FontLoader {
    //    id: kfont
    //    source: "Cinzel-Regular.ttf"
    //} //版权声明处使用字体

    //FontLoader {
    //    id: wfont
    //    source: "PlayfairDisplaySC-Black.ttf"
    //} //Gear处使用字体
    FontLoader {
        id: ffont
        source: "FasterOne-Regular.ttf"
    } //Gear处使用字体

    FontLoader {
        id: ffzont
        source: "TTZhiHeiJ-W4.ttf"
    }

    property int rpm_test: 0
    property int count: 0
    property int m_port:1883
    property string m_topic: "hello"
    property int tempSubscription: 0
    MqttClient{
        id:carData
        hostname: "82.156.207.102"
        port: m_port
        username: "lingyun"
        password: "lingyun666"

        onConnected:{


            carData.subscribe("hello")

        }

        onStateChanged: {

            if (carData.state === MqttClient.Connected) {
                mqttStatus.active = true
            } else{
                mqttStatus.active = false
            }
        }

        carSpeed: 0
        motorSpeed: 0
        batLevel: 0
        batTemp: 0
        throPos: 0
        timeCount: 0
        batVol: 0
        mcu1Temp: 0
        mcu2Temp: 0
        carDistance: 0
        brakeTravel: 0
        lmotorTemp: 0
        rmotorTemp: 0
        lmotorSpeed: 0
        rmotorSpeed: 0
        onCarModeChanged: {
            if(carMode == 0)
            {
                modeStatus.active = false
            }
            else if(carMode == 1)
            {
                modeStatus.active = false
            }
            else if(carMode == 2)
            {
                modeStatus.active = true
            }
        }
        onGearModeChanged: {
            if(gearMode == 3)
                runStuatus.active = true
            else
                runStuatus.active = false

        }
        onBatAlarmChanged:{
            socAlarmFlag = batAlarm
        }





    }
    CircularGauge {
        id: gauge_speed
        x: 38
        y: 99
        width: 262
        height: 262
        maximumValue: 120

        //property bool accelerating

        //value: accelerating ? maximumValue : 0

        value:carData.carSpeed
        //focus:true
        //value: rpm_test
        //Component.onCompleted: forceActiveFocus()
        Behavior on value {
            NumberAnimation {
                duration: 600
            }
        }

        transformOrigin: Item.Center

        style: CircularGaugeStyle {

            minimumValueAngle: -180

            maximumValueAngle: 90

            //background:
            tickmarkLabel: Text {
                text: " "
            }

            needle: Rectangle {
                // y: outerRadius * 0.15
                implicitWidth: outerRadius * 0.05
                implicitHeight: outerRadius * 1.01
                radius: outerRadius * 0.05
                antialiasing: true
                color: "#0099cc"
            }

            foreground: Canvas {
                property int value: gauge_speed.value

                onValueChanged: requestPaint()

                opacity: 0.8

                function degreesToRadians(degrees) {
                    return degrees * (Math.PI / 180)
                }
                onPaint: {

                    var ctx = getContext("2d")
                    ctx.reset()

                    ctx.beginPath()
                    ctx.strokeStyle = "#0099cc"
                    ctx.lineWidth = outerRadius * 1.01

                    ctx.arc(outerRadius, outerRadius,
                            outerRadius - ctx.lineWidth / 2, degreesToRadians(
                                valueToAngle(0) - 90), degreesToRadians(
                                valueToAngle(gauge_speed.value) - 90))
                    ctx.stroke()
                }
            }

            Item {
                Rectangle {
                    width: outerRadius * 0.1
                    height: 20
                    radius: width / 2
                    color: "black"
                    anchors.centerIn: parent
                }
            }
            tickmark: Rectangle {
                implicitWidth: outerRadius * 0.04

                implicitHeight: outerRadius * 0.21

                radius: outerRadius * 0.04

                z: 2

                color: "#336699"
            }
            minorTickmarkCount: 5
            minorTickmark: Rectangle {

                implicitWidth: outerRadius * 0.04

                implicitHeight: outerRadius * 0.21

                radius: outerRadius * 0.04

                z: 2

                color: "#336699"
            }
        }

        Rectangle {
            id: rectangle
            x: 30
            y: 30
            width: parent.width - 60
            height: parent.height - 60
            color: "#333333"
            radius: 100

            Text {
                id: kmh_10
                x: 73
                y: 69
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_speed.value / 10 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 60
            }

            Text {
                id: kmh_100
                x: 24
                y: 69
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_speed.value / 100 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: "big-numbers"
            }

            Text {
                id: kmh_1
                x: 122
                y: 69
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_speed.value / 1 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: "big-numbers"
            }

            Text {
                id: kmh
                x: 71
                y: 147
                width: 61
                height: 47
                color: "#f1f4f1"
                text: qsTr("KMH")
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 30
            }
        }
    }

    CircularGauge {
        id: gauge_rpm
        x: 348
        y: 99
        width: 262
        height: 262
        maximumValue: 8000

        value:carData.motorSpeed
        //value: rpm_test
        Behavior on value {
            NumberAnimation {
                duration: 600
            }
        }

        transformOrigin: Item.Center

        style: CircularGaugeStyle {
            id:rpm_style
            minorTickmarkCount: 7
            tickmarkInset: 1
            tickmarkStepSize: 1000

            minimumValueAngle: -180

            maximumValueAngle: 90

            //background:
            tickmarkLabel: Text {
                text: " "
            }

            needle: Rectangle {
                // y: outerRadius * 0.15
                implicitWidth: outerRadius * 0.05
                implicitHeight: outerRadius * 1.01
                radius: outerRadius * 0.05
                antialiasing: true
                color: "#0099cc"
            }

            foreground: Canvas {
                property int value: gauge_rpm.value

                onValueChanged: requestPaint()

                opacity: 0.8

                function degreesToRadians(degrees) {
                    return degrees * (Math.PI / 180)
                }
                onPaint: {

                    var ctx = getContext("2d")
                    ctx.reset()

                    ctx.beginPath()
                    ctx.strokeStyle = "#0099cc"
                    ctx.lineWidth = outerRadius * 1.01

                    ctx.arc(outerRadius, outerRadius,
                            outerRadius - ctx.lineWidth / 2, degreesToRadians(
                                valueToAngle(0) - 90), degreesToRadians(
                                valueToAngle(gauge_rpm.value) - 90))
                    ctx.stroke()
                }
            }

            Item {
                Rectangle {
                    width: outerRadius * 0.1
                    height: 20
                    radius: width / 2
                    color: "black"
                    anchors.centerIn: parent
                }
            }
            tickmark: Rectangle {
                implicitWidth: outerRadius * 0.04

                implicitHeight: outerRadius * 0.21

                radius: outerRadius * 0.04

                z: 4

                color: "#336699"
            }
            //minorTickmarkCount: 100
            minorTickmark: Rectangle {

                implicitWidth: outerRadius * 0.04

                implicitHeight: outerRadius * 0.21

                radius: outerRadius * 0.04

                z: 2

                color: "#336699"
            }
        }

        Rectangle {
            id: rectangle1
            x: 30
            y: 30
            width: parent.width - 60
            height: parent.height - 60
            color: "#333333"
            radius: 100

            Text {
                id: rpm_10
                x: 96
                y: 69
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_rpm.value / 10 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: "big-numbers"
            }

            Text {
                id: rpm_100
                x: 49
                y: 69
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_rpm.value / 100 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: "big-numbers"
            }

            Text {
                id: rpm_1
                x: 145
                y: 69
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_rpm.value / 1 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
                font.family: "big-numbers"
            }

            Text {
                id: rpm
                x: 71
                y: 147
                width: 61
                height: 47
                color: "#f1f4f1"
                text: qsTr("RPM")
                font.bold: true
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: rpm_1000
                x: 0
                y: 69
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_rpm.value / 1000 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 60
            }
        }
    }

    CircelBar {
        id: speedUpPadelTravel
        x: 38
        y: 456
        width: 557
        height: 30
        value: carData.throPos
        color: "#336699"


    }

    CircelBar {
        id: brakePadelTravel
        x: 38
        y: 562
        width: 557
        height: 30
        value:carData.brakeTravel
    }

    Label {
        id: speedUp
        x: 38
        y: 513
        width: 153
        height: 27
        color: "#99ccff"
        text: qsTr("加速踏板行程")
        font.family: "Tensentype ZhiHeiJ-W4"
        font.pointSize: 14
    }

    Label {
        id: brake
        x: 38
        y: 621
        width: 153
        height: 27
        color: "#99ccff"
        text: qsTr("刹车踏板行程")
        font.family: "Tensentype ZhiHeiJ-W4"
        font.pointSize: 14
    }

    Label {
        id: speed
        x: 93
        y: 384
        width: 153
        height: 27
        color: "#99ccff"
        text: qsTr("车速")
        horizontalAlignment: Text.AlignHCenter
        font.family: "Tensentype ZhiHeiJ-W4"
        font.pointSize: 12
    }

    Label {
        id: mspeed
        x: 403
        y: 384
        width: 153
        height: 27
        color: "#99ccff"
        text: qsTr("发动机转速")
        font.family: "Tensentype ZhiHeiJ-W4"
        font.pointSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    Image {
        id: logo
        x: 1472
        y: 20
        width: 320
        height: 297
        fillMode: Image.PreserveAspectFit
        source: "lingyun.png"

        TextEdit {
            id: logoText
            x: -14
            y: 223
            width: 348
            height: 66
            color: "#99ccff"
            text: qsTr("LingYunRacingTeam")
            wrapMode: Text.WordWrap
            font.family: "Faster One"
            selectionColor: "#336699"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 27
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.debug("count   =====   ", count)
                count++
                if (count == 10) {
                    borderImage.visible = true
                    speedChart.visible = false
                    rpmChart.visible = false
                }

                if (count == 1) {
                    $message({
                                 "message": '吃太饱了？',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 2) {
                    $message({
                                 "message": '有病病？？',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 3) {
                    $message({
                                 "message": '哪儿凉快哪儿呆着去！',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 4) {
                    $message({
                                 "message": '车修好了？',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 5) {
                    $message({
                                 "message": '四六级都过了？',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 6) {
                    $message({
                                 "message": '欸你这人怎么回事儿？',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 7) {
                    $message({
                                 "message": '你再点一下试试？',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 8) {
                    $message({
                                 "message": '没完了是吧？？？',
                                 "type": 'info',
                                 "show": true
                             })
                } else if (count == 9) {
                    $message({
                                 "message": '有点儿什么大病',
                                 "type": 'info',
                                 "show": true
                             })
                }
            }
        }
    }

    StatusIndicator {

        id: runStuatus
        x: 1726
        y: 323
        width: 86
        height: 67
        color: "#6095c9"

        active: false

        Label {
            id: runLabel
            x: 9
            y: 73
            width: 68
            height: 22
            color: "#99ccff"
            text: qsTr("RUN")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pointSize: 12
            font.capitalization: Font.AllUppercase
        }
    }

    StatusIndicator {
        id: mqttStatus
        x: 1449
        y: 323
        width: 101
        height: 67
        color: "#6095c9"
        active: false

        Label {
            id: mqttLabel
            x: 17
            y: 73
            width: 68
            height: 22
            color: "#99ccff"
            text: qsTr("MQTT")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pointSize: 12
            font.capitalization: Font.AllUppercase
        }
    }


    Item {
        id: lmotorTempLabel
        x: 49
        y: 678
        width: 100
        height: 100

        Text {
            id: lmotorTemp
            x: 9
            y: 63
            color: "#b4cfe5"
            text: qsTr("机油压力")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }

        Text {
            id: lmotorTemp_10
            x: 15
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.lmotorTemp / 10 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 35
        }

        Text {
            id: lmotorTemp_1
            x: 39
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.lmotorTemp / 1 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item {
        id: rmotorTempLabel
        x: 182
        y: 678
        width: 100
        height: 100
        Text {
            id: rmotorTemp
            x: 9
            y: 63
            color: "#b4cfe5"
            text: qsTr("氧传感器")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }

        Text {
            id: rmotorTemp_10
            x: 15
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.rmotorTemp / 10 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: rmotorTemp_1
            x: 39
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.rmotorTemp / 1 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item {
        id: batTempLabel
        x: 318
        y: 678
        width: 100
        height: 100
        Text {
            id: batTemp_10
            x: 15
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batTemp / 10 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: batTemp_1
            x: 39
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batTemp / 1 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: batTemp
            x: 17
            y: 62
            color: "#b4cfe5"
            text: qsTr("ECU温度")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }
    }

    Item {
        id: batVolLabel
        x: 440
        y: 678
        width: 100
        height: 100
        Text {
            id: batVol_100
            x: 15
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batVol / 100 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: batVol_10
            x: 39
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batVol / 10 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: batVol_1
            x: 70
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batVol / 1 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: batVol
            x: 31
            y: 61
            color: "#b4cfe5"
            text: qsTr("低压电池电压")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }
    }

    Item {
        id: runTravelLabel
        x: 1719
        y: 731
        width: 100
        height: 100
        Text {
            id: runTravel
            x: 8
            y: 62
            color: "#b4cfe5"
            text: qsTr("行驶里程/km")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }

        Text {
            id: runTravel_100
            x: 0
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.carDistance / 100 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: runTravel_10
            x: 28
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.carDistance / 10 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: runTravel_1
            x: 62
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.carDistance / 1 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item {
        id: runTimeLabel
        x: 1433
        y: 731
        width: 100
        height: 100
        Text {
            id: runTime_100
            x: 0
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.timeCount / 120 / 100 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: runTime_10
            x: 28
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.timeCount / 120 / 10 % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: runTime_1
            x: 62
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.timeCount / 120  % 10)
            horizontalAlignment: Text.AlignHCenter
            font.family: "big-numbers"
            font.pixelSize: 35
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: runTime
            x: 8
            y: 62
            color: "#b4cfe5"
            text: qsTr("运行时间/min")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }
    }
    CircularGauge {
            id: gauge_Lrpm
            x: 1383
            y: 471
            width: 200
            height: 200
            maximumValue: 8000

            value:carData.lmotorSpeed
            //value: rpm_test
            Behavior on value {
                NumberAnimation {
                    duration: 600
                }
            }

            transformOrigin: Item.Center

            style: CircularGaugeStyle {
                id:lrpm_style
                minorTickmarkCount: 7
                tickmarkInset: 1
                tickmarkStepSize: 1000

                minimumValueAngle: -180

                maximumValueAngle: 90

                //background:
                tickmarkLabel: Text {
                    text: " "
                }

                needle: Rectangle {
                    // y: outerRadius * 0.15
                    implicitWidth: outerRadius * 0.05
                    implicitHeight: outerRadius * 1.01
                    radius: outerRadius * 0.05
                    antialiasing: true
                    color: "#0099cc"
                }

                foreground: Canvas {
                    property int value: gauge_rpm.value

                    onValueChanged: requestPaint()

                    opacity: 0.8

                    function degreesToRadians(degrees) {
                        return degrees * (Math.PI / 180)
                    }
                    onPaint: {

                        var ctx = getContext("2d")
                        ctx.reset()

                        ctx.beginPath()
                        ctx.strokeStyle = "#0099cc"
                        ctx.lineWidth = outerRadius * 1.01

                        ctx.arc(outerRadius, outerRadius,
                                outerRadius - ctx.lineWidth / 2, degreesToRadians(
                                    valueToAngle(0) - 90), degreesToRadians(
                                    valueToAngle(gauge_Lrpm.value) - 90))
                        ctx.stroke()
                    }
                }

                Item {
                    Rectangle {
                        width: outerRadius * 0.1
                        height: 20
                        radius: width / 2
                        color: "black"
                        anchors.centerIn: parent
                    }
                }
                tickmark: Rectangle {
                    implicitWidth: outerRadius * 0.04

                    implicitHeight: outerRadius * 0.21

                    radius: outerRadius * 0.04

                    z: 4

                    color: "#336699"
                }
                //minorTickmarkCount: 100
                minorTickmark: Rectangle {

                    implicitWidth: outerRadius * 0.04

                    implicitHeight: outerRadius * 0.21

                    radius: outerRadius * 0.04

                    z: 2

                    color: "#336699"
                }
            }

        Rectangle {
            id: lrpmBeforeground
            x: 26
            y: 26
            width: 148
            height: 148
            color: "#333333"
            radius: 100
            Text {
                id: lrpm_100
                x: 28
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Lrpm.value / 100 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }

            Text {
                id: lrpm_1000
                x: -7
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Lrpm.value / 1000 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }

            Text {
                id: lrpm_10
                x: 63
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Lrpm.value / 10 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }

            Text {
                id: lrpm
                x: 39
                y: 94
                width: 61
                height: 47
                color: "#f1f4f1"
                text: qsTr("RPM")
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 25
            }

            Text {
                id: lrpm_1
                x: 96
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Lrpm.value / 1 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }
        }
    }
    CircularGauge {
            id: gauge_Rrpm
            x: 1669
            y: 471
            width: 200
            height: 200
            maximumValue: 8000

            value:carData.rmotorSpeed
            //value: rpm_test
            Behavior on value {
                NumberAnimation {
                    duration: 600
                }
            }

            transformOrigin: Item.Center

            style: CircularGaugeStyle {
                id:rrpm_style
                minorTickmarkCount: 7
                tickmarkInset: 1
                tickmarkStepSize: 1000

                minimumValueAngle: -180

                maximumValueAngle: 90

                //background:
                tickmarkLabel: Text {
                    text: " "
                }

                needle: Rectangle {
                    // y: outerRadius * 0.15
                    implicitWidth: outerRadius * 0.05
                    implicitHeight: outerRadius * 1.01
                    radius: outerRadius * 0.05
                    antialiasing: true
                    color: "#0099cc"
                }

                foreground: Canvas {
                    property int value: gauge_rpm.value

                    onValueChanged: requestPaint()

                    opacity: 0.8

                    function degreesToRadians(degrees) {
                        return degrees * (Math.PI / 180)
                    }
                    onPaint: {

                        var ctx = getContext("2d")
                        ctx.reset()

                        ctx.beginPath()
                        ctx.strokeStyle = "#0099cc"
                        ctx.lineWidth = outerRadius * 1.01

                        ctx.arc(outerRadius, outerRadius,
                                outerRadius - ctx.lineWidth / 2, degreesToRadians(
                                    valueToAngle(0) - 90), degreesToRadians(
                                    valueToAngle(gauge_Rrpm.value) - 90))
                        ctx.stroke()
                    }
                }

                Item {
                    Rectangle {
                        width: outerRadius * 0.1
                        height: 20
                        radius: width / 2
                        color: "black"
                        anchors.centerIn: parent
                    }
                }
                tickmark: Rectangle {
                    implicitWidth: outerRadius * 0.04

                    implicitHeight: outerRadius * 0.21

                    radius: outerRadius * 0.04

                    z: 4

                    color: "#336699"
                }
                //minorTickmarkCount: 100
                minorTickmark: Rectangle {

                    implicitWidth: outerRadius * 0.04

                    implicitHeight: outerRadius * 0.21

                    radius: outerRadius * 0.04

                    z: 2

                    color: "#336699"
                }
            }


        Rectangle {
            id: rrpmBeforeground
            x: 26
            y: 26
            width: 148
            height: 148
            color: "#333333"
            radius: 100
            Text {
                id: rrpm_100
                x: 28
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Rrpm.value / 100 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }

            Text {
                id: rrpm_1000
                x: -7
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Rrpm.value / 1000 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }

            Text {
                id: rrpm_10
                x: 63
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Rrpm.value / 10 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }

            Text {
                id: rrpm
                x: 39
                y: 94
                width: 61
                height: 47
                color: "#f1f4f1"
                text: qsTr("RPM")
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 25
            }

            Text {
                id: rrpm_1
                x: 96
                y: 42
                width: 57
                height: 64
                color: "#f1f4f1"
                text: parseInt(gauge_Rrpm.value / 1 % 10)
                horizontalAlignment: Text.AlignHCenter
                font.family: "big-numbers"
                font.pixelSize: 45
            }
        }
    }

    Label {
        id: lRpmLabel
        x: 1407
        y: 698
        width: 153
        height: 27
        color: "#99ccff"
        text: qsTr("左电机转速")
        horizontalAlignment: Text.AlignHCenter
        font.family: "Tensentype ZhiHeiJ-W4"
        font.pointSize: 12
    }

    Label {
        id: rRpmLabel
        x: 1693
        y: 698
        width: 153
        height: 27
        color: "#99ccff"
        text: qsTr("右电机转速")
        horizontalAlignment: Text.AlignHCenter
        font.family: "Tensentype ZhiHeiJ-W4"
        font.pointSize: 12
    }

    Button {
        id: saveBut
        x: 1433
        y: 893
        //tooltip: qsTr("")
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25

                border.color: "#0099cc"
                color: "#0099cc"
                radius: 10

                Text {
                    id: btnText
                    anchors.centerIn: parent
                    text: qsTr("Save")
                    color: "white"
                }
            }
        }

    Button {
        id: connectBut
        x: 1720
        y: 893
        //ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25

                border.color: "#0099cc"
                color: "#0099cc"
                radius: 10

                Text {
                    //id: btnText
                    anchors.centerIn: parent
                    text: carData.state === MqttClient.Connected ? "Disconnect" : "Connect"
                    color: "white"
                }
            }
       // }
        onClicked: {
            if (carData.state === MqttClient.Connected) {
                carData.disconnectFromHost()
                time.running = false

                //mqttStatus.active = false
            } else{
                carData.connectToHost()
                time.running = true


            }

        }

    }

    Item {
        id: timeLabel
        x: 27
        y: 893
        width: 507
        height: 126

        Text {
            id: element29
            x: 5
            y: 26
            color: "#96c4f1"
            text: qsTr("TIME:")
            font.pixelSize: 48
            font.weight: Font.Bold
            font.family: "Lobster"
        }

        Text {
            id: datatime
            x: 161
            y: 23
            color: "#96c4f1"
            text: currentDateTime()
            font.family: "big-numbers"
            font.weight: Font.Bold
            font.pixelSize: 48
        }
    }

    function currentDateTime() {
        return Qt.formatDateTime(new Date(), "hh:mm:ss")
    }

    Timer {
        id: timer
        interval: 1
        repeat: true
        onTriggered: {
            datatime.text = currentDateTime()
        }
        Component.onCompleted: {
            timer.start()
        }
    }

    BorderImage {
        id: borderImage
        x: 672
        y: 17
        width: 621
        height: 975
        visible: false
        source: "me.jpg"
    }
    Message {
        id: message
        z: 3
    }

    ChartView {
        id: speedChart
        x: 633
        y: 56
        width: 720
        height: 443
        dropShadowEnabled: true
        localizeNumbers: false
        legend.visible: false
        plotAreaColor: "#333333"
        backgroundRoundness: 2.2
        backgroundColor: "#333333"
        animationOptions: ChartView.SeriesAnimations
        property double timer: 0

        ValueAxis {
            id: axisX
            min: 0
            max: 10
            labelsColor: "white"
            tickCount: 11
            //labelsVisible: false
            gridVisible: false
            color: "white"
            labelFormat: "%d"
        }
        ValueAxis {
            id: axisY
            min: 0
            max: 120
            tickCount: 12
            //labelsVisible: false
            labelsColor: "white"
            gridVisible: false
            color: "white"
            labelFormat: "%d"
        }
        SplineSeries {
            id: lineSeries
            name: "speed"
            axisX: axisX
            axisY: axisY
            width: 5
            color: "#96c4f1"
            useOpenGL: true
        }

        Label {
            id: label9
            x: 639
            y: 406
            width: 81
            height: 23
            color: "#f1f4f1"
            text: qsTr("time/0.5s")
            font.pointSize: 11
            font.family: "Tahoma"
        }
        Label {
            id: label12
            x: 88
            y: 21
            width: 81
            height: 23
            color: "#f1f4f1"
            text: qsTr("KMH")
            font.family: "Tahoma"
            font.pointSize: 11
        }
    }

    ChartView {
        id: rpmChart
        x: 633
        y: 490
        width: 720
        height: 443
        dropShadowEnabled: true
        legend.visible: false
        plotAreaColor: "#333333"
        backgroundRoundness: 0.1
        backgroundColor: "#333333"
        animationOptions: ChartView.SeriesAnimations
        property double timer_rpm: 0

        ValueAxis {
            id: axisX_rpm
            min: 0
            max: 10
            labelsColor: "white"
            tickCount: 11
            //labelsVisible: false
            gridVisible: false
            color: "white"
            labelFormat: "%d"
        }
        ValueAxis {
            id: axisY_rpm
            min: 0
            max: 8000
            tickCount: 8
            //labelsVisible: false
            labelsColor: "white"
            gridVisible: false
            color: "white"
            labelFormat: "%d"
        }
        SplineSeries {
            id: rpmSeries
            name: "RPM"
            axisX: axisX_rpm
            axisY: axisY_rpm
            width: 5
            color: "#96c4f1"
            useOpenGL: true
        }
        Label {
            id: label10
            x: 639
            y: 406
            width: 81
            height: 23
            color: "#f1f4f1"
            text: qsTr("time/0.5s")
            font.pointSize: 11
            font.family: "Tahoma"
        }

        Label {
            id: label11
            x: 88
            y: 21
            width: 81
            height: 23
            color: "#f1f4f1"
            text: qsTr("RPM")
            font.family: "Tahoma"
            font.pointSize: 11
        }
    }
    Timer {
        id: time
        interval: 500
        //running: true
        repeat: true
        onTriggered: {
            lineSeries.append(speedChart.timer, gauge_speed.value)
            rpmSeries.append(rpmChart.timer_rpm, gauge_rpm.value)
            ++speedChart.timer
            ++rpmChart.timer_rpm
            if (speedChart.timer >= (axisX.tickCount + 1)) {
                speedChart.scrollRight(
                            speedChart.plotArea.width / (axisX.tickCount - 1))
            }
            if (rpmChart.timer_rpm >= (axisX_rpm.tickCount + 1)) {
                rpmChart.scrollRight(
                            rpmChart.plotArea.width / (axisX_rpm.tickCount - 1))
            }
        }
    }

    Item {
        id: lMcuTempLabel1
        x: 119
        y: 784
        width: 100
        height: 100
        Text {
            id: lMcuTemp
            x: -11
            y: 59
            color: "#b4cfe5"
            text: qsTr("机油温度")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }

        Text {
            id: lMcuTemp_10
            x: 15
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.mcu1Temp / 10 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: lMcuTemp1
            x: 39
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.mcu1Temp / 1 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Item {
        id: batLevelLabel
        x: 230
        y: 784
        width: 100
        height: 100
        Text {
            id: batLev_100
            x: 15
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batLevel / 100 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: batLev_10
            x: 39
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batLevel / 10 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: batLev_1
            x: 70
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.batLevel / 1 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: batLev
            x: 31
            y: 61
            color: "#b4cfe5"
            text: qsTr("电池电量")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }
    }

    Item {
        id: rMcuTempLabel
        x: 389
        y: 784
        width: 100
        height: 100
        Text {
            id: rMcuTemp
            x: 13
            y: 57
            color: "#b4cfe5"
            text: qsTr("发动机温度")
            font.family: "Tensentype ZhiHeiJ-W4"
            font.pixelSize: 15
        }

        Text {
            id: rMcuTemp_10
            x: 15
            y: 5
            width: 38
            height: 62
            color: "#99ccff"
            text: parseInt(carData.rmotorTemp / 10 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: rMcuTemp_1
            x: 39
            y: 5
            width: 45
            height: 62
            color: "#99ccff"
            text: parseInt(carData.rmotorTemp / 1 % 10)
            font.family: "big-numbers"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Text {
        id: gearText
        x: 1605
        y: 310
        width: 54
        height: 51
        color: "#45a0ff"
        text: carData.gearMode == 0 ? "N" : parseInt(carData.gearMode)
        font.pixelSize: 100
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Bold
        font.bold: true
        font.family: "Playfair Display SC Black"
        minimumPointSize: 15
        minimumPixelSize: 20
    }
    //彩蛋对话框提示函数
    function $message(data) {
        if (data && data.show) {
            message.show = data.show
        }
        if (data && data.message) {
            message.text = data.message
        }

        if (data && data.type) {
            message.type = data.type
        }

        if (data && data.type && data.type !== 'success'
                && data.type !== 'error' && data.type !== 'info') {
            return false
        }

        message.openTimer() //调用Message组件下定时器方法
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
