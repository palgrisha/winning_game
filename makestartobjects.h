#ifndef MAKESTARTOBJECTS_H
#define MAKESTARTOBJECTS_H
#include "resourceloader.h"
#include "sceneinfo.h"
#include "drawingmanager.h"
#include "buttons/doublestatebutton.h"
void make_start_objects(DrawingManagerPtr drawing_manager, ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info,
                        DoubleStateButtonPtr start_button, DoubleStateButtonPtr stop_button);

#endif // MAKESTARTOBJECTS_H
