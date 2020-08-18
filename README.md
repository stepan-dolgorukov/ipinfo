# ipinfo by DolgorukovGTA #

Hi, nice to meet you in the ipinfo project repository. This is tiny, but nimble module for getting information about IP addresses.
You can include the module to your project or use as an CLI application.

## How does it work? ##

For getting IP information I choose [ipwhois.io](https://ipwhois.io) IP Geolocation API. The site returns information into JSON object.

Libraries used:

1. [libcurl](https://github.com/curl/curl) - for HTTP request, for getting the answer from the server.
2. [cJSON](https://github.com/DaveGamble/cJSON) - for parsing the JSON object coming from the server.
3. [spdlog](https://github.com/gabime/spdlog) - for debug logging.

I am grateful to the developers of the libraries listed above.