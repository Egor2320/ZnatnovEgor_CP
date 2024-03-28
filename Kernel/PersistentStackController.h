#include "ActionRequest.h"
#include "PersistentStackModel.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
    namespace Kernel {

        template<typename T>
        class PersistentStackController {
            using ActionData = std::optional<ActionRequest<T>>;
            using Observer = Library::CObserver<ActionData>;

        public:
            PersistentStackController(PersistentStackModel<T>* model) :
                host_(model),
                port_([this](ItemData&& data) { onItemData(std::move(data)); }) {
                assert(host_);
            }

            Observer* get_port() {
                return &port_;
            }

        private:
            void onActionData(ActionData&& data) {
                if (data.has_value()) {
                    onActionRequest(std::move(*data));
                }
            }

            void onActionRequest(ActionRequest<T> request) {
                assert(host_);
                host_->make_action(request);
            }

            PersistentStackModel<T>* model_;
            Observer port_;
        };
    }
}
