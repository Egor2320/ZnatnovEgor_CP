#include <memory>

namespace QApp{

    class ApplicationImplementation;

    class Application {
    public:
        Application();
        ~Application();

    private:
        std::unique_ptr<ApplicationImplementation> _implementation;
    };
}// namespace QApp

