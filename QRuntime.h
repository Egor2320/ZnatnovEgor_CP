#include <QObject>
#include <QApplication>

namespace QApp {
    class QRuntime : public QApplication {
    public:
        QRuntime(int argc, char** argv);
    private:
        bool eventFilter(QObject* obj, QEvent* event) override;
    };
}// namespace QApp
