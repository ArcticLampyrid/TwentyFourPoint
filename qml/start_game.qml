import QtQuick
import QtQuick.Controls
import twenty_four_point

Page {
    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {
            id: nickname

            opacity: 0.8
            width: parent.width
            placeholderText: qsTr("Your nickname")
            text: ""
            Component.onCompleted: {
                nickname.text = GameUIController.random_nickname();
            }
        }

        ComboBox {
            id: difficulty

            opacity: 0.8
            textRole: "text"
            valueRole: "value"
            width: parent.width
            model: [{
                "value": 0,
                "text": qsTr("Easy Mode")
            }, {
                "value": 1,
                "text": qsTr("Normal Mode")
            }, {
                "value": 2,
                "text": qsTr("Hard Mode")
            }, {
                "value": 3,
                "text": qsTr("Infinite Mode")
            }]

            delegate: ItemDelegate {
                width: parent.width
                text: modelData.text
                highlighted: ListView.isCurrentItem
            }

        }

        Row {
            spacing: 10

            Button {
                opacity: 0.9
                width: 60
                height: 30
                text: qsTr("Back")
                onClicked: {
                    ViewUIController.pop();
                }
            }

            Button {
                opacity: 0.9
                width: 60
                height: 30
                text: qsTr("OK")
                onClicked: {
                    GameUIController.start_game(nickname.text, difficulty.currentValue);
                }
            }

        }

    }

    background: Image {
        source: "/twenty_four_point/resources/background.jpg"
        fillMode: Image.PreserveAspectCrop
    }

}
