#pragma once
#include <chrono>
#include <random>
#include <string>
#include <vector>
#include <stdint.h>
#include <cmath>

struct vec2
{
public:
	float x = 512;
	float y = 512;

	vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	vec2 operator*(vec2 rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return vec2(this->x, this->y);
	}

	vec2 operator*(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return vec2(this->x, this->y);
	}

	vec2 operator+(vec2 rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return vec2(this->x, this->y);
	}
};

class SimplexNoise
{
private:
	vec2 m_size;
	std::vector<float> m_texture;

private:
	float m_frequency;
	float m_amplitude;
	float m_lacunarity;
	float m_persistence;
	float m_octaves;
	float m_scale;

public:
	explicit SimplexNoise(vec2 size = vec2(512, 512), float frequency = 1.0f, float amplitude = 1.0f, float lacunarity = 2.0f, float persistence = 0.5f, int octaves = 3, float scale = 0.0025):
		m_size(size),
		m_frequency(frequency),
		m_amplitude(amplitude),
		m_lacunarity(lacunarity),
		m_persistence(persistence),
		m_octaves(octaves),
		m_scale(scale)
	{
	}

public:
	void GenerateNoise(vec2 position);
	void CreateTexture(vec2 position);
	std::vector<float> GetTexture();

private:
	static float noise(vec2 position);
	float fbm(vec2 position);
};