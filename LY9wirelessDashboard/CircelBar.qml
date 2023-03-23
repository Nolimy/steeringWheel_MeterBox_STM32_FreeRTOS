import QtQuick 2.12

Rectangle{
    id: contair
    width: 400
    height: 30
    color: "#336699"
    radius: 45
    property var value: 0
    property var maxValue: 100

    Rectangle{
        height: parent.height
        width: (value / maxValue) * (parent.width - parent.height) + parent.height
        radius: 45
        color:"#0099cc"
        Behavior on width {
            NumberAnimation {
                duration: 500
            }
        }
        Text {
            font.pixelSize: 12
            font.family: "微软雅黑"
            color:"#c6d6df"
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            text: Math.round(value / maxValue * 100) + "%"
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked:
            NumberAnimation {
            target: contair
            property: "value"
            to: maxValue
            easing.type: Easing.OutQuart
            duration: 5000
        }
    }
}
