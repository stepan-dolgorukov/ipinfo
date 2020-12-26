#ifndef __IPINFO__REQUESTER__HPP__
    #define __IPINFO__REQUESTER__HPP__

    #include <string>

    namespace ipinfo
    {
        class __requester
        {
            private:
                std::string __request_url{};
                std::string __request_answer{};
                std::string __error{"No error"};

            public:
                void            create_request_url(const std::string &host,
                                                   const std::string &ip,
                                                   const std::string &lang);

                void            send_request(void);
                std::string     get_request_answer(void) const;
                std::string     get_err(void) const;
        };
    }

#endif
