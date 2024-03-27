#include "QRuntime.h"
#include "QPort.h"

namespace QApp {
    QRuntime::QRuntime(int argc, char** argv) : QApplication(argc, argv) {
        installEventFilter(this);
    }

    bool QRuntime::eventFilter(QObject* obj, QEvent *event) {
        using Message = Library::Message;
        if(event->type() == Message::type()) {
            Message* msg = static_cast<Message*>(event);
            if(msg->is_alive()) {
                msg->receiver()->event(event);
            }
            return true;
        }
        return QApplication::eventFilter(obj, event);
    }
}// namespace QApp
