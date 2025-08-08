#pragma once
#include <utility>
#include <functional>
#include <tuple>

// Manual implementation of std::apply for C++11
namespace detail {
    // Helper for index sequences (C++11 compatible)
    template<int...> struct seq {};
    template<int N, int... S> struct gens : gens<N-1, N-1, S...> {};
    template<int... S> struct gens<0, S...> { typedef seq<S...> type; };
    
    // Apply implementation
    template<typename F, typename Tuple, int... I>
    auto apply_impl(F&& f, Tuple&& t, seq<I...>) -> decltype(f(std::get<I>(t)...)) {
        return f(std::get<I>(t)...);
    }
}

template<typename F, typename Tuple>
auto apply(F&& f, Tuple&& t) -> decltype(detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(t), 
    typename detail::gens<std::tuple_size<typename std::decay<Tuple>::type>::value>::type{})) {
    return detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(t), 
        typename detail::gens<std::tuple_size<typename std::decay<Tuple>::type>::value>::type{});
}

// Primary template
// TODO: Specialization for regular function pointers (R, Args...)
template<typename T>
struct LambdaTraits;

// Specialization for lambda types (callable objects)
template<typename T>
struct LambdaTraits : public LambdaTraits<decltype(&T::operator())> {};

// Specialization for member function pointers (from lambda operator())
template<typename R, typename C, typename... Args>
struct LambdaTraits<R(C::*)(Args...) const> {
    using ReturnType = R;
    using ArgsTuple = std::tuple<Args...>;
};

/** @brief Memoization lambda wrapper returned value cache */
template<typename Callback>
class Memoize {
    public:
    using Traits = LambdaTraits<Callback>;
    using Return = typename Traits::ReturnType;
    using ArgsTuple = typename Traits::ArgsTuple;

    // 1 Take callback
    Memoize(Callback&& cb) : _cb(std::forward<Callback>(cb)) {}

    // 2 get (arguments) -> result (recompute if changed)
    template<typename... Args>
    Return get(Args&&... args) {
        // Convert args to tuple
        auto newArgs = std::make_tuple(std::forward<Args>(args)...);
        
        // Type check: ensure the tuple matches expected ArgsTuple
        static_assert(std::is_same<std::tuple<typename std::decay<Args>::type...>, ArgsTuple>::value, 
            "Arguments don't match callback signature");
    
        if (!_hasCache || _args != newArgs) {
            _args = newArgs;
            _cached = apply(_cb, _args);
            _hasCache = true;
        }
        
        return _cached;
    }

    private:
        Callback _cb;
        typename Traits::ArgsTuple _args;
        bool _hasCache = false;
        Return _cached;
        
};

template<typename F>
auto memo(F&& f) -> Memoize<typename std::decay<F>::type> {
    return Memoize<typename std::decay<F>::type>(std::forward<F>(f));
}