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
        clip: true

        ListView {
            model: RankListModel

            delegate: Item {
                width: parent.width
                height: 50

                Row {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 16

                    Text {
                        anchors.left: parent.left
                        height: parent.height
                        text: "#" + (index + 1) + '  ' + model.nickname
                        verticalAlignment: Text.AlignVCenter
                    }

                    Text {
                        anchors.right: parent.right
                        anchors.rightMargin: 4
                        height: parent.height
                        text: model.score
                        verticalAlignment: Text.AlignVCenter
                    }

                }

                Rectangle {
                    color: "#88000000"
                    height: 1
                    width: parent.width
                    anchors.bottom: parent.bottom
                }

            }

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
