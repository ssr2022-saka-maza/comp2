#include "ssr2/PS4USB.hpp"

ssr2::PS4USB::PS4USB() : _usb(), _ps4(&_usb) {}

int ssr2::PS4USB::begin() { return _usb.Init(); }

void ssr2::PS4USB::update() { _usb.Task(); }

bool ssr2::PS4USB::connected() { return _ps4.connected(); }

void ssr2::PS4USB::read(ssr2::PS4Value *output) {
    if (output == nullptr || output == NULL)
        return;
    output->lstick.x = _ps4.getAnalogHat(LeftHatX);
    output->lstick.y = _ps4.getAnalogHat(LeftHatY);
    output->rstick.x = _ps4.getAnalogHat(RightHatX);
    output->rstick.y = _ps4.getAnalogHat(RightHatY);
    output->up = _ps4.getButtonPress(UP);
    output->right = _ps4.getButtonPress(RIGHT);
    output->down = _ps4.getButtonPress(DOWN);
    output->left = _ps4.getButtonPress(LEFT);
    output->triangle = _ps4.getButtonPress(TRIANGLE);
    output->circle = _ps4.getButtonPress(CIRCLE);
    output->cross = _ps4.getButtonPress(CROSS);
    output->square = _ps4.getButtonPress(SQUARE);
    output->l1 = _ps4.getButtonPress(L1);
    output->l2 = _ps4.getAnalogButton(L2);
    output->l3 = _ps4.getButtonPress(L3);
    output->r1 = _ps4.getButtonPress(R1);
    output->r2 = _ps4.getAnalogButton(R2);
    output->r3 = _ps4.getButtonPress(R3);
    output->ps = _ps4.getButtonPress(PS);
    output->share = _ps4.getButtonPress(SHARE);
    output->options = _ps4.getButtonPress(OPTIONS);
    output->finger1Touch = _ps4.isTouching(0);
    if (output->finger1Touch) {
        output->finger1Pos.x = _ps4.getX(0);
        output->finger1Pos.y = _ps4.getY(0);
    } else {
        output->finger1Pos.x = 0;
        output->finger1Pos.y = 0;
    }
    output->finger2Touch = _ps4.isTouching(1);
    if (output->finger2Touch) {
        output->finger2Pos.x = _ps4.getX(1);
        output->finger2Pos.y = _ps4.getY(1);
    } else {
        output->finger2Pos.x = 0;
        output->finger2Pos.y = 0;
    }
}

ssr2::PS4Value *ssr2::PS4USB::read() {
    ssr2::PS4Value *value = new ssr2::PS4Value(
        _ps4.getAnalogHat(LeftHatX), _ps4.getAnalogHat(LeftHatY),
        _ps4.getAnalogHat(RightHatX), _ps4.getAnalogHat(RightHatY),
        _ps4.getButtonPress(UP), _ps4.getButtonPress(RIGHT),
        _ps4.getButtonPress(DOWN), _ps4.getButtonPress(LEFT),
        _ps4.getButtonPress(TRIANGLE), _ps4.getButtonPress(CIRCLE),
        _ps4.getButtonPress(CROSS), _ps4.getButtonPress(SQUARE),
        _ps4.getButtonPress(L1), _ps4.getAnalogButton(L2),
        _ps4.getButtonPress(L3), _ps4.getButtonPress(R1),
        _ps4.getAnalogButton(R2), _ps4.getButtonPress(R3),
        _ps4.getButtonPress(PS), _ps4.getButtonPress(SHARE),
        _ps4.getButtonPress(OPTIONS), _ps4.isTouching(0), 0, 0,
        _ps4.isTouching(1), 0, 0);
    if (value->finger1Touch) {
        value->finger1Pos.x = _ps4.getX(0);
        value->finger1Pos.y = _ps4.getY(0);
    }
    if (value->finger2Touch) {
        value->finger2Pos.x = _ps4.getX(1);
        value->finger2Pos.y = _ps4.getY(1);
    }
    return value;
}
