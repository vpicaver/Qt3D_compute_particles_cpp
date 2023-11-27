import QtQuick
import QtQuick.Window
import Qt3D.Core
import Qt3D.Render
import Qt3D.Extras
import QtQuick.Scene3D

Window {

    visible: true
    width: 640
    height: 480

    Scene3D {
        id: sceneId
        anchors.fill: parent
        focus: true
        aspects: ["render", "input", "logic"]
        entity: rootEntity
    }
}
