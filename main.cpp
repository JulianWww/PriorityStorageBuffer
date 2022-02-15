#include <iostream>
#include "include/priorityBuffer.hpp"

int main(int argc, char){
    priorityBuffer::Buffer<int, int> buffer(2, "storage/", "bin");
    buffer.addElement(2,1);
    buffer.addElement(3,2);
    buffer.addElement(4,3);
    buffer.render();
    return 1;
}