export module generator; //export this module

template<typename T>
export struct generator {
    using myType = T;
};

struct helper {
    int x;
}