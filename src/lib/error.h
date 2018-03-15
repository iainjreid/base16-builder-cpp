#ifndef BASE16_BUILDER_ERROR_H
#define BASE16_BUILDER_ERROR_H

class Error {
public:
    int code;
    std::string message;

    Error(int, std::string);

    void Fatal();
};

#endif //BASE16_BUILDER_ERROR_H
