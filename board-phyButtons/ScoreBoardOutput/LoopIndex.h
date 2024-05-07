#ifndef _LOOPINDEX_HPP_
#define _LOOPINDEX_HPP_

class LoopIndex
{
public:

	LoopIndex(uint8_t min, uint8_t max) : _index(min), _minIndex(min), _maxIndex(max)
	{
	};

	uint8_t set(uint8_t index)
	{
		if (index >= _maxIndex) _index = _maxIndex;
		else if (index <= _minIndex) _index = _minIndex;
		else _index = index;

		return _index;
	}

	inline uint8_t getMin() const
	{
		return _minIndex;
	}

	inline uint8_t getMax() const
	{
		return _maxIndex;
	}

	inline operator uint8_t() const
	{
		return _index;
	}

	LoopIndex operator++()
	{
		increment();
		return LoopIndex(*this);
	}

	LoopIndex operator++(int)
	{
		LoopIndex preModified(*this);
		increment();
		return preModified;
	}

	LoopIndex operator--()
	{
		decrement();
		return LoopIndex(*this);
	}

	LoopIndex operator--(int)
	{
		LoopIndex preModified(*this);
		decrement();
		return preModified;
	}

protected:

	inline void increment()
	{
		if (_index == _maxIndex) _index = _minIndex;
		else ++_index;
	}

	inline void decrement()
	{
		if (_index == _minIndex) _index = _maxIndex;
		else --_index;
	}

private:

	uint8_t _index;
	uint8_t _minIndex;
	uint8_t _maxIndex;

};


#endif