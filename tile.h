#ifndef TILE_H
#define TILE_H

#include "common_types.h"

class Tile : public QObject
{
    Q_OBJECT
public:
    explicit Tile(QObject *parent = 0, QString type = "", QString color = "", int index = 0, float opacity = 0);

    QString getType() const;
    void setType(const QString &type);

    QString getColor() const;
    void setColor(const QString &color);

    float getOpacity() const;
    void setOpacity(const float &opacity);

    int getIndex() const;
    void setIndex(int index);

signals:

public slots:

private:
    QString type_;
    QString color_;
    float opacity_;
    int index_;


};

#endif
