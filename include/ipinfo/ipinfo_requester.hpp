#ifndef __IPINFO__REQUESTER__HPP__
    #define __IPINFO__REQUESTER__HPP__

    #include <string>

    namespace ipinfo
    {
        class __requester
        {
            public:
                std::string get_full_url(const std::string &host,
                                         const std::string &ip,
                                         const std::string &lang);

                std::string make_request(const std::string &url);
        };
    }

#endif
