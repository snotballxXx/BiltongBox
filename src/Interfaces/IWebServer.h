#ifndef __IWEB_SERVER__H__
#define __IWEB_SERVER__H__

namespace Interfaces
{
    class IWebServer 
    {
        public:
        virtual String GetIpAddress() = 0;
    };
}

#endif  //!__IWEB_SERVER__H__