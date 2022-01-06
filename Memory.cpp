#include "Memory.h"

bool contains(std::map<std::string, std::shared_ptr<MemoryUnit>> m, std::string s) {
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->first == s) {
            return true;
        }
    }
    return false;
}
