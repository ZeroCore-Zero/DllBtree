#include "uuid.h"
namespace ZC
{
    
using std::string;

string generate_uuid() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, 15);

    const string uuid_format = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    string uuid;
    uuid.reserve(uuid_format.size());

    for (size_t i = 0; i < uuid_format.size(); ++i) {
        if (uuid_format[i] == 'x' || uuid_format[i] == 'y') {
            const int r = dist(rng);
            const char c = uuid_format[i] == 'x' ? "0123456789abcdef"[r] : "89ab"[r % 4];
            uuid += c;
        }
        else {
            uuid += uuid_format[i];
        }
    }
    return uuid;
}

}