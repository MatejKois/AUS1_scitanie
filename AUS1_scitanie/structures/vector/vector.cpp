#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		std::memcpy(memory_, other.memory_, size_);
	}

	Vector::~Vector()
	{
		std::free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other)
		{
			Vector& otherVector = dynamic_cast<Vector&>(other);
			size_ = otherVector.size_;
			memory_ = std::realloc(memory_, otherVector.size_);
			std::memcpy(memory_, otherVector.memory_, size_);
		}
		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		if (this != &other)
		{
			Vector* otherVector = dynamic_cast<Vector*>(&other);
			if (otherVector == nullptr)
			{
				return false;
			}
			return this->size_ == otherVector->size_
				&& std::memcmp(this->memory_, otherVector->memory_, size_) == 0;
		}
		else
		{
			return true;
		}
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Index out of range!");
		byte* firstByte = reinterpret_cast<byte*>(memory_);
		firstByte += index;
		return *(firstByte);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		Utils::rangeCheckExcept(srcStartIndex, src.size(), "Index out of range!");
		Utils::rangeCheckExcept(destStartIndex, dest.size(), "Index out of range!");
		Utils::rangeCheckExcept(srcStartIndex + length, src.size() + 1, "Index out of range!");
		Utils::rangeCheckExcept(destStartIndex + length, dest.size() + 1, "Index out of range!");


		if (&src == &dest && std::abs(srcStartIndex - destStartIndex) < length)
		{
			std::memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else
		{
			std::memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Index out of range!");
		//return &this->at(index);
		byte* firstByte = reinterpret_cast<byte*>(memory_);
		firstByte += index;
		return (firstByte);
	}
}
