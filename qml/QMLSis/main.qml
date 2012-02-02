import QtQuick 1.1
import com.nokia.symbian 1.1

import "code.js" as Code
import "engine.js" as Engine

PageStackWindow {
    id: rootWindow
    function engineViewUserMessages(puid, page){
        Engine.engineViewUserMessages(puid, page);
    }

    initialPage: MainPage {
        id: mainPage
        tools: toolBarLayout
        onPageChanged: {
            nextButton.enabled = true;
            nextButton.opacity = 1;
            prevButton.enabled = true;
            prevButton.opacity = 1;
            if(pages.currentPageIdx == 0){
                prevButton.enabled = false;
                prevButton.opacity = 0.5;
            } else if(pages.currentPageIdx == pages.pageCount - 1){
                nextButton.enabled = false;
                nextButton.opacity = 0.5;
            }
        }
    }
    showStatusBar: true
    showToolBar: true


    Component.onCompleted: {
        Engine.login();
        console.log(mainPage.content0);
    }

    ToolBarLayout {
        id: toolBarLayout
        ToolButton {
            flat: true
            iconSource: "toolbar-back"
            onClicked: window.pageStack.depth <= 1 ? Qt.quit() : window.pageStack.pop()
        }

        ToolButton {
            id: prevButton
            flat: true
            iconSource: "toolbar-previous"
            onClicked: {
                mainPage.pages.moveToPrev();
            }
        }
        ToolButton {
            id: nextButton
            flat: true
            iconSource: "toolbar-next"
            onClicked: {
                mainPage.pages.moveToNext();
            }
        }
    }
}
