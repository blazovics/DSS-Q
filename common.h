#ifndef COMMON_H
#define COMMON_H

#define NULL 0

#define MAX_DISTANCE 1000000

#define TARGET_ENTITY 0
#define SWARM_ENTITY 1
#define GRG_ENTITY 2

#include "maths.h"

#include <math.h>

#include <stdlib.h>

#include <time.h>

#include <iostream>

#define QT_UI
//#define MARMALADE_UI

#ifdef QT_UI

#include <QPainter>
#include <QPoint>
#include <QBrush>

#endif

#endif // COMMON_H
