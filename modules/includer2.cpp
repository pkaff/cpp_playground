export module includerModule2; //can export module from cpp, even depending on imported modules

import generator;
import math;

void includerFunc2() {
    math(2);
    generator<float> g;
}
