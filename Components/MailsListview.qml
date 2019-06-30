import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQml.Models 2.3

import MailsModel 1.0

ListView {
    Connections {
        target: selectionModel
        onSelectionChanged: {
            if (!selected.toString())
                listView.currentIndex = -1
        }
    }

    id: listView
    model: mailsModel
    width: parent.width
    height: parent.height

    spacing:  4

    ScrollBar.vertical: ScrollBar {} // enable scrollbar

    delegate: Rectangle {
        property bool hovered: false
        id: emailDelegate
        height: 60
        width: listView.width
        color: ListView.isCurrentItem ? "lightsteelblue" : (hovered ? "lightgray" : "white") // highlights current item

        Behavior on color {
            ColorAnimation{
                duration: 200
            }
        }

        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;

            onEntered: emailDelegate.hovered = true
            onExited: emailDelegate.hovered = false
            onClicked: {
                listView.currentIndex = index
                selectionModel.setCurrentIndex(mailsModel.index(index, 0),
                                               ItemSelectionModel.Current
                                               | ItemSelectionModel.Select
                                               | ItemSelectionModel.Rows)
            }
        }

        Column{
            spacing: 5
            Text {
                text: "From: " + cFrom
                width: listView.width - 10
                height: 10
                leftPadding: 10
                elide: Text.ElideRight
            }
            Text {
                text: "Subject: " + cSubject
                width: listView.width - 10
                height: 10
                leftPadding: 10
                elide: Text.ElideRight
            }
            Text {
                text: cAnno
                width: listView.width - 10
                height: 30
                leftPadding: 10
                elide: Text.ElideRight
                wrapMode: Text.Wrap
                color: "darkgray"
            }
        }
    }

//    highlight: Component {
//        id: highlight;
//        Rectangle {
//            z: 100
//            width: listView.width;
//            height: 60;
//            color: "lightsteelblue";
//            opacity: 0.3;
//            radius: 5;
//            y: listView.currentItem.y;
//            Behavior on y {
//                SpringAnimation {
//                    spring: 1;
//                    damping: 0.2;
//                }
//            }
//        }
//    }

}

