#include "error.h"

Error::Error(int err_code, string err_message) {
    code    = err_code;
    message = err_message;
}

void Error::Fatal() {
    printf("ERROR %d: %s", this->code, this->message);
    exit(1);
}
