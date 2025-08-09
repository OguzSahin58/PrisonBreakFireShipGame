import QtQuick 2.15

Item
{

    property var ePng:[
        "qrc:/enemy/enemy1",
        "qrc:/enemy/enemy2",
        "qrc:/enemy/enemy3",
        "qrc:/enemy/enemy4",
        "qrc:/enemy/enemy5",
    ]

    property int eIndex: 0

    id: enemy1
    width: 50
    height: 50
    x: model.x
    y: model.y

    Image
    {
        id:enemies
        anchors.fill:parent
        source: ePng[model.mIndex]
    }
}
