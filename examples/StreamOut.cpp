#include "StreamOut.h"

using namespace csmith; 

int main(){
    LogJsonBase msg("hello");

    LogJsonBase msg2("MSandNSsinceEpoch",TimestampStyle::milliseconds_and_nanoseconds_since_unix_epoch);

    LogJsonBase msg3("MSSinceMidnight", TimestampStyle::milliseconds_since_utc_midnight_with_date);

    LogJsonBase msg4("MSandNSSinceMidnight", TimestampStyle::milliseconds_and_nanoseconds_since_utc_midnight_with_date);

    std::cout << msg << std::endl;

    std::cout << msg2 << std::endl;

    std::cout << msg3 <<std::endl;

    std::cout << msg4 <<std::endl;
}
