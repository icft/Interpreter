#include <iostream>
#include "Nodes.h"

int main() {
    auto u = std::shared_ptr<Node>();
    u = std::make_shared<IntLeaf>(1, 21);
    if (std::dynamic_pointer_cast<IntLeaf>(u)->data->data->get_type() == Datatypes::INT)
        std::cout << std::dynamic_pointer_cast<Int>(std::dynamic_pointer_cast<IntLeaf>(u)->data->data)->value;
    //std::cout << std::dynamic_pointer_cast<Int>(i->data);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
