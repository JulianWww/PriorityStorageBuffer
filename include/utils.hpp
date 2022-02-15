#include <sstream>
#include <iomanip>

namespace priorityBuffer
{   
    template<typename T>
    std::string int_to_hex( T i );
}

template< typename T >
std::string priorityBuffer::int_to_hex( T i )
{
    std::stringstream stream;
    stream << std::setfill ('0') << std::setw(sizeof(T)*2) 
           << std::hex << i;
        
    auto out = stream.str();
    return out;
}