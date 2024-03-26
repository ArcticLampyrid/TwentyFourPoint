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
            placeholderText: "你的名字"
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
                "text": "难度：简单"
            }, {
                "value": 1,
                "text": "难度：中等"
            }, {
                "value": 2,
                "text": "难度：困难"
            }, {
                "value": 3,
                "text": "难度：无尽"
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
                text: "返回"
                onClicked: {
                    ViewUIController.pop();
                }
            }

            Button {
                opacity: 0.9
                width: 60
                height: 30
                text: "确定"
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
