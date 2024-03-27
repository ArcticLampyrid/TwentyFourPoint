import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtQuick.Window
import twenty_four_point

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("24-Point Game")

    Item {
        anchors.fill: parent

        StackView {
            id: view

            anchors.fill: parent
            Component.onCompleted: {
                view.push("qrc:/twenty_four_point/qml/menu.qml");
            }
        }

    }

    Connections {
        function onPagePushed(page) {
            view.push(page);
        }

        target: ViewUIController
    }

    Connections {
        function onPagePopped() {
            view.pop();
        }

        target: ViewUIController
    }

    palette: Palette {
        alternateBase: "#fff"
        base: "#fff"
        button: "#eee"
        buttonText: "#000"
        dark: "#999"
        highlight: "#38c"
        highlightedText: "#fff"
        light: "#fff"
        mid: "#bbb"
        midlight: "#ccc"
        placeholderText: "#80000000"
        shadow: "#777"
        text: "#000"
        window: "#eee"
        windowText: "#000"
    }

}
