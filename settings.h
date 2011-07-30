#ifndef SETTINGS_H
#define SETTINGS_H

//#include "ocrkernel.h"

class Settings
{
public:
    Settings();
    bool setLayout(bool);
    bool getLayout() const;
    bool setCurrentKernel(int);
    int getCurrentKernel() const;
    bool setCurrentLanguage(int);
    int getCurrentLanguage() const;

private:
    bool layout;
    int currentKernel;
    int currentLanguage;
};

#endif // SETTINGS_H
