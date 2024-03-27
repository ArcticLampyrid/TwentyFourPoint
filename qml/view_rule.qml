import QtQuick
import QtQuick.Controls
import twenty_four_point

Page {
    ScrollView {
        anchors.fill: parent
        anchors.topMargin: 4
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 48
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        TextArea {
            text: ViewRuleUIController.rule
            wrapMode: Text.WordWrap
            readOnly: true
            font.pixelSize: 16
        }

        background: Rectangle {
            color: "#cccccccc"
        }

    }

    Button {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        opacity: 0.9
        width: 80
        height: 40
        text: qsTr("Back")
        onClicked: {
            ViewUIController.pop();
        }
    }

    background: Image {
        source: "/twenty_four_point/resources/background.jpg"
        fillMode: Image.PreserveAspectCrop
    }

}
