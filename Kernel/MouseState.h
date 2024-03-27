#include <QPointF>

namespace QApp {
    namespace Kernel {

        enum class MouseStatus { Pressed, Moved, Released };

        struct MouseState {
            MouseStatus status;
            QPointF position;
        };

    } // namespace Kernel
} // namespace QApp
