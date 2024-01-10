import QtQuick
import QtQuick.Controls

Window {
    width: 1080
    height: 1920
    visible: true
    title: qsTr("Ma fenêtre")
    Rectangle
    {
        id: rect
        anchors.centerIn: parent
        width: 200
        height: 100
        color: "red"
        Text {
            anchors.centerIn: parent
            color: "yellow"
            text: "Hello, World!"
        }
        Button {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Change la couleur !"
            onClicked: {
                rect.color=Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random())
            }
        }
    }
}
