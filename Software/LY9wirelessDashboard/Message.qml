
import QtQuick 2.0

Item {
    id: messageBox
    width: msgBox.width
    y: 50
    z:2
    anchors {
        horizontalCenter: parent.horizontalCenter
    }
    //提示框内容
    property alias text: msg.text
    property bool show: false
    property var type: "info"
    visible: show
    //执行定时器
    function openTimer() {
        timerId.start()
        messageBox.y = 80
    }
    Behavior on y {
        NumberAnimation {
            duration: 200
        }
    }
    Timer {
        id: timerId
        interval: 1000
        repeat: false
        onTriggered: {

            messageBox.y = 200
             timerHide.start()
        }
    }
    Timer {
        id: timerHide
        interval: 100
        repeat: false
        onTriggered: {
            show = false
        }
    }
    //$Utils.boxWidth封装的一个函数 计算元素的宽度  自身宽度+leftMargin+rightMargin
    Rectangle {
        id: msgBox
        clip: true
        width:200
        /* {

            if ($Utils.boxWidth(img) + $Utils.boxWidth(msg) < 300
                    || $Utils.boxWidth(img) + $Utils.boxWidth(msg) === 300)
                return 300
            else
                return $Utils.boxWidth(img) + $Utils.boxWidth(msg) >
                            600 ? 600 : $Utils.boxWidth(
                                       img) + $Utils.boxWidth(msg) + 15

        }*/
        height: 50
         color:  type=== "info" ? "#fdf6ec" : type=== "success" ? "#f0f9eb" : "#fef0f0"
        border.color:type=== "info" ? "#faecd8" : type=== "success" ? "#e1f3d8" : "#fde2e2"
        radius: 5

        Image {
            id: img
            //source: type
            //        === "info" ? "qrc:/images/remind.png" : type
            //                     === "success" ? "qrc:/images/true.png" : "qrc:/images/error.png"
            width: 24
            height: 24
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 15
            }
        }
        Text {
            id: msg
            color: type=== "info" ? "#e6a23c" : type=== "success" ? "#67c23a" : "#f56c6c"
            font.pixelSize: 16
            anchors {
                verticalCenter: img.verticalCenter
                left: img.right
                leftMargin: 10
            }
        }
    }
}
