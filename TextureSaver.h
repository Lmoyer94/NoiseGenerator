#pragma once
#include <stdint.h>
#include <string>
#include <fstream>
#include <vector>

struct BMPHeader
{
	char bitmapSignatureBytes[2] = {'B', 'M'};
	uint32_t sizeofBitmapFile = 54;
	uint32_t reservedBytes = 0;
	uint32_t pixelDataOffset = 54;
};

struct BMPInfoHeader
{
	uint32_t headersize = 40;
	int32_t width = 0;
	int32_t height = 0;
	uint16_t colorPlanes = 1;
	uint16_t colorDepth = 24;
	uint16_t compressionMethod = 0;
	uint16_t rawBitmapDataSize = 0;
	uint16_t horizontalResolution = 3780;
	uint16_t verticalResolution = 3780;
	uint32_t colorTableEntries = 0;
	uint32_t importantColors = 0;
};

struct Pixel
{
	uint8_t blue = 255;
	uint8_t green = 255;
	uint8_t red = 0;
};


void SaveBMP(std::string filename, std::vector<float> texture, int width, int height)
{
	std::string filepath = filename + ".bmp";
	std::ofstream outFile(filepath, std::ofstream::binary);

	BMPHeader bmpHeader;
	BMPInfoHeader bmpInfoHeader;

	bmpHeader.sizeofBitmapFile += (width * height) * 3;

	bmpInfoHeader.width = width;
	bmpInfoHeader.height = height;

	outFile.write((char*)&bmpHeader.bitmapSignatureBytes, 2);
	outFile.write((char*)&bmpHeader.sizeofBitmapFile, sizeof(uint32_t));
	outFile.write((char*)&bmpHeader.reservedBytes, sizeof(uint32_t));
	outFile.write((char*)&bmpHeader.pixelDataOffset, sizeof(uint32_t));

	outFile.write((char*)&bmpInfoHeader.headersize, sizeof(uint32_t));
	outFile.write((char*)&bmpInfoHeader.width, sizeof(int32_t));
	outFile.write((char*)&bmpInfoHeader.height, sizeof(int32_t));
	outFile.write((char*)&bmpInfoHeader.colorPlanes, sizeof(uint16_t));
	outFile.write((char*)&bmpInfoHeader.colorDepth, sizeof(uint16_t));
	outFile.write((char*)&bmpInfoHeader.compressionMethod, sizeof(uint32_t));
	outFile.write((char*)&bmpInfoHeader.rawBitmapDataSize, sizeof(uint32_t));
	outFile.write((char*)&bmpInfoHeader.horizontalResolution, sizeof(uint32_t));
	outFile.write((char*)&bmpInfoHeader.verticalResolution, sizeof(uint32_t));
	outFile.write((char*)&bmpInfoHeader.colorTableEntries, sizeof(uint32_t));
	outFile.write((char*)&bmpInfoHeader.importantColors, sizeof(uint32_t));

	size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
	for (int i = 0; i < numberOfPixels; i++)
	{
		Pixel pixel;
		pixel.blue = pixel.green = pixel.red = (uint8_t) ((texture[i] + 1) / 2 * 255);

		outFile.write((char*)&pixel.blue, sizeof(uint8_t));
		outFile.write((char*)&pixel.green, sizeof(uint8_t));
		outFile.write((char*)&pixel.red, sizeof(uint8_t));
	}

	outFile.close();
}