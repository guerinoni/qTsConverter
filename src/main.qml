import QtQuick 2.0
import QtQuick.Window 2.11
import Qt.labs.platform 1.0
import Qt.labs.settings 1.0
import QtQuick.Controls 2.7
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.0

Window {
    title: qsTr("Ts2Csv Converter ") + version

    minimumHeight: 220
    minimumWidth: 800

    height: minimumHeight
    width: minimumWidth

    visible: ApplicationWindow.Windowed

    property bool choosingFile: true
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
                    choosingFile = true
                    fileDialog.folder = settings.lastSourceInput
                    fileDialog.open()
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
                    choosingFile = false
                    fileDialog.folder = settings.lastSourceOutput
                    fileDialog.open()
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
                messageDialog.visible = true
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: choosingFile ? qsTr("Select File") : qsTr("Select Folder")
        nameFilters: []
        selectFolder: !choosingFile

        onAccepted: {
            if (choosingFile) {
                sourceInput.text = fileDialog.fileUrl
                var str = fileDialog.fileUrl.toString()
                settings.lastSourceInput =  str.substring(0, str.lastIndexOf("/"))
            } else {
                sourceOutput.text = fileDialog.fileUrl
                settings.lastSourceOutput =  fileDialog.fileUrl
            }
        }
    }

    Dialog {
        id: messageDialog
        visible: false
        title: converter.convSuccessfull ? "Conversion completed" : "Conversion failed"
        contentItem: Rectangle {
            implicitWidth: 400
            implicitHeight: 150
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 40

                Text {
                    text: converter.convMsg
                    Layout.alignment: Qt.AlignHCenter
                    color: Material.color(Material.Grey)
                    font.pointSize: 16
                }

                Text {
                    text: converter.detailedConvMsg
                     Layout.alignment: Qt.AlignHCenter
                     color: Material.color(Material.BlueGrey)
                }

                Button {
                    text: qsTr("Ok!")
                    onClicked: messageDialog.close()
                    highlighted: true
                    Material.background: Material.Orange
                    Layout.fillWidth: true
                }
            }
        }

        onAccepted: {
            visible = false
        }
    }
}
