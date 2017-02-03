#include "sources/core/SDLBackend/SDLEngine.h"
#include "sources/GameDelegate.h"

using namespace csd;

int main() {
    csd::GameDelegate& delegate = csd::GameDelegate::sharedInstance();

    delegate.init(std::shared_ptr<csd::GameEngineInterface>(new csd::SDLEngine()));

    return delegate.start();
}