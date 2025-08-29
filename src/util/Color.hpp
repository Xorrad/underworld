#pragma once

struct Color;
struct HSVColor;

struct Color {
	uint8_t r, g, b, a;

	Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}
	
	bool operator ==(const Color& other) const {
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}
	
	bool operator !=(const Color& other) const {
		return !(*(this) == other);
	}

	Color& operator =(const Color& other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		return (*this);
	}

	uint32_t ToInteger() const {
		return (r << 24) + (g << 16) + (b << 8) + (a);
	}

	std::string ToHex() const {
		return std::format("{:02x}{:02x}{:02x}", r, g, b);
	}

	static Color FromHex(uint32_t hex) {
		uint8_t r = (hex >> 24) & 0xFF;
		uint8_t g = (hex >> 16) & 0xFF;
		uint8_t b = (hex >> 8) & 0xFF;
		uint8_t a = (hex) & 0xFF;
		return Color(r, g, b, a);
	}
	
	static Color FromHex(std::string str) {
		Color color;
		if (str.starts_with("#"))
			str = str.substr(1, std::max((size_t) 0, std::min((size_t) 6, str.size())));
		unsigned long hex;
		auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), hex, 16);
		if (ec != std::errc())
			return color;
		color.r = static_cast<uint8_t>((hex >> 16) & 0xFF);
		color.g = static_cast<uint8_t>((hex >> 8) & 0xFF);
		color.b = static_cast<uint8_t>(hex & 0xFF);
		return color;
	}
};

struct HSVColor {
	float h; // Hue component, range: [0.f, 360.f)
	float s; // Saturation component, range: [0.f, 1.f)
	float v; // Value component, range: [0.f, 1.f)

	HSVColor(float hue, float saturation, float value) : h(hue), s(saturation), v(value) {}
	HSVColor(const Color& rgb) {
		HSVColor hsv = FromRgb(rgb);
		(*this) = hsv;
	}

	operator Color() const {
		return ToRgb();
	}
	
	bool operator ==(const HSVColor& other) const {
		return h == other.h && s == other.s && v == other.v;
	}
	
	bool operator !=(const HSVColor& other) const {
		return !(*(this) == other);
	}

	HSVColor& operator =(const HSVColor& other) {
		h = other.h;
		s = other.s;
		v = other.v;
		return (*this);
	}

	uint32_t ToInteger() const {
		return ToRgb().ToInteger();
	}

	// credits to https://gist.github.com/marukrap/7c361f2c367eaf40537a8715e3fd952as
	// for the conversion between rgb and hsv.

	static HSVColor FromRgb(const Color& rgb) {
		float R = rgb.r / 255.f;
		float G = rgb.g / 255.f;
		float B = rgb.b / 255.f;

		float M = std::max({ R, G, B });
		float m = std::min({ R, G, B });
		float C = M - m; // Chroma

		float H = 0.f; // Hue
		float S = 0.f; // Saturation
		float V = 0.f; // Value

		if(C != 0.f) {
			if(M == R) H = std::fmod(((G - B) / C), 6.f);
			else if(M == G) H = ((B - R) / C) + 2;
			else if(M == B) H = ((R - G) / C) + 4;
			H *= 60;
		}
		if(H < 0.f) H += 360;
		V = M;
		if(V != 0.f) S = C / V;
		return HSVColor(H, S, V);
	}
	
	Color ToRgb() const {
		float C = s * v; // Chroma
		float HPrime = std::fmod(h / 60, 6.f); // H'
		float X = C * (1 - std::fabs(std::fmod(HPrime, 2.f) - 1));
		float M = v - C;

		float R = 0.f;
		float G = 0.f;
		float B = 0.f;

		switch(static_cast<int>(HPrime)) {
			case 0: R = C; G = X;        break; // [0, 1)
			case 1: R = X; G = C;        break; // [1, 2)
			case 2:        G = C; B = X; break; // [2, 3)
			case 3:        G = X; B = C; break; // [3, 4)
			case 4: R = X;        B = C; break; // [4, 5)
			case 5: R = C;        B = X; break; // [5, 6)
		}
		R += M;
		G += M;
		B += M;
		return Color(
			static_cast<uint8_t>(std::round(R * 255)),
			static_cast<uint8_t>(std::round(G * 255)),
			static_cast<uint8_t>(std::round(B * 255)),
			255
		);	
	}
};