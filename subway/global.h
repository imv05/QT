#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMap>
#include <QVector>
#include <nlohmann/json.hpp>
#include <QDebug>

using json = nlohmann::json;

int toSec(int h, int m, int s);
#endif // GLOBAL_H
