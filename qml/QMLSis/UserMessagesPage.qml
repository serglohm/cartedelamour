import QtQuick 1.1
import com.nokia.symbian 1.1

Item {
    property alias model: userMessagesModel

    Component{
        id: delegate
        Item{
            height: img.height + 10 + 10
            width: parent.width
            Column{
                anchors.fill: parent
                anchors.margins: 5
                spacing: 8
                Item{
                    id: imgRect
                    width: parent.width
                    height: img.height
                    Image{
                        id: img
                        visible: imgLoaded
                        anchors.centerIn: parent
                        source: imgLoaded ? "image://pushthescreen/" + iid: (qtengine.tryImage(iid) ? "image://pushthescreen/0": "image://pushthescreen/100000")
                    }
                    BusyIndicator {
                            id: indicator
                            anchors.centerIn: parent
                            running: ! imgLoaded
                            width: parent.height - 4
                            height: parent.height - 4
                            visible: ! imgLoaded
                    }
                    Text{
                        id: txt
                        anchors.centerIn: parent
                        text: message
                        color: "#fff"
                    }
                }
                Rectangle{
                    height: 2
                    width: parent.width
                }
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log('Clicked on user: ' + mid + ' ' + iid);
                    qtengine.uploadImage(iid);
                }
            }

        }
    }

    ListModel{
        id: userMessagesModel
    }

    ListView{
        anchors.fill: parent
        delegate: delegate
        model: userMessagesModel
    }

}
