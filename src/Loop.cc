#include "native/Loop.hh"
#include "native/helper/trace.h"

#include <memory>
#include <map>
#include <thread>

namespace {
    typedef std::map<uv_loop_t*, std::thread::id> LoopMapType;
    LoopMapType _loopMap;

    void deregisterLoop(uv_loop_t *iLoopPtr) {
        for(LoopMapType::iterator it = _loopMap.begin(); it != _loopMap.end(); ++it) {
            if(it->first == iLoopPtr) {
                _loopMap.erase(it);
                return;
            }
        }
    }

    void registerLoop(std::shared_ptr<uv_loop_t> iLoop) {
        deregisterLoop(iLoop.get());
        _loopMap[iLoop.get()] = std::this_thread::get_id();
    }
}

namespace native {

bool isOnEventloopThread(std::shared_ptr<uv_loop_t> iLoop) {
    LoopMapType::iterator it = _loopMap.find(iLoop.get());
    return ((it == _loopMap.end()) || (it->second == std::this_thread::get_id()));
}

Loop::Loop(bool use_default) {
    NNATIVE_FCALL();
    if(use_default) {
        static std::weak_ptr<uv_loop_t> savedPtr;

        if(!savedPtr.expired()) {
            _uv_loop = savedPtr.lock();
            return;
        }

        // don't delete the default Loop
        _uv_loop = std::shared_ptr<uv_loop_t>(uv_default_loop(), [](uv_loop_t* iLoop){
                NNATIVE_DEBUG("destroying default Loop...");
                deregisterLoop(iLoop);
                int res = 1;
                do {
                    res = uv_loop_close(iLoop);
                } while (res != 0);
            });

        if(0 != uv_loop_init(_uv_loop.get())) {
            NNATIVE_DEBUG("error to init Loop " << (_uv_loop.get()));
            _uv_loop.reset();
        }

        savedPtr = _uv_loop;
    } else {
        std::unique_ptr<uv_loop_t> loopInstance(new uv_loop_t);
        if(0 == uv_loop_init(loopInstance.get())) {
            _uv_loop = std::shared_ptr<uv_loop_t>(loopInstance.release(), [](uv_loop_t* iLoop){
                    NNATIVE_DEBUG("destroying specified Loop..");
                    deregisterLoop(iLoop);
                    int res = 1;
                    do {
                        res = uv_loop_close(iLoop);
                    } while (res != 0);
                    delete iLoop;
                });
        }
    }
}

Loop::~Loop()
{
    NNATIVE_FCALL();
}

bool Loop::run() {
    NNATIVE_FCALL();
    NNATIVE_ASSERT(_uv_loop);
    registerLoop(_uv_loop);
    return (uv_run(_uv_loop.get(), UV_RUN_DEFAULT) == 0);
}

bool Loop::run_once() {
    NNATIVE_FCALL();
    NNATIVE_ASSERT(_uv_loop);
    registerLoop(_uv_loop);
    return (uv_run(_uv_loop.get(), UV_RUN_ONCE) == 0);
}

bool Loop::run_nowait()
{
    registerLoop(_uv_loop);
    return (uv_run(_uv_loop.get(), UV_RUN_NOWAIT) == 0);
}

void Loop::update_time()
{
    uv_update_time(_uv_loop.get());
}

int64_t Loop::now()
{
    return uv_now(_uv_loop.get());
}

bool run()
{
    Loop currLoop(true);
    return currLoop.run();
}

bool run_once()
{
    Loop currLoop(true);
    return currLoop.run_once();
}

bool run_nowait()
{
    Loop currLoop(true);
	return currLoop.run_nowait();
}

} /* namespace native */