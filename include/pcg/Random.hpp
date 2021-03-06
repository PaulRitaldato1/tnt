#ifndef TNT_PCG_RANDOM_HPP
#define TNT_PCG_RANDOM_HPP

#include <random>
#include "math/Vector.hpp"

// TODO: randomVector, randomColor, etc.

namespace tnt
{

    /// @brief Get a random float on range @c [min_,max_].
    /// @param min_ The minimum value of the float.
    /// @param max_ The maximum value of the float.
    /// @return float
    inline float randomFloat(float min_, float max_)
    {
        static std::default_random_engine eng;
        static std::uniform_real_distribution<float> dist{min_, std::nextafter(max_, std::numeric_limits<float>::max())};
        return dist(eng);
    }

    /// @brief Get a random int on range @c [min_,max_].
    /// @param min_ The minimum value of the int.
    /// @param max_ The maximum value of the int.
    /// @return int
    inline int randomInt(int min_, int max_)
    {
        static std::random_device device;
        static std::mt19937 generator{device()};
        static std::uniform_int_distribution dist{min_, max_};
        return dist(generator);
    }

    /// @brief Get a tnt::Vector with randomly generated coordinates.
    /// @param minX The minimum value of the x coordinate.
    /// @param maxX The maximum value of the x coordinate.
    /// @param minY The minimum value of the y coordinate.
    /// @param maxY The maximum value of the y coordinate.
    /// @return tnt::Vector
    inline tnt::Vector randomVector(float minX, float maxX, float minY, float maxY) noexcept
    {
        const tnt::Vector result{randomFloat(minX, maxX), randomFloat(minY, maxY)};
        return result;
    }
} // namespace tnt

#endif //!TNT_PCG_RANDOM_HPP