#ifndef ENEMY_H
#define ENEMY_H


#include <QObject>
#include <QTimer>

class Enemy: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int mIndex READ mIndex WRITE setIndex NOTIFY indexChanged )


public:
    Enemy(QObject* parent = nullptr);

    int mIndex(){return m_index;}

    void setIndex(int index)
    {
        if(m_index !=index)
        {
            m_index = index;
            emit indexChanged();
        }
    }

    double x(){return m_x;}

    double y(){return m_y;}

    void setX(double value)
    {
        if(m_x !=value)
        {
            m_x = value;
            emit xChanged();
        }
    }

    void setY(double value)
    {
        if(m_y !=value)
        {
            m_y = value;
            emit yChanged();
        }
    }

public slots:
    void updateEnemy();


signals:
    void xChanged();
    void yChanged();
    void EnemyDestroyed(Enemy* self);
    void indexChanged();

private:
    double m_x;
    double m_y;
    double ySpeed;
    QTimer eTime;
    int m_index;

};

#endif // ENEMY_H
