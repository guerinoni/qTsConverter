import QtQuick 2.0
import QtQuick.Window 2.11
import QtQuick.Controls 2.7
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.0

import Qt.labs.platform 1.1
import Qt.labs.settings 1.0

Window {
    title: qsTr("Ts2Csv Converter ") + version

    minimumHeight: 220
    minimumWidth: 800

    height: minimumHeight
    width: minimumWidth

    visible: ApplicationWindow.Windowed

    readonly property bool isCsvFormat: comboType.currentIndex === 0
                                        || comboType.currentIndex === 1

    Settings {
        id: settings
        property string lastSourceInput
        property string lastSourceOutput
    }

    GridLayout {
        anchors {
            fill: parent
            margins: 20
        }

        columns: 1
        rows: 3

        RowLayout {

            Text {
                text: qsTr("Source filename:")
            }

            Text {
                id: sourceInput
                color: Material.color(Material.Grey)
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Browse")
                highlighted: true
                onClicked: {
                    loadFileDialog.folder = settings.lastSourceInput
                    loadFileDialog.open()
                }
            }
        }

        RowLayout {

            Text {
                text: qsTr("Destination folder:")
            }

            Text {
                id: sourceOutput
                color: Material.color(Material.Grey)
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Browse")
                highlighted: true
                onClicked: {
                    saveFileDialog.folder = settings.lastSourceOutput
                    saveFileDialog.open()
                }
            }
        }

        RowLayout {
            spacing: 20
            ComboBox {
                id: comboType
                model: ["TS => CSV", "CSV => TS", "TS => XLSX", "XLSX => TS"]
            }

            Text {
                text: qsTr("Field separator:")
                visible: isCsvFormat
            }

            Rectangle {
                visible: isCsvFormat
                border.width: 0.5
                border.color: "black"
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
                visible: isCsvFormat
            }

            Rectangle {
                visible: isCsvFormat
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
            highlighted: true
            Material.background: Material.Orange
            enabled: sourceInput.text.length !== 0
                     && sourceOutput.text.length !== 0
                     && fieldSeparator.text.length !== 0
                     && stringSeparator.text.length !== 0
            onClicked: {
                converter.convert(comboType.currentIndex, sourceInput.text,
                                  sourceOutput.text, fieldSeparator.text,
                                  stringSeparator.text)
                finishDialog.visible = true
            }
        }
    }

    LoadFileDialog {
        id: loadFileDialog
        objectName: "loadFileDialog"

        onAccepted: sourceInput.text = loadFileDialog.file
    }

    SaveFileDialog {
        id: saveFileDialog
        objectName: "saveFileDialog"

        onAccepted: sourceOutput.text = saveFileDialog.file
    }

    FinishDialog {
        id: finishDialog
        objectName: "finishDialog"

        onAccepted: visible = false
    }
}
