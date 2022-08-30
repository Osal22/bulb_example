import  QtQuick 2.12
import  QtQuick.Controls 1.0
import  QtQuick.Window 2.12


Item {
    id: timeText
    color: timeText.color
    font.pixelSize: Theme.fontSizeHuge * 2.0
    text: { 
        updatesEnabled: timeText.time  <--------add line here
        Qt.formatTime(new Date(), "hh:mm:ss")
    }
    anchors {
        horizontalCenter: parent.horizontalCenter
    }
}
