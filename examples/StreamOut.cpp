#include "StreamOut.h"

int main(){
    csmith::LogJsonBase msg("hello");

    csmith::LogJsonBase msg2("MSandNSsinceEpoch",csmith::TimestampStyle::milliseconds_and_nanoseconds_since_unix_epoch);

    csmith::LogJsonBase msg3("MSSinceMidnight", csmith::TimestampStyle::milliseconds_since_utc_midnight_with_date);

    csmith::LogJsonBase msg4("MSandNSSinceMidnight", csmith::TimestampStyle::milliseconds_and_nanoseconds_since_utc_midnight_with_date);

    std::cout << msg << std::endl;

    std::cout << msg2 << std::endl;

    std::cout << msg3 <<std::endl;

    std::cout << msg4 <<std::endl;
}
