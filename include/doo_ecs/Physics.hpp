#ifndef TNT_DOO_ECS_PHYSICS_HPP
#define TNT_DOO_ECS_PHYSICS_HPP

#include "doo_ecs/Base.hpp"
#include "math/Rectangle.hpp"

// TODO:
// springs.
// maximal speed/acceleration.
// move the bounding box when the body/object moves.
// modify the collision algorithm to return what kind of collision occurs (horizontal/vertical/none).
// (maybe):
// set some default values (ex for damping, mass) ??

namespace tnt::doo
{
    inline namespace phys
    {
        inline static constexpr float beta{0.05f};         /// < A constant used for baumgarte stabilization.
        inline static constexpr Vector gravity{0.f, 10.f}; /// < A vector acting as the gravity force.
    }                                                      // namespace phys

    enum class body_type
    {
        fixed = 0, /// < The body is fixed in a certain position.
        dynamic    /// < The body can move freely.
    };

    enum class collision_type
    {
        none = 0,   /// < The objects don't collide.
        horizontal, /// < The objects collide on their left/right side.
        vertical,   /// < The objects collide on their top/down side.
    };

    struct physics_comp final
    {
        body_type type;
        float mass;
        float damping;
        float restitution;
        Rectangle bound_box{};
    };

    /// @brief A struct that handles the physics data of all the objects.
    inline struct physics_sys final
    {
        inline physics_sys() noexcept = default;

        physics_sys(physics_sys const &) = delete;
        physics_sys &operator=(physics_sys const &) = delete;

        /// @brief Add a new object to the physics system.
        /// @param body The physics component that has the data of the object.
        /// @note The position of the bounding box of the component is considered
        /// to be relative to the position of the body.
        void add_object(physics_comp const &body);

        /// @brief Apply the given force to the object with the given id.
        /// @param id The id of the object.
        /// @param force The force to apply to the object.
        void addForce(object const &id, tnt::Vector const &force) noexcept;

        /// @brief Add a force that would be applied to each object when Update is called.
        /// @param force The force to be applied.
        void addGlobalForce(tnt::Vector const &force) noexcept;

        /// @brief Update the physics data of the object with the given id.
        /// @param id The id of the object to update.
        /// @param time_ The time that passed since the last update call.
        void Update(object const &id, float time_) noexcept;

        /// @brief Check if the bounding boxes of the two objects are colliding.
        /// @param id The id of the first object.
        /// @param id2 The id of the second object.
        /// @return bool
        bool colliding(object const &id, object const &id2) noexcept;

        // thx Randy Gaul
        // https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

        /// @brief Resolve the collision between the two objects.
        /// @param id The id of the first object.
        /// @param id2 The id of the second object.
        void resolve(object const &id, object const &id2) noexcept;

        /// @brief Load objects physics data from a json chunk.
        /// @param j The json chunk that contains the objects data.
        void from_json(nlohmann::json const &j);

        tnt::Vector totalForce{0.f, 0.f};

        std::vector<float> inv_mass; /// < The inverse of the mass of each objects.

        std::vector<float> damping;     /// < The damping of the objects.
        std::vector<float> restitution; /// < The restitution of the objects.

        std::vector<Vector> vel;   /// < The velocities of the objects.
        std::vector<Vector> accel; /// < The accelerations of the objects.

        std::vector<Rectangle> bound_box; /// < The bounding boxes of the bodies.
    } physics;                            /// < An instance of phys_sys.
} // namespace tnt::doo

#endif //!TNT_DOO_ECS_PHYSICS_HPP