#pragma once

/*
 * Implementation of Observer Pattern for Qt is based
 * on project of Dmitry Trushin: https://github.com/DimaTrushin/InteractiveGUI.git
 */

#include <QObject>
#include <QEvent>
#include <QPointer>

#include <any>

namespace QApp{
    namespace Library {

        class Message : public QEvent {
        public:
            Message(QObject* addr, const std::any& data);
            Message(QObject* addr, std::any&& data);

            std::any&& extract();
            QObject* receiver() const;
            bool is_alive() const;


            static QEvent::Type type();

        private:
            QPointer <QObject> addr_;
            std::any data_;
        };

        class QSender : public QObject {
            Q_OBJECT
            using Message = Message;

        public:
            void send(QObject* receiver, std::any data) const;
        };

        class QReceiver : public QObject {
            Q_OBJECT
            using Message = Message;

        public:
            bool event(QEvent* event) override;

        protected:
            virtual void action(std::any&& data) = 0;

        private:
            static constexpr bool k_is_processed = true;
        };


    }// namespace Library
}// namespace QApp

