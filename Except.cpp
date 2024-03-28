#include "Except.h"

#include <exception>
namespace QApp {
    namespace Except {
      void react() {
        try {
          throw;
        } catch (std::exception &ex){
          //TODO: think about exception and react on them
        }
        catch (...) {
          //TODO: think about exception and react on them
        }
      }
    }// namespace Except
}// namespace QApp
