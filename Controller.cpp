#include "Controller.h"

Controller::Controller(QObject* parent): m_x(1920/2),m_y(950-50),
    xSpeed(10), minX(0), maxX(1920), bottomY(950-50)
{
    // &Controller
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16); //60fps

    connect(&moveTimer, &QTimer::timeout, this, &Controller::updateMovement);
    moveTimer.start(16); //60fps


    connect(&startE, &QTimer::timeout, this, &Controller::createEnemy);
    startE.start(1000 + rand()% 2000);



}

void Controller::moveLeft()
{
    moveDirection = -1;

    if (!moveTimer.isActive())
    {
        moveTimer.start();
    }
    // setX(m_x - xSpeed);
    // if(m_x < minX )
    // {
    //     setX(minX);
    // }
}

void Controller::moveRight()
{
    moveDirection = 1;

    if (!moveTimer.isActive())
    {
        moveTimer.start();
    }
    // setX(m_x + xSpeed);
    // if(m_x > maxX-50)
    // {
    //     setX(maxX-50);
    // }
}

void Controller::stopMovement()
{
    moveDirection = 0;
    moveTimer.stop();
}

QString Controller::showScore()
{
    return QString::number(score());
}

void Controller::restartGame()
{
    for(Enemy* e: enemyList)
    {
        delete e;
    }
    enemyList.clear();

    for(Bullet* b: bulletList)
    {
        delete b;
    }
    bulletList.clear();

    emit bulletChanged();
    emit enemyChanged();

    setX(1920/2);
    setY(950-50);

    setScore(0);
    emit scoreChanged();

    emit xChanged();
    emit yChanged();

}

void Controller::applyThrust()
{

    ySpeed = maxThrust;
    if(m_y < bottomY/1.5)
    {
        ySpeed =0;
    }
}

void Controller::fireBullet()
{
    Bullet* newBullet = new Bullet();
    newBullet->setX(m_x+20);
    newBullet->setY(m_y);

    connect(newBullet, &Bullet::bulletDestroyed, this, &Controller::removeBullet);

    bulletList.append(newBullet);
    emit bulletChanged();
    qInfo()<<"Tadic is on fire";

}

void Controller::createEnemy()
{
    Enemy* newEnemy = new Enemy();
    newEnemy->setX((rand() % 1920) - 25);
    newEnemy->setY(-50);

    connect(newEnemy, &Enemy::EnemyDestroyed, this, &Controller::deleteEnemy);

    enemyList.append(newEnemy);
    startE.start(1000 + rand()% 2000);
    emit enemyChanged();
    qInfo()<<"Tadic is on the board";
}

void Controller::updateState()
{
    m_y += ySpeed;
    ySpeed += gravity;

    if(m_y >bottomY)
    {
        m_y = bottomY;
    }

    checkCollision();


    for(Enemy* e: enemyList)
    {
        if(e->y()> bottomY)
        {
            emit gameOver();
            qInfo()<< "Game Over";
            return;
        }

        double enemyLeft = e->x();
        double enemyRight = e->x()+50;
        double enemyTop = e->y();
        double enemyBottom = e->y()+50;

        double playerLeft = m_x;
        double playerRight = m_x+50;
        double playerTop = m_y;
        double playerBottom = m_y+50;


            if (enemyRight > playerLeft &&
                enemyLeft < playerRight &&
                enemyBottom > playerTop &&
                enemyTop < playerBottom)
            {
                emit gameOver();
                qInfo()<< "Game Over";
                return;
            }

    }

    emit yChanged();

}

void Controller::removeBullet(Bullet* b)
{
    bulletList.removeAll(b);
    emit bulletChanged();
    b->deleteLater();
}


void Controller::deleteEnemy(Enemy* enemy)
{
    enemyList.removeAll(enemy);
    emit enemyChanged();
    enemy->deleteLater();
}

void Controller::checkCollision()
{
    for(int i= bulletList.size() -1; i >=0; i-- )
    {
        Bullet* bullet = bulletList[i];

        for(int j= enemyList.size()-1; j >= 0; j--)
        {
            Enemy* enemy = enemyList[j];

            double bulletLeft = bullet->x();
            double bulletRight = bullet->x()+10;

            double bulletTop = bullet->y();
            double bulletBottom = bullet->y()+30;

            double enemyLeft = enemy->x();
            double enemyRight = enemy->x()+50;
            double enemyTop = enemy->y();
            double enemyBottom = enemy->y()+50;

            if (bulletRight > enemyLeft &&
                bulletLeft < enemyRight &&
                bulletBottom > enemyTop &&
                bulletTop < enemyBottom)
            {
                removeBullet(bullet);
                deleteEnemy(enemy);
                setScore(score() + 10);
                emit scoreChanged();
                break;
            }
        }
    }
}

void Controller::updateMovement()
{
    if(moveDirection == -1 && m_x > minX )
    {
        setX(m_x - xSpeed);
    }
    if(moveDirection == 1 && m_x < maxX- 50 )
    {
        setX(m_x + xSpeed);
    }
    if(moveDirection == 0)
    {
        setX(m_x);
    }
}

