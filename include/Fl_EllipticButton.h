#ifndef FL_ELLIPTICBUTTON_H
#define FL_ELLIPTICBUTTON_H

#include <FL/Fl_Button.H>

class Fl_EllipticButton : public Fl_Button
{
    public:
        Fl_EllipticButton(int X, int Y, int W, int H, char *title = 0);
        virtual ~Fl_EllipticButton();
        void draw();
        void doubleBorder(bool doubleBorder);
        bool doubleBorder() const;
    protected:
    private:
        Fl_Color lineLightColor;
        Fl_Color lineDarkColor;
        bool double_border;
        bool hovered;
};

#endif // FL_ELLIPTICBUTTON_H
