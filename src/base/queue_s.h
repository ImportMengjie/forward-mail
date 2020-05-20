//
// Created by mengjie on 5/20/20.
//

#ifndef FORWARD_MAIL_QUEUE_S_H
#define FORWARD_MAIL_QUEUE_S_H

#include <queue>
#include <mutex>
#include <atomic>
#include <initializer_list>
#include <condition_variable>

namespace dd{

    template <typename T>
    class queue_s{
    private:
        mutable std::mutex mut;
        mutable std::condition_variable data_cond;
        using queue_type = typename std::queue<T>;
        queue_type data_queue;

    public:
        using value_type = typename queue_type::value_type;
        using container_type = typename queue_type::container_type;

        queue_s()=default;
        queue_s(const queue_s&)=delete;
        queue_s& operator=(queue_s&)=delete;

        template<typename _InputIterator>
        queue_s(_InputIterator first, _InputIterator last){
            for(auto itor=first;itor!=last;++itor){
                data_queue.push(*itor);
            }
        }
        explicit queue_s(const container_type &c):data_queue(c){}
        queue_s(std::initializer_list<value_type> list):data_queue(list.begin(),list.end()){}

        void push(const value_type& new_value){
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(std::move(new_value));
            data_cond.notify_all();
        }

        template<typename _InputIterator>
        void push(_InputIterator first, _InputIterator last){
            std::lock_guard<std::mutex> lk(mut);
            for(auto itor=first;itor!=last;++itor){
                data_queue.push(*itor);
            }

        }

        value_type wait_and_pop(){
            std::unique_lock<std::mutex>lk(mut);
            data_cond.wait(lk,[this]{return !this->data_queue.empty();});
            auto value=std::move(data_queue.front());
            data_queue.pop();
            return value;
        }

        bool try_pop(value_type& value){
            std::lock_guard<std::mutex>lk(mut);
            if(data_queue.empty())
                return false;
            value=std::move(data_queue.front());
            data_queue.pop();
            return true;
        }

        auto empty() const->decltype(data_queue.empty()) {
            std::lock_guard<std::mutex>lk(mut);
            return data_queue.empty();
        }

        auto size() const->decltype(data_queue.size()){
            std::lock_guard<std::mutex>lk(mut);
            return data_queue.size();
        }
    };

}

#endif //FORWARD_MAIL_QUEUE_S_H
