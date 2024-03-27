import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import twenty_four_point

Page {
    function show_result(message) {
        result_bar.text = message;
        result_bar.visible = true;
        result_bar.color = "#ff0000";
        result_bar_timer.stop();
        result_bar_timer.interval = 2000;
        result_bar_timer.repeat = false;
        result_bar_timer.start();
    }

    Component.onCompleted: {
        GameUIController.new_problem();
    }

    Timer {
        id: result_bar_timer

        onTriggered: {
            result_bar.visible = false;
        }
    }

    Column {
        anchors.centerIn: parent
        width: parent.width - 20
        spacing: 10

        Text {
            id: title_bar

            text: qsTr("Dear player '%1', you are playing '%2'").arg(GameUIController.nickname).arg([qsTr("Easy Mode"), qsTr("Medium Mode"), qsTr("Hard Mode"), qsTr("Infinite Mode")][GameUIController.difficulty])
        }

        RowLayout {
            width: parent.width
            height: 30

            Text {
                id: time_elapsed_title

                height: 30
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Time elapsed: ")
            }

            Text {
                height: 30
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 20
                color: "#ff0000"
                text: GameUIController.time_elapsed
            }

            Item {
                Layout.fillWidth: true
                height: 30
            }

            Text {
                height: 30
                Layout.alignment: Qt.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Current score: %1").arg(GameUIController.score)
            }

        }

        Row {
            width: parent.width
            spacing: 10

            Image {
                source: "/twenty_four_point/resources/cards/" + GameUIController.card_colors[0] + "/" + GameUIController.cards[0] + ".png"
                width: (parent.width - 30) / 4
                fillMode: Image.PreserveAspectFit
            }

            Image {
                source: "/twenty_four_point/resources/cards/" + GameUIController.card_colors[1] + "/" + GameUIController.cards[1] + ".png"
                width: (parent.width - 30) / 4
                fillMode: Image.PreserveAspectFit
            }

            Image {
                source: "/twenty_four_point/resources/cards/" + GameUIController.card_colors[2] + "/" + GameUIController.cards[2] + ".png"
                width: (parent.width - 30) / 4
                fillMode: Image.PreserveAspectFit
            }

            Image {
                source: "/twenty_four_point/resources/cards/" + GameUIController.card_colors[3] + "/" + GameUIController.cards[3] + ".png"
                width: (parent.width - 30) / 4
                fillMode: Image.PreserveAspectFit
            }

        }

        RowLayout {
            spacing: 10
            width: parent.width

            TextField {
                id: answer

                opacity: 0.8
                Layout.fillWidth: true
                placeholderText: qsTr("Your answer")
                Keys.onReturnPressed: submit_answer_button.onClicked()
                Keys.onEnterPressed: submit_answer_button.onClicked()
                font.pixelSize: 20
            }

            Button {
                id: submit_answer_button

                opacity: 0.9
                Layout.alignment: Qt.AlignRight
                Layout.fillHeight: true
                implicitWidth: 60
                text: qsTr("Submit")
                onClicked: {
                    if (!submit_answer_button.enabled)
                        return ;

                    submit_answer_button.enabled = false;
                    GameUIController.submit_answer(answer.text);
                    answer.text = "";
                }
            }

        }

        Button {
            anchors.right: parent.right
            opacity: 0.9
            width: 60
            height: 30
            text: qsTr("Back")
            onClicked: {
                GameUIController.finish_game();
                game_finished_dialog.close();
                ViewUIController.pop();
            }
        }

    }

    Text {
        id: result_bar

        width: parent.width
        height: 30
        anchors.bottom: parent.bottom
        z: Infinity
        horizontalAlignment: Text.AlignHCenter
        visible: false
    }

    Connections {
        function onTimeout() {
            show_result(qsTr("Time's up!"));
            let not_finished = GameUIController.new_problem();
            submit_answer_button.enabled = not_finished;
        }

        target: GameUIController
    }

    Connections {
        function onAnswerAccepted() {
            show_result(qsTr("Answer accepted!"));
            let not_finished = GameUIController.new_problem();
            submit_answer_button.enabled = not_finished;
        }

        target: GameUIController
    }

    Connections {
        function onAnswerRejected() {
            show_result(qsTr("Answer rejected!"));
            let not_finished = GameUIController.new_problem();
            submit_answer_button.enabled = not_finished;
        }

        target: GameUIController
    }

    Connections {
        function onGameFinished() {
            game_finished_dialog.open();
        }

        target: GameUIController
    }

    Dialog {
        id: game_finished_dialog

        modal: true
        anchors.centerIn: parent
        closePolicy: Dialog.CloseOnEscape
        onAccepted: {
            game_finished_dialog.close();
            ViewUIController.pop();
        }
        onRejected: {
            game_finished_dialog.close();
            ViewUIController.pop();
            ViewUIController.pop();
        }

        ColumnLayout {
            id: column

            width: parent ? parent.width : 100

            Label {
                text: qsTr("Game finished, your score: %1!").arg(GameUIController.score)
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Do you want another round?")
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight

                Button {
                    text: qsTr("One more round")
                    onClicked: {
                        game_finished_dialog.accept();
                    }
                }

                Button {
                    text: qsTr("Back to main")
                    onClicked: {
                        game_finished_dialog.reject();
                    }
                }

            }

        }

    }

    background: Image {
        source: "/twenty_four_point/resources/background.jpg"
        fillMode: Image.PreserveAspectCrop
    }

}
