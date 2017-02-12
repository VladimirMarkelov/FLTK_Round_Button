#include <math.h>

#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>
#include "Fl_EllipticButton.h"

Fl_EllipticButton::Fl_EllipticButton(int X, int Y, int W, int H, char *title) :
    Fl_Button(X, Y, W, H, title),
    lineLightColor(fl_rgb_color(240, 240, 240)), lineDarkColor(fl_rgb_color(10, 10, 10)),
    double_border(true), hovered(false)
    {
}

Fl_EllipticButton::~Fl_EllipticButton() {
}

#define REDVAL(x) ((((unsigned long)x) & 0xFF000000) >> 24)
#define GREENVAL(x) ((((unsigned long)x) & 0x00FF0000) >> 16)
#define BLUEVAL(x) ((((unsigned long)x) & 0x0000FF00) >> 8)

Fl_Color get_color(float angle, Fl_Color bright, Fl_Color dark){
    #define RAD2DEG 180.0/M_PI
    #define LIGHT_SOURCE_ANGLE  -M_PI*0.75  //-2.356 rad = -135 deg

    float angle_difference = LIGHT_SOURCE_ANGLE - angle;
    if (angle_difference < - M_PI)
        angle_difference = 2 * M_PI + angle_difference;
    else if (angle_difference > M_PI)
        angle_difference = 2 * M_PI - angle_difference;

    double weight = 0.5 * (cos(angle_difference) + 1.0);

    unsigned char red = (unsigned char) (
        (weight * REDVAL(bright)) + (1.0 - weight) * (REDVAL(dark))
    );
    unsigned char green = (unsigned char) (
        (weight * GREENVAL(bright)) + (1.0 - weight) * (GREENVAL(dark))
    );
    unsigned char blue = (unsigned char) (
        (weight * BLUEVAL(bright)) + (1.0 - weight) * (BLUEVAL(dark))
    );

    return fl_rgb_color(red, green, blue);
};

void draw_ellipse(int X, int Y, long W, long H,
                Fl_Color bright, Fl_Color dark, bool double_width)
{
    long hrad = W / 2, vrad = H / 2;
    int cx = X + hrad, cy = Y + vrad;
    long xoffset = hrad, yoffset = 0;
    float angle;
    Fl_Color clr;

    long d1,d2;
    long t1,t2,t3,t4,t5,t6,t7,t8,t9;
    int xOrig, yOrig;

    t1 = hrad * hrad;
    t2 = 4 * t1;
    t3 = 2 * t2;
    t4 = vrad * vrad;
    t5 = 4 * t4;
    t6 = 2 * t5;
    t7 = hrad * t5;
    t8 = 2 * t7;
    t9 = 0;
    d1 = t2 - t7 + t4;
    d2 = t1 - t8 + t5;

    while (d2 < 0){
        angle = atan2(yoffset, xoffset);
        //Draw the current pixel, reflected across all eight arcs
        clr = get_color(angle, bright, dark);

        fl_color(clr);
        xOrig = cx + xoffset;
        yOrig = cy + yoffset;
        fl_point(xOrig, yOrig);
        if (double_width) {
            fl_point(xOrig + 1, yOrig);
            fl_point(xOrig + 1, yOrig + 1);
            fl_point(xOrig, yOrig + 1);
        };

        clr = get_color(M_PI - angle, bright, dark);
        fl_color(clr);
        xOrig = cx - xoffset;
        yOrig = cy + yoffset;
        fl_point(xOrig, yOrig);
        if(double_width){
            fl_point(xOrig - 1, yOrig);
            fl_point(xOrig - 1, yOrig + 1);
            fl_point(xOrig, yOrig + 1);
        };

        clr = get_color(-M_PI + angle, bright, dark);
        fl_color(clr);
        xOrig = cx - xoffset;
        yOrig = cy - yoffset;
        fl_point(xOrig, yOrig);
        if(double_width){
            fl_point(xOrig - 1, yOrig);
            fl_point(xOrig - 1, yOrig - 1);
            fl_point(xOrig, yOrig - 1);
        };

        clr = get_color(-angle, bright, dark);
        fl_color(clr);
        xOrig = cx + xoffset;
        yOrig = cy - yoffset;
        fl_point(xOrig, yOrig);
        if(double_width){
            fl_point(xOrig + 1, yOrig);
            fl_point(xOrig + 1, yOrig - 1);
            fl_point(xOrig, yOrig - 1);
        };

        yoffset++;
        t9 = t9 + t3;
        if (d1 < 0) {
            d1 = d1 + t9 + t2;
            d2 = d2 + t9;
        }
        else{
            xoffset--;
            t8 = t8 - t6;
            d1 = d1 - t8 + t9 + t2;
            d2 = d2 - t8 + t9 + t5;
        }
    };
    do {
        angle = atan2(yoffset, xoffset);
        //Draw the current pixel, reflected across all eight arcs
        clr = get_color(angle, bright, dark);
        fl_color(clr);
        xOrig = cx + xoffset;
        yOrig = cy + yoffset;
        fl_point(xOrig, yOrig);
        if(double_width){
            fl_point(xOrig + 1, yOrig);
            fl_point(xOrig + 1, yOrig + 1);
            fl_point(xOrig, yOrig + 1);
        };

        clr = get_color(M_PI - angle, bright, dark);
        fl_color(clr);
        xOrig = cx - xoffset;
        yOrig = cy + yoffset;
        fl_point(xOrig, yOrig);
        if(double_width){
            fl_point(xOrig - 1, yOrig);
            fl_point(xOrig - 1, yOrig + 1);
            fl_point(xOrig, yOrig + 1);
        };

        clr = get_color(-M_PI + angle, bright, dark);
        fl_color(clr);
        xOrig = cx - xoffset;
        yOrig = cy - yoffset;
        fl_point(xOrig, yOrig);
        if(double_width){
            fl_point(xOrig - 1, yOrig);
            fl_point(xOrig - 1, yOrig - 1);
            fl_point(xOrig, yOrig - 1);
        };

        clr = get_color(-angle, bright, dark);
        fl_color(clr);
        xOrig = cx + xoffset;
        yOrig = cy - yoffset;
        fl_point(xOrig, yOrig);
        if(double_width){
            fl_point(xOrig + 1, yOrig);
            fl_point(xOrig + 1, yOrig - 1);
            fl_point(xOrig, yOrig - 1);
        };

        xoffset--;
        t8 = t8 - t6;
        if (d2 < 0) {
            yoffset++;
            t9 = t9 + t3;
            d2 = d2 - t8 + t5 + t9;
        }
        else
            d2 = d2 - t8 + t5;
    } while (xoffset >= 0);
};

void Fl_EllipticButton::draw() {
    if (type() == FL_HIDDEN_BUTTON) return;

    if (value()) {
        draw_ellipse(x()+2, y()+2, w()-4, h()-4, lineDarkColor, lineLightColor, doubleBorder());
    } else {
        draw_ellipse(x()+2, y()+2, w()-4, h()-4, lineLightColor, lineDarkColor, doubleBorder());
    }
    if (labeltype() == FL_NORMAL_LABEL && value()) {
        Fl_Color col = value() ? selection_color() : color();
        Fl_Color c = labelcolor();
        labelcolor(fl_contrast(c, col));
        draw_label();
        labelcolor(c);
    } else {
        draw_label();
    }
}

void Fl_EllipticButton::doubleBorder(bool doubleBorder) {
    double_border = doubleBorder;
}

bool Fl_EllipticButton::doubleBorder() const {
    return double_border;
};

