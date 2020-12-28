export module includerModule1; //can export module from cpp, even depending on imported modules

import generator;
import math;

void includerFunc1() {
    math(1);
    generator<int> g;
}
