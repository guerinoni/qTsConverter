import QtQuick 2.0
import QtQuick.Window 2.11
import Qt.labs.platform 1.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Window {
    title: qsTr("Ts2Csv Converter ") + version

    minimumHeight: 200
    minimumWidth: 800

    height: minimumHeight
    width: minimumWidth

    visible: ApplicationWindow.Windowed

    property bool choosingFile: true

    GridLayout {
        anchors {
            fill: parent
            margins: 10
        }

        columns: 1
        rows: 3

        RowLayout {

            Text {
                text: qsTr("Source filename:")
            }

            Text {
                id: sourceInput
                Layout.fillWidth: true
                text: ""
            }

            Button {
                text: qsTr("Browse")
                onClicked: {
                    choosingFile = true
                    fileDialog.open()
                }
            }
        }

        RowLayout {

            Text {
                text: qsTr("Destination filename:")
            }

            Text {
                id: sourceOutput
                Layout.fillWidth: true
                text: ""
            }

            Button {
                text: qsTr("Browse")
                onClicked: {
                    choosingFile = false
                    fileDialog.open()
                }
            }
        }

        RowLayout {

            ComboBox {
                id: comboType
                model: ["TS => CSV", "CSV => TS"]
            }

            Text {
                text: qsTr("Field separator:")
            }

            Rectangle {
                border.width: 0.5
                border.color: "black"
                color: "transparent"
                width: 30
                height: 30

                TextInput {
                    id: fieldSeparator
                    text: ";"
                    anchors.centerIn: parent
                }
            }

            Text {
                text: qsTr("String separator:")
            }

            Rectangle {
                border.width: 0.5
                border.color: "black"
                color: "transparent"
                width: 30
                height: 30

                TextInput {
                    id: stringSeparator
                    text: "\""
                    anchors.centerIn: parent
                }
            }
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Convert")
            enabled: sourceInput.text.length !== 0
                     && sourceOutput.text.length !== 0
                     && fieldSeparator.text.length !== 0
                     && stringSeparator.text.length !== 0
            onClicked: converter.convert(comboType.currentIndex,
                                         sourceInput.text, sourceOutput.text,
                                         fieldSeparator.text,
                                         stringSeparator.text)
        }
    }

    FileDialog {
        id: fileDialog
        title: choosingFile ? qsTr("Select File") : qsTr("Select Folder")
        nameFilters: []
        selectFolder: !choosingFile
        folder: StandardPaths.standardLocations(
                    StandardPaths.DesktopLocation)[0]

        onAccepted: {
            if (choosingFile) {
                sourceInput.text = fileDialog.fileUrl
            } else {
                sourceOutput.text = fileDialog.fileUrl
            }
        }
    }
}
