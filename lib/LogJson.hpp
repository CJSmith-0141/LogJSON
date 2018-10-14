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
#include <ctime>

/*!
 * @namespace csmith
 * @brief namespace for LogJson project
 */
namespace csmith{

    using json = nlohmann::json; //Bless up
    
    template<typename T>
    decltype(auto) timeIsNowEpoch(){
        using namespace std::chrono;
        return duration_cast<T>(high_resolution_clock::now().time_since_epoch()).count();
    };

    enum class TimestampStyle : uint8_t {
        milliseconds_since_unix_epoch,
        milliseconds_since_utc_midnight_with_date,
        milliseconds_and_nanoseconds_since_unix_epoch,
        milliseconds_and_nanoseconds_since_utc_midnight_with_date,
        nanoseconds_since_unix_epoch,
        seconds_since_unix_epoch,
        seconds_since_midnight_with_date,
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

    inline Ms_Us_Date_Midnight_class getMSandUSFromMidnightWithDate(){
        using namespace std::chrono;
        auto timeMeasurement = time_point_cast<nanoseconds>(system_clock::now()); 
        Ms_Us_Date_Midnight_class ret{};
        ret.us = timeMeasurement.time_since_epoch().count() % 86'400'000'000'000; //nanoseconds since midnight
        ret.ms = ret.us / 1'000'000; //miliseconds since midnight
        ret.sec = ret.us / 1'000'000'000;
        ret.us %= 1'000'000; //nanoseconds since last milisecond
        auto CTime = system_clock::to_time_t(timeMeasurement);
        tm utc_tm = *gmtime(&CTime); //there has to be a better way to do this
        ret.date = (utc_tm.tm_year+1900)*10'000 + (utc_tm.tm_mon+1)*100 + (utc_tm.tm_mday);
        return ret;
    }


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
                        log["timestampMSE"] = timeIsNowEpoch<std::chrono::milliseconds>();
                        break;
                    }
                    case TimestampStyle::milliseconds_since_utc_midnight_with_date:{
                        auto mud = getMSandUSFromMidnightWithDate();
                        log["timestampDate"] = mud.date;
                        log["timestampMSSM"] = mud.ms;
                        break;
                    }
                    case TimestampStyle::milliseconds_and_nanoseconds_since_unix_epoch:{
                        auto time = getMSandUSFromEpoch();
                        log["timestampMSE"] = time.first;
                        log["timestampUSP"] = time.second;
                        break;
                    }
                    case TimestampStyle::milliseconds_and_nanoseconds_since_utc_midnight_with_date:{
                        auto mud = getMSandUSFromMidnightWithDate();
                        log["timestampDate"] = mud.date;
                        log["timestampMSSM"] = mud.ms;
                        log["timestampUSSMSSM"] = mud.us; //nanoseconds since milliseconds since midnight
                        break;
                    }
                    case TimestampStyle::nanoseconds_since_unix_epoch:{
                        log["timestampUSE"] = timeIsNowEpoch<std::chrono::nanoseconds>();
                        break;
                    }
                    case TimestampStyle::seconds_since_unix_epoch : {
                        log["timestampSSE"] = timeIsNowEpoch<std::chrono::seconds>();
                        break;
                    }
                    case TimestampStyle::seconds_since_midnight_with_date:{
                        auto mud = getMSandUSFromMidnightWithDate();
                        log["timestampDate"] = mud.sec;
                        log["timestampSSM"] = mud.sec;
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
