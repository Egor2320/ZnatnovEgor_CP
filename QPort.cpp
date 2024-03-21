#include "QPort.h"

#include <QApplication>

namespace QApp {
    namespace Library {

        QEvent::Type Message::type() {
            static int msg_type = registerEventType();
            assert(msg_type >= QEvent::User && msg_type <= QEvent::MaxUser);
            return QEvent::Type(msg_type);
        }

        Message::Message(QObject* addr, const std::any& data)
            : QEvent(type()), addr_(addr), data_(data) {
        }

        Message::Message(QObject* addr, std::any&& data)
            : QEvent(type()), addr_(addr), data_(std::move(data)){
        }

        std::any&& Message::extract() {
            return std::move(data_);
        }

        bool Message::is_alive() const {
            return addr_;
        }

        QObject* Message::receiver() const {
            return addr_;
        }

        void QSender::send(QObject *receiver, std::any data) const {
            QCoreApplication::postEvent(QCoreApplication::instance(),
                                        new Message(receiver, std::move(data)));
        }

        bool QReceiver::event(QEvent* event) {
            if (event->type() == Message::type()) {
                Message* msg = static_cast<Message*>(event);
                action(msg->extract());
                return k_is_processed;
            }
            return QObject::event(event);
        }
    }// namespace Library
}// namespace QApp
