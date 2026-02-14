#pragma once

namespace rat {

	enum class TextureFormat { RGBA };

	class Texture {
	public:
		virtual unsigned getWidth() const = 0;
		virtual unsigned getHeight() const = 0;
		virtual unsigned getDepth() const = 0;
		TextureFormat getFormat() const { return m_format; }

	protected:
		virtual ~Texture() = default;

	protected:
		TextureFormat m_format;
	};

	class BaseTexture2D : public Texture {
	public:
		virtual unsigned getWidth() const override { return m_width; }
		virtual unsigned getHeight() const override { return m_height; }
		virtual unsigned getDepth() const override { return 1; }

		virtual void setData(const void* data) = 0;
		virtual void setData(const void* data, unsigned width, unsigned height, TextureFormat format) = 0;

	protected:
		unsigned m_width;
		unsigned m_height;
	};

	using Texture2D = BaseTexture2D;

} // namespace rat
