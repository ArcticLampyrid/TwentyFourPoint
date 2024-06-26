import QtQuick
import QtQuick.Controls
import twenty_four_point

Page {
    Column {
        anchors.centerIn: parent
        spacing: 10

        Button {
            opacity: 0.9
            width: 160
            height: 80
            text: qsTr("Start")
            onClicked: {
                MenuUIController.start();
            }
        }

        Button {
            opacity: 0.9
            width: 160
            height: 80
            text: qsTr("Rank")
            onClicked: {
                MenuUIController.view_rank_list();
            }
        }

        Button {
            opacity: 0.9
            width: 160
            height: 80
            text: qsTr("Rule")
            onClicked: {
                MenuUIController.view_rule();
            }
        }

        Button {
            opacity: 0.9
            width: 160
            height: 80
            text: qsTr("Quit")
            onClicked: {
                MenuUIController.quit_game();
            }
        }

    }

    background: Image {
        source: "/twenty_four_point/resources/background.jpg"
        fillMode: Image.PreserveAspectCrop
    }

}
