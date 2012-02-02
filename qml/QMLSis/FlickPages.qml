import QtQuick 1.1
import com.nokia.symbian 1.1

Item {
    id: rootItem
    property alias content: rowCnt.children

    property int currentPageIdx: flick.currentIdx
    property int pageCount: 4

    signal pageChanged()

    Flickable{
        id: flick
        flickableDirection: Flickable.HorizontalFlick

        property int startX: 0
        property int stopX: 0
        property int currentIdx: 0
        property bool wasFlicked: false

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        clip: true
        interactive: true
        flickDeceleration: 4000

        contentWidth: rowCnt.width
        contentHeight: rowCnt.height
        Row{
            id: rowCnt
        }

        Behavior on contentX {
            NumberAnimation {
                id: bouncebehavior
                easing.type: Easing.InOutQuad
            }
        }

        transitions: Transition {
            PropertyAnimation { property: "contentX"; easing.type: Easing.InOutQuart; duration: 300 }
        }

        onMovementStarted:{
            flick.startX = flick.contentX;
            flick.wasFlicked = false;
        }

        onMovementEnded:{
            if(! flick.wasFlicked){
                flick.stopX = flick.contentX;
                flick.currentIdx = Math.round(flick.stopX / rootItem.width);
                moveToIndex();
            }
        }

        onFlickStarted:{
            flick.wasFlicked = true;
            flick.startX = flick.contentX
        }

        onFlickEnded:{
            flick.stopX = flick.contentX;
            if(flick.startX <= rootItem.width * (rootItem.pageCount - 1) && flick.startX > 0){
                if(flick.stopX - flick.startX > 0){
                    flick.currentIdx = Math.ceil(flick.stopX / rootItem.width);
                } else {
                    flick.currentIdx = Math.floor(flick.stopX / rootItem.width);
                }
                flick.currentIdx = Math.round(flick.stopX / rootItem.width);
            }
            if(flick.currentIdx < 0){flick.currentIdx = 0;}
            else if(flick.currentIdx > (rootItem.pageCount - 1)){flick.currentIdx = (rootItem.pageCount - 1);}
            moveToIndex();
        }
    }

    function moveToPrev(){
        flick.currentIdx--;
        if(flick.currentIdx < 0){flick.currentIdx = 0;}
        moveToIndex();
    }

    function moveToNext(){
        flick.currentIdx++;
        if(flick.currentIdx > 3){flick.currentIdx = 3;}
        moveToIndex();
    }

    function moveToPage(idx){
        flick.currentIdx = idx;
        moveToIndex();
    }

    function moveToIndex(){
        flick.contentX = flick.currentIdx * rootItem.width;
        rootItem.pageChanged();
    }
}
