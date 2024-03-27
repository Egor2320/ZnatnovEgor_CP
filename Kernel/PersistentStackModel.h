#include "ActionRequest.h"
#include "PersistentStack.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
    namespace Kernel {

        template <typename T>
        class PersistentStackModel {
            using StackData = std::optional<PersistentStack<T>>;
            using ObservableStack = Library::CObservable<StackData>;
            using ObserverStack = Library::CObserver<StackData>;

        public:
            PersistentStackModel() : stack_(std::in_place_t()) {
            }

            void subscribe(ObserverStack* obs) {
                assert(obs);
                port_.subscribe(obs);
            }

            void make_action(ActionRequest<T>& request) {
                if(stack_.has_value()) {
                    stack_->perform_action(request);
                    port_.notify();
                }
            }

        private:
            StackData stack_;
            ObservableStack port_ = [this]() -> const StackData& { return stack_; };
        };
    }// namespace Kernel
}// namespace QApp
