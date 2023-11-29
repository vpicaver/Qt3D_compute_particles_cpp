import QtQuick
import QtQuick.Window
import Qt3D.Core
import Qt3D.Render
import Qt3D.Extras
import QtQuick.Scene3D
import QtQuick.Controls
import QtQuick.Layouts

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

    Rectangle {
        anchors.fill: columnLayoutId
        anchors.margins: -5
    }

    ColumnLayout {
        id: columnLayoutId

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10

        GridLayout {
            columns: 2

            Label {
                text: "step"
            }

            Slider {
                id: stepSlider
                from: 0.1
                to: 1.0
                value: computeMaterial.particleStep
                onMoved: {
                    computeMaterial.particleStep = value
                }
            }

            Label {
                text: "collision factor"
            }

            Slider {
                id: collisionSliderId
                from: 0.1
                to: 1.0
                value: computeMaterial.finalCollisionFactor
                onMoved: {
                    computeMaterial.finalCollisionFactor = value
                }
            }

            Label {
                text: "particles"
            }

            Label {
                text: computeMaterial.particleCount
            }
        }
    }
}
