#ifndef LOGJSON_HPP
#define LOGJSON_HPP
/*
 * @file LogJson.hpp
 * @author Connor James Smith
 * @date 2018
 * @brief Forward decelerations for library
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

    using json = nlohmann::json;
    
    template<typename T>
    decltype(auto) timeIsNowEpoch(){
        using namespace std::chrono;
        return duration_cast<T>(high_resolution_clock::now().time_since_epoch()).count();
    };

    enum class TimestampStyle : uint8_t {
        milliseconds_since_unix_epoch,
        milliseconds_and_nanoseconds_since_unix_epoch,
        nanoseconds_since_unix_epoch,
        seconds_since_unix_epoch,
        milliseconds_since_midnight,
        nanoseconds_since_midnight,
        no_timestamp = 0xFF
    };

    inline auto getMSandUSFromEpoch(){
        using namespace std::chrono;
        auto US_duration = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch());
        auto MS = US_duration.count() / 1'000'000;
        auto US = US_duration.count() % 1'000'000;
        return std::pair<decltype(MS),decltype(US)>{MS,US};
    };

    class Ms_Us_Date_Midnight_class{ //POD convenience class
    public: 
        uint64_t sec,ms,us,date;
    };


    class LogJsonBase{
    public:
        LogJsonBase() = delete;
        
        explicit LogJsonBase(std::string nameArg, //name of the log you're about to make
            TimestampStyle style = TimestampStyle::milliseconds_since_unix_epoch) : //How do you want the timestamp?
            name{std::move(nameArg)}, //move the by-value arg into name 
            log({}) //initialize the log explicitly to a json object, not a json array 
            {
                switch(style){
                    case TimestampStyle::milliseconds_since_unix_epoch :{
                        log["time"] = timeIsNowEpoch<std::chrono::milliseconds>();
                        break;
                    }
                    case TimestampStyle::milliseconds_and_nanoseconds_since_unix_epoch:{
                        auto time = getMSandUSFromEpoch();
                        log["time_ms"] = time.first;
                        log["time_us"] = time.second;
                        break;
                    }
                    case TimestampStyle::nanoseconds_since_unix_epoch:{
                        log["time"] = timeIsNowEpoch<std::chrono::nanoseconds>();
                        break;
                    }
                    case TimestampStyle::seconds_since_unix_epoch : {
                        log["time"] = timeIsNowEpoch<std::chrono::seconds>();
                        break;
                    }
                    case TimestampStyle::no_timestamp: {
                        break; 
                    }
                    default:{
                        break;
                    }
                }
            }; 
        
        LogJsonBase(const LogJsonBase& copyLog) = default; 
        LogJsonBase& operator=(const LogJsonBase& copyAssignLog) = default; 
        LogJsonBase(LogJsonBase&& moveLog) = default;
        LogJsonBase& operator=(LogJsonBase&& moveAssignLog) = default;

        virtual ~LogJsonBase() = default;
        
        friend std::ostream& operator<<(std::ostream &lhs, const LogJsonBase &rhs){
            lhs << rhs.log.dump(4);
            return lhs;
        };
        
        const json& getConstJson(){
            return log;
        };

    protected:
        json& getJson(){
            return log;
        };

    
    private:
        std::string name;
        json log;
    
    }; /* class LogJsonBase */




} /* namespace csmith */



#endif /* LOGJSON_HPP */
