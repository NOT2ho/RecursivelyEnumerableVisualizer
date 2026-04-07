#ifndef EXPORT_H
#define EXPORT_H
#include <QImage>

class Export
{
public:
    Export();
    static bool export2D(int width, int height, QImage::Format format,
                         std::vector<std::vector<int>>, QString fileName);

private:

};
#endif // EXPORT_H
