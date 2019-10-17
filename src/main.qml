import QtQuick 2.0
import QtQuick.Window 2.11
import Qt.labs.platform 1.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Ts2Csv Converter")

    height: 400
    width: 600

    visible: ApplicationWindow.Windowed

    property bool choosingFile: true

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 3
        rows: 2

        Text {
            text: qsTr("Source filename:")
        }

        Text {
            id: sourceInput
            text: ""
        }

        Button {
            text: qsTr("Browse")
            onClicked: {
                choosingFile = true
                fileDialog.open()
            }
        }

        Text {
            text: qsTr("Destination filename:")
        }

        Text {
            id: sourceOutput
            text: ""
        }

        Button {
            text: qsTr("Browse")
            onClicked: {
                choosingFile = false
                fileDialog.open()
            }
        }

        ComboBox {
            id: comboType
            model: ["TS => CSV", "CSV => TS"]
        }

        Item {
            id: dummy
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Convert")
            onClicked: converter.convert(comboType.currentIndex,
                                         sourceInput.text, sourceOutput.text)
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
