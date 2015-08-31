#ifndef TILESMODEL_H
#define TILESMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>

#include <QVector>
#include <QQueue>

#include "tile.h"
#include "cell.h"
#include "package.h"



class TilesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int execPackCnt READ execPackCnt WRITE setExecPackCnt NOTIFY execPackCntChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)

    ///////////////////////////////////////////////////////
    enum TileElemRoles {
        TypeRole = Qt::UserRole + 1,
        OpacityRole,
        ScaleRole
    };

    ///////////////////////////////////////////////////////
    enum GameResult {
        Win = Qt::UserRole + 1,
        Lose,
        NotFinished
    };


public:
    static TilesModel *Instance();
    void generate();

private:
    bool leadsToMatch(QSharedPointer<Tile> new_tile);

signals:
    void widthChanged();
    void heightChanged();
    void execPackCntChanged();
    void statusChanged();
    void scaleChanged();


public slots:
    /*********************/
    /********SLOTS********/
    /*********************/

    void moveTile(int index);
    void provideScaleAnimation();

    void execNextPackage();
    void createPackages();       //tmp move to slots for testing


    // setters / getters for qml engine
    int width();
    void setWidth(const int width);

    int height();
    void setHeight(const int height);

    int execPackCnt() const;
    void setExecPackCnt(int execPackCnt);

    QString status();

public:
    /***************************/
    /***interface for Command***/
    /***************************/

    void swapCells(const int from, const int to);
    void swapCells(const Cell &from, const Cell &to);

    void changeOpacity(QSharedPointer<Tile> target, const float opacity);
    void changeScale(QSharedPointer<Tile> target, const float scale);

    void createItem(int index);
    void refreshItem(int index);

    QSharedPointer<Tile> item(int index);
    QString getRandType();


    /***************************/
    /*****interface for Tile****/
    /***************************/

    int indexOfItem(const Tile *item) const;


    // for QML Engine
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;


    // setters / getters
    int elementScore() const;
    void setElementScore(int element_score);

    int minScore() const;
    void setMinScore(int minScore);

    int maxMoves() const;
    void setMaxMoves(int maxMoves);

    QVector<int> getTypes() const;
    void setTypes(const QVector<int> &types);

    static bool getInitialised();
    static void setInitialised(bool initialised);

    QObject *getRoot() const;
    void setRoot(QObject *root);

private:
    /***************************/
    /*******for game logic******/
    /***************************/
    bool able_to_move(Cell);
    QVector<Cell> cellsToMove(Cell cell);

    QVector<QVector<QSharedPointer<Tile> > > findMatches() const;
    bool checkForRepeating(QSharedPointer<Tile> tile, QVector<QVector<QSharedPointer<Tile> > > conteiner) const;
    bool matchesExisting();

    GameResult gameResult();


    // for singleton
    TilesModel();
    TilesModel(const TilesModel&);
    TilesModel& operator=(const TilesModel&);

private:
    QObject *m_root;

    QVector<QSharedPointer<Tile> > m_dataList;
    QQueue<Package> m_packList;
    QVector<int> m_types;

    int m_width;
    int m_height;
    int m_elementScore;
    int m_minScore;
    int m_maxMovesCount;

    int m_movesCount;
    int m_score;

    int m_execPackCnt;
    Cell m_dragedCell;

    static bool m_initialised;
};

#endif // TILESMODEL_H
