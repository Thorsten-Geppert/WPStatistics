import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Script.js" as Scripts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("WPStatistics")
    
    Component.onCompleted: Scripts.loadData()
    
    Rectangle {
        id: headlineRectangle
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        
        color: "#038cfc"
        implicitHeight: headlineLabel.height + 40
        
        Label {
            id: headlineLabel
            text: "Statistics"
            anchors.centerIn: parent
            color: "#ffffff"
            font.pointSize: 20
            font.weight: Font.Bold
        }
        
        Button {
            id: refreshButton
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Refresh")
            onClicked: Scripts.loadData()
        }
    }
    
    Component {
        id: entryComponent
        
        Rectangle {
            width: entriesListView.width
            implicitHeight: titleLabel.height
            
            RowLayout {
                anchors.fill: parent
            
                Label {
                    id: titleLabel
                    text: title
                    wrapMode: Text.Wrap
                    Layout.fillWidth: true
                }
                
                Label {
                    id: counterLabel
                    text: counter
                }
            }
        }
    }
    
    ListView {
        id: entriesListView
        
        model: ListModel {
            id: entriesListModel
        }
        
        delegate: entryComponent
        
        anchors {
            top: headlineRectangle.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 20
        }
    }
    
     Popup {
        id: errorPopup
        anchors.centerIn: parent        
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        
        Label {
            text: qsTr("Could not load data")
        }
    }
}
