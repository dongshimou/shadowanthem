#ifndef YANTHEMS_DEFER_HPP
#define YANTHEMS_DEFER_HPP

#include <tuple>
#include <utility>
#include <functional>
#if 0
struct defer{
    template <typename F,typename... Args>
    defer(F&&f,Args&&...args)noexcept{
        auto tmp=std::make_tuple(std::forward<Args>(args)...);
//         task=[&,tt=std::move(tmp)](){
//             std::apply(std::forward<F>(f),tt);
//         };
        task=[&](){
            std::apply(std::forward<F>(f),std::move(tmp));
        };
    }
    std::function<void(void)>task;
    ~defer(){
        task();
    }
};
#endif

#endif //YANTHEMS_DEFER_HPP