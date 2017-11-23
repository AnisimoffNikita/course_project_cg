#include "gaussianblur.h"

#include "src/image/imageconverter.h"
#include "src/math/math.h"

GaussianBlur::GaussianBlur(float sigma, uint8 kernelSize):
    sigma(sigma),
    kernelSize(kernelSize)
{
}

GaussianBlur::~GaussianBlur()
{
}

void GaussianBlur::process(Image &image)
{
    if (kernelSize == 1)
    {
        return;
    }

    Image saved(image);
    float sum = 0;
    float kernel[kernelSize][kernelSize];

    for (int i = 0; i < kernelSize; i++)
        for (int j = 0; j < kernelSize; j++)
        {
            kernel[i][j] = Math::Gauss2(sigma, i - kernelSize / 2, j - kernelSize / 2);
            sum += kernel[i][j];
        }

    for (int i = 0; i < kernelSize; i++)
        for (int j = 0; j < kernelSize; j++)
        {
            kernel[i][j] /= sum;
        }

    uint32 height = image.getHeight();
    uint32 width = image.getWidth();
    uint32 pixelPosX;
    uint32 pixelPosY;
    float resultR, resultG, resultB;

    for (uint32 y = 0; y < height; y++)
    {
        for (uint32 x = 0; x < width; x++)
        {
            resultR = resultG = resultB = 0;

            for (int i = 0; i < kernelSize; i++)
            {
                for (int j = 0; j < kernelSize; j++)
                {
                    pixelPosX = (x + j - kernelSize / 2 + width) % width;
                    pixelPosY = (y + i - kernelSize / 2 + height) % height;
                    Color color = saved.at(pixelPosY, pixelPosX);
                    float kernelVal = kernel[i][j];
                    resultR += color.getRed() * kernelVal;
                    resultG += color.getGreen() * kernelVal;
                    resultB += color.getBlue() * kernelVal;
                }
            }

            image.set(y, x, Color(static_cast<uint8>(resultR),
                                  static_cast<uint8>(resultG),
                                  static_cast<uint8>(resultB)));
        }
    }
}

float GaussianBlur::getSigma() const
{
    return sigma;
}

void GaussianBlur::setSigma(float value)
{
    sigma = value;
}

uint8 GaussianBlur::getKernelSize() const
{
    return kernelSize;
}

void GaussianBlur::setKernelSize(const uint8 &value)
{
    kernelSize = value;
}
