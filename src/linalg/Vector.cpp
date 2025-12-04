#include <iostream> 
#include <vector>
#include <initializer_list>
#include <Windows.h>

using namespace std;

class Vector {
private:
    vector<double> data_;
public:
    Vector(size_t n) : data_(n) {}

    Vector(initializer_list<double> list)
        :data_(list) {
        
    };

    size_t size() const noexcept { return data_.size(); }

};

int main() {

}