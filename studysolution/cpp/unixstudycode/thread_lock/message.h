#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <boost/thread.hpp>

class Message {
public:
    Message(int id) {
        id_ = id;
        has_called_ = false;
        count_ = 0;
    }

    void Check() {
        boost::mutex::scoped_lock lock(mutex_);
        if (has_called_) {
            return;
        }

        has_called_ = true;

        __sync_fetch_and_add(&count_, 1); 
    }

    int count() const { return count_; }
    int id()    const { return id_;    }

private:
    int          count_;          
    bool         has_called_;
    boost::mutex mutex_;
    int          id_;
};

#endif

