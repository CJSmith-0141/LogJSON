#ifndef LOGJSON_HPP
#define LOGJSON_HPP
/*
 * @file LogJson.hpp
 * @author Connnor Jamse Smith
 * @date 2018
 * @brief Forward Decalerations for library 
 * @copyright MIT License
 */

#include <iostream>
#include <json.hpp>
#include <chrono>

/*!
 * @namespace csmith
 * @brief namespace for LogJson project
 */
namespace csmith{

    using json = nlohmann::json; //Bless up
    
    template<typename T>
    decltype(auto) timeIsNow(){
        using namespace std::chrono;
        return duration_cast<T>(system_clock::now().time_since_epoch()).count();
    };

    class LogJsonBase{
    public:
        LogJsonBase() = delete;
        explicit LogJsonBase(std::string nameArg) : 
            name{std::move(nameArg)}, //move the by-value arg into name
            log({}) //initialize the log to a json object, not an array 
            {
                log[name]["tstmp"] = timeIsNow<std::chrono::milliseconds>();
            }; 
        
        LogJsonBase(const LogJsonBase& copyLog) = default; 
        LogJsonBase& operator=(const LogJsonBase& copyAssignLog) = default; 
        LogJsonBase(LogJsonBase&& moveLog) = default;
        LogJsonBase& operator=(LogJsonBase&& moveAssignLog) = default;

        virtual ~LogJsonBase() = default;
        
        friend std::ostream& operator<<(std::ostream &lhs, const LogJsonBase &rhs){
            lhs << rhs.log.dump();
            return lhs;
        };
        
        json& getJson(){
            return log;
        };
    
    private:
        std::string name;
        json log;
    };

} /* namespace csmith */



#endif /* LOGJSON_HPP */
