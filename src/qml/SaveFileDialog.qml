import QtQuick 2.12
import Qt.labs.platform 1.1

Item {
    property bool selectFolder: false

    signal ok(string path)

    onVisibleChanged: {
        if (!visible) {
            return
        }

        if (selectFolder) {
            dialogLoader.sourceComponent = componentFolderDialog
        } else {
            dialogLoader.sourceComponent = componentFileDialog
        }

        dialogLoader.item.open()
    }

    Loader {
        id: dialogLoader

        anchors.fill: parent
    }

    Component {
        id: componentFileDialog

        FileDialog {
            title: qsTr("Select File")
            fileMode: FileDialog.SaveFile
            onAccepted: ok(file)
        }
    }

    Component {
        id: componentFolderDialog

        FolderDialog {
            folder: StandardPaths.standardLocations(
                        StandardPaths.DocumentsLocation)[0]
            onAccepted: ok(currentFolder)
        }
    }
}
