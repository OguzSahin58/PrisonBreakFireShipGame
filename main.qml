import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts

Window {
    width: 1920
    height: 1000
    visible: true
    title: qsTr("Prison Break Fire Ship")

    FontLoader
    {
        id: pMedium
        source: "qrc:/fonts/stellar.otf"
    }

    Rectangle
    {
        id: gameArea
        anchors.fill: parent
        visible: true
        gradient: Gradient
        {
        GradientStop { position: 0.0; color: "blue" }
        GradientStop { position: 1; color: "black"}
        }

        Rectangle
        {
            id: gameOverOverlay
            anchors.fill: parent
            visible: false
            color:"Black"
            opacity: 0.8
            z: 1001

            ColumnLayout
            {
                anchors.centerIn: parent
                spacing: 30
                Text
                {
                    id: gameOver
                    text: "Game Over\n "+ scoreBoard.text;
                    font.family: pMedium.font.family
                    font.weight: pMedium.font.weight
                    font.styleName: pMedium.font.styleName
                    font.pixelSize: 60
                    color:"white"                   
                    Layout.alignment: Qt.AlignHCenter

                }

                RowLayout
                {
                    spacing: 20
                    Rectangle
                    {
                        id: closeButton
                        Layout.preferredWidth: 300
                        Layout.preferredHeight: 35
                        color: "gray"
                        radius: 20
                        Text
                            {
                            text: "Close"
                            color: "white"
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: pMedium.font.styleName
                            font.pixelSize: 30
                            anchors.centerIn: parent

                            }
                        MouseArea
                        {
                            hoverEnabled: true
                            anchors.fill: parent
                            onEntered:
                            {
                                closeButton.color = "red"
                            }
                            onExited:
                            {
                                closeButton.color = "grey"
                            }

                            onClicked:
                            {
                                Qt.quit();
                            }
                        }
                    }
                    Rectangle
                    {
                        id: restartButton
                        width: 300
                        height: 35
                        color: "gray"
                        radius: 20
                        Text
                            {
                            text: "Restart"
                            color: "white"
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: pMedium.font.styleName
                            font.pixelSize: 30
                            anchors.centerIn: parent
                            }
                        MouseArea
                        {
                            hoverEnabled: true
                            anchors.fill: parent
                            onEntered:
                            {
                                restartButton.color = "green"
                            }
                            onExited:
                            {
                                restartButton.color = "grey"
                            }

                            onClicked:
                            {
                                control.restartGame();
                                gameOverOverlay.visible = false;
                            }
                        }
                    }

                }
            }

        }
        Connections
        {
            target: control
            function onGameOver() {
                    gameOverOverlay.visible = true;
                }
        }

        Rectangle
        {
            id: move
            width: 50
            height: 50
            color: 'Transparent'
            x: control.x
            y: control.y
            focus: true

            Image
            {
                id: scofield
                source: "qrc:/player/scofield.png"
                width: 55
                height: 55
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top:parent.top
            }

            AnimatedImage
            {
                id: thruster
                source: "qrc:/player/thruster.gif"
                width: 30
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top:scofield.bottom
            }

            Keys.onPressed: (event) =>
                          {
                                if(event.key === Qt.Key_Left)
                                {
                                    control.moveLeft();
                                }
                                if(event.key === Qt.Key_Right)
                                {
                                    control.moveRight();
                                }
                                if(event.key === Qt.Key_Up)
                                {
                                    control.applyThrust();
                                }
                                if(event.key === Qt.Key_Space)
                                {
                                    control.fireBullet();
                                }
                                thruster.playing = true

                          }
            Keys.onReleased: (event)=>
                             {
                                 if(event.key === Qt.Key_Left || event.key === Qt.Key_Right)
                                 {
                                     control.stopMovement();
                                 }
                                 thruster.playing = true

                             }

            Component.onCompleted:
            {
                move.forceActiveFocus();
                thruster.playing = true;
            }

        }

        Text
        {
            id: scoreBoard
            text: "Score: " + control.showScore()
            font.family: pMedium.font.family
            font.weight: pMedium.font.weight
            font.styleName: pMedium.font.styleName
            font.pixelSize: 40
            color: "white"
            x: 50
            y: 50

            Connections
            {
                target: control
                function onScoreChanged()
                {
                    scoreBoard.text = "Score: "+ control.showScore()
                }
            }
        }

        Repeater
        {
            model: control.bullets
            delegate: Bullet{}
        }
        Repeater
        {
            model: control.enemies
            delegate: Enemy{}
        }
    }




}
