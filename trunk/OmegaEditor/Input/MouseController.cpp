#include "MouseController.h"
#include <QDebug>

MouseController::MouseController()
{
    _lastPressed = Qt::NoButton;
    _lastX = 0;
    _lastY = 0;
    _continuePress = false;
}

void
MouseController::rotateCam(Ogre::Real dx, Ogre::Real dy, Ogre::Camera *cam)
{
    //qDebug() << "ROTACION EN EL MOUSE CONTROLLER";
    //qDebug() << "dx: " << dx << "dy: " << dy;
    Ogre::Radian pitchValue, yawValue;

    //TODO: Calculate Current yaw and pitch from the camera

    pitchValue -= (Ogre::Radian)ROTATION_SPEED*dy;
    yawValue -= (Ogre::Radian)ROTATION_SPEED*dx;

    //qDebug() << "Yaw dx(º): " << yawValue.valueDegrees() << "Pitch dy(º): " <<  pitchValue.valueDegrees();
    //qDebug() << "Yaw Suma(º): " << yawValue.valueDegrees() + _yawValue.valueDegrees() << "Pitch Suma(º): " <<  pitchValue.valueDegrees()+_pitchValue.valueDegrees();
    //qDebug() << "YawOnly(º): " << _yawValue.valueDegrees() << "PitchOnly(º): " <<  _pitchValue.valueDegrees();

    _lastYawValue = yawValue;
    _lastPitchValue = pitchValue;

    Ogre::Real radius = cam->getPosition().length();
    cam->setPosition(0,0,0);
    cam->setOrientation(Ogre::Quaternion::IDENTITY);
    cam->yaw(Ogre::Degree((_yawValue+yawValue)*-1));
    cam->pitch(Ogre::Degree((_pitchValue+pitchValue)*-1));
    cam->moveRelative(Ogre::Vector3(0.0,0.0,radius));
}
