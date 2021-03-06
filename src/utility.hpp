#ifndef _COMPILER_UTILITY_HPP
#define _COMPILER_UTILITY_HPP

#include <iostream>
#include <list>
#include <type_traits>

#include <Maybe/Maybe.hpp>

// Function pointer template, to ease implementing apply_phase
template<typename ReturnType, typename... Parameters>
using FunctionPointer = ReturnType (*)(Parameters...);

// Applies a phase, given by the function pointer phase.
template<typename FunctionReturnType, typename... Parameters>
FunctionReturnType apply_phase(std::string phase_name, FunctionPointer<FunctionReturnType, Parameters...> phase, Parameters... arguments)
{
    std::cout << " *** " << phase_name << std::endl;
    return phase(arguments...);
}

// The same as std::transform
template<typename T, typename FunctionReturnType>
std::list<FunctionReturnType> unpack_list(std::list<T> list, FunctionPointer<FunctionReturnType,T> function)
{
    std::list<FunctionReturnType> return_value;
    for(T t : list)
    {
        FunctionReturnType ret = function(t);
        return_value.push_back(ret);
    }
    return return_value;
}

// Call function for each, just for side effects
template<typename T>
void unpack_list(std::list<T> list, FunctionPointer<void,T> function)
{
    for(T t : list)
    {
        function(t);
    }
}

template<typename T, typename FunctionReturnType>
void call_if(Maybe<T> maybe, FunctionPointer<FunctionReturnType, T> function)
{
     maybe_if(maybe, [function](T value)
     {
        function(value);
     });
}

/*
 * // Inherit from T, and map super to T.
 * template<typename T>
 * struct inherit_super : T 
 * { 
 *     using super = inherit_super; 
 * protected:
 *     template<typename... A>
 *     explicit inherit_super(A&&... args) : T(std::forward<A>(args)...) {}
 * };
 */

template<typename T> // TODO FIXME couldn't see why invocations no longer compiler (assumed pointers?)
std::string concat(std::list<T> input, FunctionPointer<std::string, T> string_convert_function, std::string seperator)
{
    std::string output_string = "";
    if(input.empty() == false)
    {
        // Get the first element
        std::string temp = string_convert_function(input.front());
        // And append it
        output_string.append(temp);
        // Now loop the remaining elements
        // (the ++ in init, is to skip the element we already read).
        for (typename std::list<T>::iterator it=(++input.begin()); it != input.end(); ++it)
        {
            temp = string_convert_function(*it);
            output_string.append(seperator);
            output_string.append(temp);
        }
    }
    return output_string;
}

#endif //_COMPILER_UTILITY_HPP
