import QtQuick 2.8
import QtQuick.Window 2.2

import "Components" as MyComponents

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function fun() {
        mailsListView.clearSelection()
    }

    MyComponents.MailsListview {
        id: mailsListView
    }
}
