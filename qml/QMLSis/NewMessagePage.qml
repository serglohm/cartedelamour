import com.nokia.symbian 1.1
import QtQuick 1.1

Item {
    Column{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: btn.top
        spacing: 10
        Text{color: "#fff"; text: "Текст сообщения"}
        TextInput{color: "#fff"; width: parent.width; }
    }
    Button{
        id: btn
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        text: "Изображение"
    }

}
