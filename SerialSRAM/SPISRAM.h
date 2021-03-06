/*
 Copyright (c) 2010 by arms22 (arms22 at gmail.com)
 Microchip 23x256 SPI SRAM library for Arduino

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 23K256/640
 modified by Sin

 */

#ifndef SPISRAM_H
#define SPISRAM_H

#include <Arduino.h>
#include <SPI.h>
#include <Stream.h>

class SPISRAM : public Stream {
private:
	const byte _csPin;
	const byte _addrbus;
	long _readpt, _writept;
//	byte clock_divider;
//	byte spi_mode;
//	byte status_cache;

// INSTRUCTION SET
	static const byte READ = 0x03; // Read data from memory
	static const byte WRITE = 0x02; // Write data to memory
	// EDIO
	// EQIO
	// RSTIO
	static const byte RDSR = 0x05; // Read Status register
	static const byte WRSR = 0x01; // Write Status register

	// STATUS REGISTER
	static const byte BYTE_MODE = 0x00;
	static const byte PAGE_MODE = 0x80;
	static const byte SEQ_MODE = 0x40;

	void set_access(const byte mode, const long & address) {
		SPI.transfer(mode);
		if (_addrbus == BUS_MBits)
			SPI.transfer(address >> 16 & 0xff);
		SPI.transfer(address >> 8 & 0xff);
		SPI.transfer(address & 0xff);
	}

	void writeStatusRegister(byte stat) {
		SPI.transfer(WRSR);
		SPI.transfer(stat);
	}

	byte readStatusRegister() {
		return SPI.transfer(RDSR);
	}

public:
	enum {
		BUS_WIDTH_23K256 = 16, // 23K256
		BUS_WIDTH_23K640 = 16,  // 23K640
		BUS_WIDTH_23LC1024 = 24, // 23A/LC1024
		BUS_KBits = 16,
		BUS_MBits = 24
	};

	SPISRAM(const byte csPin, const byte addrwidth = BUS_WIDTH_23K256);

	void init();
	inline void begin() {
		init();
	}
	inline void setSPIMode();

	byte read(const long & address);
	void read(const long & address, byte *buffer, const long & size);
	void write(const long & address, byte data);
	void write(const long & address, byte *buffer, const long & size);
	const long & readpoint() { return _readpt; }
	const long & writepoint() { return _writept; }
	virtual size_t write(uint8_t val) { write(_writept, val); return 1; }
	virtual int read(void) { return read(_readpt); }
	virtual int peek(void) { uint8_t val = read(_readpt); _readpt--; return val; }
	virtual int available(void);
	virtual void flush(void) { _readpt = _writept; }
	void reset(long val = (long)0) { _readpt = val; _writept = _readpt; }

	inline void csLow();
	inline void csHigh();
	inline void select(void);
	inline void deselect(void);
};

#endif
