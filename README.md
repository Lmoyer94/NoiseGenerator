Proper Usage

Example1 usage:

SimplexNoise noise(vec2(256, 256));
noise.GenerateNoise(vec2(0, 0));
SaveBMP("noise", noise.GetTexture(), 256, 256)



Example2 usage:

SimplexNoise noise(vec2(256, 256), 1.0f, 1.0f, 2.0f, 0.5f, 3, 0.0025f);
noise.GenerateNoise(vec2(100, 256));
SaveBMP("noise", noise.GetTexture(), 256, 256);
