#ifndef IMAGEBASE_H
#define IMAGEBASE_H

#include <QImage>

#include <memory>

#include "src/number.h"
#include "color.h"


template<class T>
class ImageBase
{
public:
    ImageBase();
    ImageBase(const ImageBase &image);
    ImageBase(ImageBase &&image);
    ImageBase(uint32 height, uint32 width);

    ImageBase &operator =(const ImageBase &image);
    ImageBase &operator =(ImageBase &&image);

public:
    const T &at(uint32 i, uint32 j) const;
    void set(uint32 i, uint32 j, const T &color);

    uint32 getHeight() const;
    void setHeight(uint32 value);

    uint32 getWidth() const;
    void setWidth(uint32 value);

private:
    std::unique_ptr<T[]> data;
    uint32 width, height;

    friend class ImageConverter;
    friend class GrayscaleConverter;
};

template<class T>
ImageBase<T>::ImageBase() :
    data(nullptr),
    width(0),
    height(0)
{
}

template<class T>
ImageBase<T>::ImageBase(const ImageBase &image) :
    data(std::make_unique<T[]>(image.width * image.height)),
    width(image.width),
    height(image.height)
{
    for (uint32 i = 0; i < width * height; i++)
    {
        data[i] = image.data[i];
    }
}

template<class T>
ImageBase<T>::ImageBase(ImageBase &&image) :
    data(std::move(image.data)),
    width(image.width),
    height(image.height)
{
    image.data = nullptr;
}

template<class T>
ImageBase<T>::ImageBase(uint32 height, uint32 width) :
    data(std::make_unique<T[]>(width * height)),
    width(width),
    height(height)
{
    for (uint32 i = 0; i < width * height; i++)
    {
        data[i] = T(0);
    }
}


template<class T>
ImageBase<T> &ImageBase<T>::operator =(const ImageBase<T> &image)
{
    width = image.width;
    height = image.height;
    data = std::make_unique<T[]>(width * height);

    for (uint32 i = 0; i < width * height; i++)
    {
        data[i] = image.data[i];
    }

    return *this;
}

template<class T>
ImageBase<T> &ImageBase<T>::operator =(ImageBase<T> &&image)
{
    data = std::move(image.data);
    width = image.width;
    height = image.height;
    image.data = nullptr;
    return *this;
}


template<class T>
const T &ImageBase<T>::at(uint32 i, uint32 j) const
{
    return data[i * width + j];
}

template<class T>
void ImageBase<T>::set(uint32 i, uint32 j, const T &color)
{
    data[i * width + j] = color;
}

template<class T>
uint32 ImageBase<T>::getHeight() const
{
    return height;
}

template<class T>
void ImageBase<T>::setHeight(uint32 value)
{
    height = value;
}

template<class T>
uint32 ImageBase<T>::getWidth() const
{
    return width;
}

template<class T>
void ImageBase<T>::setWidth(uint32 value)
{
    width = value;
}


#endif // IMAGEBASE_H
