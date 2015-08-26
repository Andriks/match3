import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2


ApplicationWindow {
    title: qsTr("Hello World")
    width: 700
    height: 900
    visible: true

    property int delay: 2000

    //////////////////////////////////////////////////////////////////
    Component {
        id: highlight
        Rectangle {
            height: view.cellHeight
            width: view.cellWidth
            radius: 10
            color: "lightgrey"
        }
    }

    //////////////////////////////////////////////////////////////////
    Transition {
        id: move_animation
        NumberAnimation {
            properties: "x,y"
            duration: 1000 + delay
            easing.type: Easing.OutCirc
        }

        onRunningChanged:
        {
            if (!move_animation.running) {
//                console.log("move stop");
                dataModel.execPackCnt--;
                dataModel.execNextPackage();
            } else {
//                console.log("move start");
                dataModel.execPackCnt++;
            }
        }
    }

    //////////////////////////////////////////////////////////////////
    Transition {
        id: add_animation
        NumberAnimation {
            properties: "y"
            duration: 500 + delay
            easing.type: Easing.OutCirc
        }

        onRunningChanged:
        {
            if (!add_animation.running) {
//                console.log("add stop");
                dataModel.execPackCnt--;
                dataModel.execNextPackage();
            } else {
//                console.log("add start");
                dataModel.execPackCnt++;
            }
        }
    }

    //////////////////////////////////////////////////////////////////

    Rectangle {
        width: parent.height; height: parent.width
        anchors.fill: parent
        anchors.centerIn: parent



        GridView {
            id: view
            objectName: "view"
            model: dataModel

            anchors.fill: parent
            anchors.centerIn: parent
            cellHeight: parent.height / dataModel.height;
            cellWidth: parent.width / dataModel.width;

            interactive: false

            highlight: highlight
            highlightFollowsCurrentItem: true

            move: move_animation
            add:add_animation


            delegate: Item {
                property var view: GridView.view

                height: view.cellHeight
                width: view.cellWidth

                Rectangle {
                    id: tile_

                    anchors.margins: 5
                    radius: 15
                    anchors.fill: parent


//                    Image {
//                        height: view.cellHeight
//                        width: view.cellWidth

//                        anchors.fill: parent
//                        source: model.type
////                        opacity: model.opacity
//                    }
                    color: model.color
                    opacity: model.opacity

                    Behavior on opacity {
                        NumberAnimation {
                            id: opacity_animation
                            duration: 500 + delay

                            onRunningChanged:
                            {
                                if (!opacity_animation.running) {
//                                    console.log("op stop");
                                    dataModel.execPackCnt--;
                                    dataModel.execNextPackage();
                                } else {
//                                    console.log("op start");
                                    dataModel.execPackCnt++;
                                }
                            }
                        }
                    }

                    Text {
                        x: 10; y: 10
                        text: "%1".arg(model.index)
                    }

                    Text {
                        anchors.centerIn: parent
                        text: model.text
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked:
                        {
                            view.currentIndex = model.index;
                            dataModel.moveTile(model.index);
                        }
                    }
                }
            }
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("some slot")
                onTriggered: dataModel.someSlot();
            }
            MenuItem {
                text: qsTr("rem matches")
                onTriggered: dataModel.createPackages();
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
