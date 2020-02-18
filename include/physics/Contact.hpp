#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "physics/Particle.hpp"

namespace tnt
{
// this works only on particles, momentally...
class Contact
{
protected:
    void resolve(float duration);
    float calcSeparatingVelocity() const;

    float restitution; // coefficient
    float penetration;
    Vector contactNormal;
    Particle *particles[2];

private:
    void resolveVel(float duration);
    void resolveInterpenetration(float duration);
};

class ContactResolver
{
public:
    ContactResolver(unsigned it);

    void setIterations(unsigned it) noexcept;
    void resolve(Contact *contacts, unsigned number, float duration);

protected:
    unsigned iterations;
    unsigned iterationsUsed;
};
} // namespace tnt

#endif //!CONTACT_HPP