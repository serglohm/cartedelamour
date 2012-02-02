import QtQuick 1.1
import com.nokia.symbian 1.1
import QtMultimediaKit 1.1

Page {
    id: rootPage
    property int pageId: 0
    property alias pages: pages
    property alias content0: mainRect
    property alias usersModel: usersModel
    property alias debugText: debugText.text
    property alias userMessagesModel: userMessagesPage.model

    signal pageChanged()

    FlickPages{
        id: pages
        anchors.fill: parent
        onPageChanged: {
            rootPage.pageChanged();
        }

        content: [
            Item{
                id: mainRect
                width: rootPage.width
                height: rootPage.height

                Component{
                    id: delegate
                    Item{
                        height: txt.height + 10 + 10
                        width: parent.width
                        Column{
                            anchors.fill: parent
                            spacing: 8
                            Text{
                                id: txt
                                width: parent.width
                                text: name
                                color: "#fff"
                            }
                            Rectangle{
                                height: 2
                                width: parent.width
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                console.log('Clicked on user: ' + puid);
                                userMessagesModel.clear();
                                pages.moveToPage(2);
                                rootWindow.engineViewUserMessages(puid, 0);
                            }
                        }

                    }
                }

                ListModel{
                    id: usersModel
                }

                ListView{
                    anchors.fill: parent
                    anchors.margins: 10
                    delegate: delegate
                    model: usersModel
                }
            },
            Item{
                id: secondRect
                width: rootPage.width
                height: rootPage.height

                Button{
                    id: testBtn
                    anchors.margins: 10
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: "upload image"
                    onClicked: {
                        qtengine.uploadImage(282);
                    }
                }
                Text{
                    id: debugText
                    anchors.margins: 10
                    height: 40
                    anchors.top: testBtn.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: "..."
                    color: "#fff"
                }
                Camera{
                    id: camera
                    anchors.margins: 10
                    anchors.top: debugText.bottom
                    height: 240
                    width: 320
                    focus: visible
                    onImageCaptured: {
                        console.log(preview);
                        prewImg.source = preview;
                        prewImg.visible = true;
                        camera.visible = false;
                        captureBtn.visible = false;
                        uploadBtn.visible = true;
                    }
                }

                Image{
                    id: prewImg
                    visible: false
                    anchors.margins: 10
                    anchors.top: debugText.bottom
                    height: 240
                    width: 320
                }

                Button{
                    id: captureBtn
                    text: "capture"
                    anchors.top: camera.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    onClicked: {
                        camera.captureImage();
                    }
                }
                Button{
                    id: uploadBtn
                    text: "upload"
                    visible: false
                    anchors.top: camera.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    onClicked: {
                        qtengine.getCameraPreview(prewImg.source, 12, "test message");
                    }
                }

            },
            Item{
                width: pages.width
                height: pages.height
                UserMessagesPage{
                    id: userMessagesPage
                    anchors.margins: 10
                    anchors.fill: parent
                }
            },
            Item{
                width: pages.width
                height: pages.height
                NewMessagePage{
                    id: messagePage
                    anchors.margins: 10
                    anchors.fill: parent
                }
            },
            Item{
                width: pages.width
                height: pages.height

                RegisterUserPage{
                    id: registerUserPage
                    anchors.margins: 10
                    anchors.fill: parent
                }
            }

        ]
    }

    Component.onCompleted: {
        //getPage();
    }

    function getPage(){
        var auth = make_base_auth('developer', 'ess+kiD!cuR84');
        var url = 'http://stage.weclever.ru/iphone_app/AppDataActionsPages/1/5/' + pageId;
        getJSON(url, wecleverCallback, auth);
        console.log(url);
        pageId++;
    }

    function wecleverCallback(data){
        for(var i = 0; i < data.length; i++){
            var el = data[i];
            model.append(el);
        }
        if(pageId < 10)
            getPage();
    }
}
