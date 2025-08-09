#include "Enemy.h"

Enemy::Enemy(QObject* parent): m_x((rand()%1920) - 25),m_y(-50), ySpeed(5), m_index(rand() % 5)
{
    connect(&eTime, &QTimer::timeout, this, &Enemy::updateEnemy);
    eTime.start(50);
}

void Enemy::updateEnemy()
{
    setY(m_y + ySpeed);

    if (m_y > 950) { // or screen bottom
        eTime.stop();
        emit EnemyDestroyed(this);  // ✅ notify controller to delete
    }
}
