#ifndef __IPINFO__REQUESTER__HPP__
    #define __IPINFO__REQUESTER__HPP__

    #include <string>
    #include "ipinfo_types.hpp"

    namespace ipinfo
    {
        class __requester
        {
            private:
                std::string __request_url;
                std::string __request_answer;
                error_t     __error;

            public:
                void            create_request_url(const std::string &host,
                                                   const std::string &ip,
                                                   const std::string &lang_name);

                void            send_request(void);
                std::string     get_request_answer(void) const;
                error_t         get_last_error(void) const;
        };
    }

#endif
