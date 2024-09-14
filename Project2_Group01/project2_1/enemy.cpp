#include "enemy.h"

Enemy::Enemy(QString attribute, int attackPower, int cd, int hp, QString specialMechanism)
    : m_attribute(attribute), m_attackPower(attackPower), m_cd(cd), m_hp(hp), m_specialMechanism(specialMechanism)
{
}

QString Enemy::getAttribute() const
{
    return m_attribute;
}

int Enemy::getAttackPower() const
{
    return m_attackPower;
}

int Enemy::getCd() const
{
    return m_cd;
}

int Enemy::getHp() const
{
    return m_hp;
}

QString Enemy::getSpecialMechanism() const
{
    return m_specialMechanism;
}
