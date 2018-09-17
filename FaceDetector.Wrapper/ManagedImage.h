#pragma once

public ref class ManagedImage
{
public:
	ManagedImage(System::Drawing::Size^ size)
	{
		channels = 3;
		data = gcnew cli::array<System::Byte>(size->Width * size->Height * channels);
		width = size->Width;
		height = size->Height;
		step = width * channels;
	}

	cli::array<System::Byte>^ data;
	int width;
	int height;
	int step;
	int channels;
};
