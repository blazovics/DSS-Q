#include "logger.h"
#include <iostream>

using namespace std;

Logger::Logger()
{

}

void Logger::log(char* logMessage){
    cout<<logMessage<<endl;
}
