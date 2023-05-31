#include "base.hpp"

std::vector<uint8_t> generate_random_boolean_vector(int length, unsigned int seed)
{
    if (!seed)
    {
        std::random_device rnd_device;
        seed = rnd_device();
    }

    std::mt19937 mersenne_engine{seed};
    std::uniform_int_distribution<uint8_t> dist{0, 1};
    auto gen = [&dist, &mersenne_engine]()
    {
        return dist(mersenne_engine);
    };

    auto vec = std::vector<uint8_t>(length, 0);
    std::generate(std::begin(vec), std::end(vec), gen);

    return vec;
}